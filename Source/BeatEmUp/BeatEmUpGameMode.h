// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "BeatEmUpSaveGame.h"
#include "Enemy.h"
#include "Familiar.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BeatEmUpGameMode.generated.h"

UCLASS(minimalapi)
class ABeatEmUpGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABeatEmUpGameMode();
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<AEnemy> EnemyClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AFamiliar> FamiliarClass;
	UPROPERTY(EditAnywhere)
    	TSubclassOf<ATrap> TrapClass;	
	void Load(UBeatEmUpSaveGame* LoadedGame);
	void Save(UBeatEmUpSaveGame* SaveGame);
	UFUNCTION()
		void PostBeginPlay();
};



