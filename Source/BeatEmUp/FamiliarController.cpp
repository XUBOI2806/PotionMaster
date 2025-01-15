// Fill out your copyright notice in the Description page of Project Settings.


#include "FamiliarController.h"

#include "Familiar.h"

AFamiliarController::AFamiliarController()
{
    // Enable ticking for this actor
    PrimaryActorTick.bCanEverTick = true;

    // Create and configure sight perception component
    SightConfiguration = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Configuration"));
    SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

    SightConfiguration->SightRadius = SightRadius;
    SightConfiguration->LoseSightRadius = LoseSightRadius;
    SightConfiguration->PeripheralVisionAngleDegrees = FieldOfView;
    SightConfiguration->SetMaxAge(SightAge);

    // Set detection affiliations
    SightConfiguration->DetectionByAffiliation.bDetectEnemies = true;
    SightConfiguration->DetectionByAffiliation.bDetectFriendlies = true;
    SightConfiguration->DetectionByAffiliation.bDetectNeutrals = true;

    // Configure the perception component
    GetPerceptionComponent()->SetDominantSense(*SightConfiguration->GetSenseImplementation());
    GetPerceptionComponent()->ConfigureSense(*SightConfiguration);
}

void AFamiliarController::BeginPlay()
{
    Super::BeginPlay();

    // Get the navigation system
    NavigationSystem = Cast<UNavigationSystemV1>(GetWorld()->GetNavigationSystem());

    // Initialize the blackboard and run the behavior tree
    UseBlackboard(AIBlackboard, BlackboardComponent);
    RunBehaviorTree(BehaviourTree);

    // Bind the perception update event
    GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AFamiliarController::OnSensesUpdated);

    // Get the player character
    PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void AFamiliarController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // Update the enemy position in the blackboard
    if (TargetEnemy)
    {
        BlackboardComponent->SetValueAsVector("EnemyPosition", TargetEnemy->GetActorLocation());
    }

    // Update the player position in the blackboard
    if (PlayerCharacter)
    {
        BlackboardComponent->SetValueAsVector("PlayerPosition", PlayerCharacter->GetActorLocation());
    }
}

FRotator AFamiliarController::GetControlRotation() const
{
    if(GetPawn())
    {
        return FRotator(0, GetPawn()->GetActorRotation().Yaw, 0);
    }
    return Super::GetControlRotation();
}

void AFamiliarController::OnSensesUpdated(AActor* UpdatedActor, FAIStimulus Stimulus)
{
    APawn* SensedPawn = Cast<APawn>(UpdatedActor);
    if (SensedPawn && !SensedPawn->IsPlayerControlled())
    {
        if (Stimulus.WasSuccessfullySensed())
        {
            // Update blackboard when an enemy is sensed
            TargetEnemy = SensedPawn;
            BlackboardComponent->SetValueAsBool("AttackEnemy", true);
            BlackboardComponent->SetValueAsVector("EnemyPosition", TargetEnemy->GetActorLocation());
        }
        else
        {
            // Clear the target enemy when it's no longer sensed
            TargetEnemy = nullptr;
            BlackboardComponent->SetValueAsBool("AttackEnemy", false);
        }
    }
}

void AFamiliarController::Attack()
{
    if (TargetEnemy)
    {
        // Calculate shoot direction and perform attack
        FVector ShootDirection = TargetEnemy->GetActorLocation() - GetPawn()->GetActorLocation();
        Cast<AFamiliar>(GetPawn())->AttackEnemies(ShootDirection);
    }
}