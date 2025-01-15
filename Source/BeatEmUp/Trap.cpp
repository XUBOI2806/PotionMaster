// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap.h"

// Sets default values
ATrap::ATrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); 
	RootComponent = Mesh;

	// Flashing variables
	CurrentLifeTime = 0.0f;
	bIsFlashing = false;
	FlashToggleInterval = 0.25f;
	LastToggleTime = 0.0f;
}

// Called when the game starts or when spawned
void ATrap::BeginPlay()
{
	Super::BeginPlay();

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &ATrap::OnOverlapBegin);

	// Checks if there is a Trap Material Class and create a Material Instance
	if (TrapMaterialClass)
	{
		TrapMaterialInstance = UMaterialInstanceDynamic::Create(TrapMaterialClass, this);
		Mesh->SetMaterial(0, TrapMaterialInstance);
	}
}

// Called every frame
void ATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentLifeTime += DeltaTime;

	// Checks is the Trap is flashing
	if (bIsFlashing)
	{
		// Check if the accumulated time has reached or exceeded the toggle interval
		LastToggleTime += DeltaTime;
		if (LastToggleTime >= FlashToggleInterval)
		{
			LastToggleTime = 0.0f;
			// Toggle the intensity value between 1.0f and 500.0f
			FlashingIntensity = (FlashingIntensity == 1.0f) ? 500.0f : 1.0f;
			if (TrapMaterialInstance)
			{
				TrapMaterialInstance->SetScalarParameterValue(TEXT("Intensity"), FlashingIntensity);
			}
		}
	}
	else
	{
		// Normal glow intensity behavior when not flashing
		float GlowIntensity = (FMath::Sin(CurrentLifeTime) + 1.0f) / 2.0f * 2.0f;
		if (TrapMaterialInstance)
		{
			TrapMaterialInstance->SetScalarParameterValue(TEXT("Intensity"), GlowIntensity);
		}
	}
}

void ATrap::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Check if the overlapping actor is the player and disable their input temporarily
	if (ABeatEmUpCharacter* PlayerHit = Cast<ABeatEmUpCharacter>(OtherActor))
	{
		PlayerHit->DisableInput(nullptr);
		Player = PlayerHit;
		FTimerHandle UnusedHandle;
		// Set a timer to restore movement after a delay
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &ATrap::RestoreMovement, ImmobilizeDuration, false);
		// Start flashing
		bIsFlashing = true;
	}
}

void ATrap::RestoreMovement()
{
    // Restore player input and destroy the trap
	Player->EnableInput(nullptr);
	Destroy();
}
