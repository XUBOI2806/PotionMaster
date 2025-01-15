// Fill out your copyright notice in the Description page of Project Settings.

#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BluePotion.h"

#include "Enemy.h"

// Sets default values
ABluePotion::ABluePotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Set up projectile mesh and movement component
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));

	MovementComponent->InitialSpeed = MovementSpeed; // Set initial speed
	MovementComponent->ProjectileGravityScale = 1; // Set gravity scale
	MovementComponent->bSweepCollision = true; // Enable sweeping collision detection
	MovementComponent->UpdatedComponent = ProjectileMesh; // Set updated component
}

// Called when the game starts or when spawned
void ABluePotion::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &ABluePotion::OnProjectileHit);
	ProjectileMesh->SetNotifyRigidBodyCollision(true);
}

// Called every frame
void ABluePotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Move the projectile forward
	FVector Movement = GetActorForwardVector() * (MovementSpeed * DeltaTime);
	FVector NewLocation = GetActorLocation() + Movement;
	SetActorLocation(NewLocation);
}

void ABluePotion::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit"));
    if (OtherActor != this && OtherActor != GetOwner() && !OtherActor->ActorHasTag("PlayerTeam"))
    {
    	// Create Area effect then destroy
    	CreateAOEEffect(Hit.Location);
        Destroy();
    }
}

void ABluePotion::CreateAOEEffect(const FVector& ImpactPoint)
{
	
	// Set effect radius
	float Radius = 500.0f;
	TArray<FOverlapResult> Overlaps;
	// Define collision shape
	FCollisionShape CollShape = FCollisionShape::MakeSphere(Radius);

	// Draw a debug sphere for visualization
	// DrawDebugSphere(GetWorld(), ImpactPoint, Radius, 32, FColor::Cyan, false, 5.0f);

	// Spawning Snow Particle Effect for the Freeze AOE
	if(SnowParticleClass)
	{
		UNiagaraComponent* SpawnedEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SnowParticleClass, ImpactPoint);
		SpawnedEffect->SetColorParameter(FName("User.SpawnColour"), FLinearColor::MakeRandomColor());
	}

	// Check for overlaps with enemies within the radius
	if (GetWorld()->OverlapMultiByChannel(Overlaps, ImpactPoint, FQuat::Identity, ECC_GameTraceChannel1, CollShape))
	{
		for (FOverlapResult Overlap : Overlaps)
		{
			AActor* OverlappedActor = Overlap.GetActor();
			if (OverlappedActor && OverlappedActor != this)
			{
				AEnemy* Enemy = Cast<AEnemy>(OverlappedActor);
				if (Enemy)
				{
					//Freeze Enemy
					Enemy->Freeze();
				}
			}
		}
	}
}
