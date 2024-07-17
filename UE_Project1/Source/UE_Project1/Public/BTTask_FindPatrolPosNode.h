// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindPatrolPosNode.generated.h"

/**
 * 
 */
UCLASS()
class UE_PROJECT1_API UBTTask_FindPatrolPosNode : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_FindPatrolPosNode();

public:
	// 이 테스크가 실행되면 뭘해야할지가 이 함수 안에 들어가야된다. 
		// 반환값은 EBTNodeResult::Type 이라는 성공 여부임. 이거에 따라 behavior tree가 이 테스크가 성공했는지 알 수 있음. 
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
