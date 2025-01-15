// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BeatEmUpCharacter.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trap.generated.h"

UCLASS()
class BEATEMUP_API ATrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* Mesh;

	// Trap Material Class
	UPROPERTY(EditAnywhere)
		UMaterialInterface* TrapMaterialClass;

	// Trap Material Instance
	UPROPERTY()
		UMaterialInstanceDynamic* TrapMaterialInstance;

	// Current Lifetime
	float CurrentLifeTime;

	// Is Flashing
	bool bIsFlashing;

	// Flashing interval
	float FlashToggleInterval;

	// Toggle Time
	float LastToggleTime;

	// Flashing Intensity
	float FlashingIntensity;
	
	// Trap Duration
	UPROPERTY(EditAnywhere)
		float ImmobilizeDuration;

	ABeatEmUpCharacter* Player;
	
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Function to restore movement to player
	UFUNCTION()
	void RestoreMovement();
};
