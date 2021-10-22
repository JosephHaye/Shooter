// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ClearBlackboard.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API UBTTask_ClearBlackboard : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTTask_ClearBlackboard();

private:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
