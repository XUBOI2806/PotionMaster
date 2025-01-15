// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NavigationSystem.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h" 
#include "Perception/AIPerceptionComponent.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "BeatEmUpCharacter.h"
#include "FamiliarController.generated.h"

/**
 * 
 */
UCLASS()
class BEATEMUP_API AFamiliarController : public AAIController
{
	GENERATED_BODY()
	
public:
	AFamiliarController();
	
	// Override BeginPlay function
	virtual void BeginPlay() override;

	// Override Tick function
	virtual void Tick(float DeltaSeconds) override;

	// Override GetControlRotation function
	virtual FRotator GetControlRotation() const override;

	// Function to handle perception updates
	UFUNCTION()
	void OnSensesUpdated(AActor* UpdatedActor, FAIStimulus Stimulus);

	// Sight perception properties
	UPROPERTY(EditAnywhere)
	float SightRadius = 500;

	UPROPERTY(EditAnywhere)
	float SightAge = 3.5;

	UPROPERTY(EditAnywhere)
	float LoseSightRadius = SightRadius + 50;

	UPROPERTY(EditAnywhere)
	float FieldOfView = 360;

	// Sight configuration for AI
	UPROPERTY(EditAnywhere)
	UAISenseConfig_Sight* SightConfiguration;

	// Blackboard data for AI
	UPROPERTY(EditAnywhere)
	UBlackboardData* AIBlackboard;

	// Behavior tree for AI
	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviourTree;

	// Blackboard component
	UPROPERTY()
	UBlackboardComponent* BlackboardComponent;

	// Navigation system
	UPROPERTY()
	UNavigationSystemV1* NavigationSystem;

	// Target enemy
	UPROPERTY()
	APawn* TargetEnemy;

	// Player character
	UPROPERTY()
	APawn* PlayerCharacter;

	// Function to handle attacking
	UFUNCTION()
	void Attack();

};
