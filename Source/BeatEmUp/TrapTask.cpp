// Fill out your copyright notice in the Description page of Project Settings.


#include "TrapTask.h"

#include "EnemyBTController.h"

EBTNodeResult::Type UTrapTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get a reference to the Behavior Tree Component and ensure it's valid
	UBehaviorTreeComponent* BTComp = &OwnerComp;
	if (!BTComp) { return EBTNodeResult::Failed; }

	// Cast the owner of the Behavior Tree Component to the specific AI Controller and check for validity
	AEnemyBTController* BTController = Cast<AEnemyBTController>(BTComp->GetOwner());
	if (!BTController) { return EBTNodeResult::Failed; }

	// Execute the trap placement function from the AI Controller and return success
	BTController->PlaceTrap();
	return EBTNodeResult::Succeeded;
}