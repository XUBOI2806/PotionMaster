// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BeatEmUpCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelTrigger.generated.h"


UCLASS()
class BEATEMUP_API ALevelTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere)
		UBoxComponent* TriggerVolume;
	UPROPERTY(EditAnywhere)
		FName LevelToLoad;
	UPROPERTY(EditAnywhere)
		bool bLoadLevel;
	UFUNCTION()
		void StartLevelStreaming(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 BodyIndex, bool bSweep, const FHitResult& Hit);

};
