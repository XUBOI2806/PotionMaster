// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FamiliarAttackTask.generated.h"

/**
 * 
 */
UCLASS()
class BEATEMUP_API UFamiliarAttackTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	// Override the ExecuteTask function from the behavior tree component
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
