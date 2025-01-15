// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TrapTask.generated.h"

/**
 * 
 */
UCLASS()
class BEATEMUP_API UTrapTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	// Overrides the ExecuteTask method to implement specific behavior for the task
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
