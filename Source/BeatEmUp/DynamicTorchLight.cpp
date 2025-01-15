// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamicTorchLight.h"

// Sets default values
ADynamicTorchLight::ADynamicTorchLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	RootComponent = PointLight;
}

// Called when the game starts or when spawned
void ADynamicTorchLight::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADynamicTorchLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Increase FlickerTime by DeltaTime.
	FlickerTime += DeltaTime;

	// Check if FlickerTime has reached or exceeded FlickerSpeed.
	if (FlickerTime >= FlickerSpeed)
	{
		// Reset FlickerTime to 0.
		FlickerTime = 0;
    
		// Generate a new random intensity value between MinIntensity and MaxIntensity.
		float NewIntensity = FMath::RandRange(MinIntensity, MaxIntensity);
    
		// Set the new intensity for the PointLight.
		PointLight->SetIntensity(NewIntensity);
	}
}

