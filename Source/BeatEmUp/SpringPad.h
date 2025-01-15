// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpringPad.generated.h"

UCLASS()
class BEATEMUP_API ASpringPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpringPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Mesh component for the spring pad
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	// Trigger box component for detecting overlaps
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;

	// Strength of the launch
	UPROPERTY(EditAnywhere)
	float LaunchStrength = 1000.0f;

	// Direction of the launch
	UPROPERTY(EditAnywhere)
	FVector LaunchDirection = FVector(0, 0, 1);

	// Function called when an overlap begins
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);};
