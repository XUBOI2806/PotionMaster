// Fill out your copyright notice in the Description page of Project Settings.


#include "FamiliarAttackTask.h"

#include "FamiliarController.h"


EBTNodeResult::Type UFamiliarAttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get the behavior tree component from the owner
	UBehaviorTreeComponent* BTComp = &OwnerComp;

	// Check if the behavior tree component is valid
	if (!BTComp) { return EBTNodeResult::Failed; }

	// Cast the owner to AFamiliarController
	AFamiliarController* FamiliarController = Cast<AFamiliarController>(BTComp->GetOwner());

	// Check if the cast was successful
	if (!FamiliarController) { return EBTNodeResult::Failed; }

	// Call the attack function on the familiar controller
	FamiliarController->Attack();

	// Return succeeded result
	return EBTNodeResult::Succeeded;
}
