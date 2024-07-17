// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Attak.generated.h"

/**
 * 
 */
UCLASS()
class UE_PROJECT1_API UBTTask_Attak : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_Attak();

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

private:
	bool bIsAttacking = false;


};
