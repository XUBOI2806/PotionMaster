// Fill out your copyright notice in the Description page of Project Settings.


#include "SpringPad.h"
#include "Components/StaticMeshComponent.h"
#include "BeatEmUpCharacter.h"
#include "Enemy.h"


// Sets default values
ASpringPad::ASpringPad()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpringPadMesh"));
	RootComponent = Mesh;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(Mesh);
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ASpringPad::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ASpringPad::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpringPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpringPad::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Check if the overlapping actor is valid and not the spring pad itself
	if (OtherActor && (OtherActor != this))
	{
		// Check if the overlapping actor is an enemy
		AEnemy* HitEnemy = Cast<AEnemy>(OtherActor);
		if (HitEnemy)
		{
			// Calculate the launch velocity and launch the enemy
			FVector LaunchVelocity = LaunchDirection.GetSafeNormal() * LaunchStrength;
			HitEnemy->LaunchCharacter(LaunchVelocity, true, true);
		}

		// Check if the overlapping actor is the player's character
		ABeatEmUpCharacter* HitCharacter = Cast<ABeatEmUpCharacter>(OtherActor);
		if (HitCharacter)
		{
			// Calculate the launch velocity and launch the character
			FVector LaunchVelocity = LaunchDirection.GetSafeNormal() * LaunchStrength;
			HitCharacter->LaunchCharacter(LaunchVelocity, true, true);
		}
	}
}
