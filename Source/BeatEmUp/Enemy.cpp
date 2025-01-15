// Fill out your copyright notice in the Description page of Project Settings.

#include "NiagaraComponent.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "BrainComponent.h"
#include "EnemyBTController.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	Player = Cast<ABeatEmUpCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AEnemy::OnHit);

	if (DynamicSpotlightClass)
	{
		FVector SpawnLocation = GetActorLocation();
		Spotlight = Cast<ADynamicSpotlight>(GetWorld()->SpawnActor(DynamicSpotlightClass, &SpawnLocation));
		Spotlight->TargetActor = this;
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::DealDamage(float Damage)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.f, MaxHealth);
	
	UDamageTextUI* SpawnedDamage = Cast<UDamageTextUI>(CreateWidget(GetGameInstance(), DamageTextClass));
	UGameplayStatics::ProjectWorldToScreen(GetWorld()->GetFirstPlayerController(), GetMesh()->GetComponentLocation(),
	                                       SpawnedDamage->CurrentLocation);
	SpawnedDamage->DamageText->SetText(FText::FromString(FString::SanitizeFloat(Damage)));
	SpawnedDamage->TargetLocation += SpawnedDamage->CurrentLocation;
	SpawnedDamage->AddToViewport();
}

void AEnemy::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector Normal, const FHitResult& Hit)
{
	if(OtherActor == Player)
	{
		Player->DealDamage(DamageToPlayer);
 		Destroy(); 
	}
}

void AEnemy::Ragdoll()
{
	Cast<AEnemyBTController>(GetController())->BrainComponent->PauseLogic("Ragdolling!");
	GetMesh()->SetCollisionProfileName("Ragdoll");
    GetMesh()->SetSimulatePhysics(true);
    GetCapsuleComponent()->SetCollisionProfileName("NoCollision");
    GetWorld()->GetTimerManager().SetTimer(RagdollTimerHandle, this, &AEnemy::StopRagdoll, RagdollTime, false);
	Cast<AEnemyBTController>(GetController())->BrainComponent->ResumeLogic("Moving Again!");
}

void AEnemy::StopRagdoll()
{
	if(CurrentHealth <= 0)
	{
		Player->AddPotion();
		Player->AddEXP(EXPAmount);
		if(DeathParticleClass)
		{
			UNiagaraComponent* SpawnedEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DeathParticleClass, GetMesh()->GetComponentLocation());
			SpawnedEffect->SetColorParameter(FName("User.SpawnColour"), FLinearColor::MakeRandomColor());
		}
		if(HealthPackClass)
		{
			FVector SpawnLocation = GetMesh()->GetComponentLocation() + FVector(0,0,50);
			GetWorld()->SpawnActor(HealthPackClass, &SpawnLocation);
		}
		Spotlight->Destroy();
		Destroy();
		return;
	}
	GetMesh()->SetSimulatePhysics(false);
	GetMesh()->SetCollisionProfileName("CharacterMesh");
	GetCapsuleComponent()->SetWorldLocation(GetMesh()->GetSocketLocation("pelvis"));
	GetMesh()->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0,0,-90), FRotator(0,-90,0));
	GetCapsuleComponent()->SetCollisionProfileName("Pawn");
	GetCharacterMovement()->GravityScale = 1;
}

void AEnemy::Freeze()
{
	// Disable enemy movement for the freeze duration
	GetCharacterMovement()->DisableMovement();
	// Set a timer to unfreeze the enemy after 5 seconds
	GetWorld()->GetTimerManager().SetTimer(FreezeTimerHandle, this, &AEnemy::Unfreeze, 5.0f, false);
}

void AEnemy::Unfreeze()
{
	// Re-enable walking movement mode after the freeze period
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

void AEnemy::Shoot(FVector Direction)
{
	FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100;
	FRotator SpawnRotation = Direction.Rotation();
	ABullet* SpawnedBullet = Cast<ABullet>(GetWorld()->SpawnActor(BulletClass, &SpawnLocation, &SpawnRotation));
	Direction.Normalize();
	SpawnedBullet->MovementComponent->Velocity = Direction * SpawnedBullet->MovementSpeed;
}


void AEnemy::PlaceTrap()
{
	// Disable enemy movement while placing the trap
	GetCharacterMovement()->DisableMovement();
	// Set a timer to finish placing the trap after 2 seconds
	GetWorld()->GetTimerManager().SetTimer(PlaceTrapTimerHandle, this, &AEnemy::FinishPlacingTrap, 2.0f, false);
}

void AEnemy::FinishPlacingTrap()
{
	// Re-enable walking movement mode after placing the trap
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	// Spawn a trap at the enemy's current location
	GetWorld()->SpawnActor<ATrap>(TrapClass, GetActorLocation()- FVector(0.f, 0.f, 90.f), GetActorRotation());
}