// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/PointLightComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicTorchLight.generated.h"

UCLASS()
class BEATEMUP_API ADynamicTorchLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADynamicTorchLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Point light to flicker
	UPROPERTY(EditAnywhere)
	UPointLightComponent* PointLight;

	// Minimum light intensity
	UPROPERTY(EditAnywhere)
	float MinIntensity = 300;

	// Maximum light intensity
	UPROPERTY(EditAnywhere)
	float MaxIntensity = 500;

	// Time between flickers
	UPROPERTY(EditAnywhere)
	float FlickerSpeed = 0.1f;

	// Timer for flicker intervals
	UPROPERTY(EditAnywhere)
	float FlickerTime = 0;
};
