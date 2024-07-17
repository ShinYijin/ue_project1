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
	// �� �׽�ũ�� ����Ǹ� ���ؾ������� �� �Լ� �ȿ� ���ߵȴ�. 
		// ��ȯ���� EBTNodeResult::Type �̶�� ���� ������. �̰ſ� ���� behavior tree�� �� �׽�ũ�� �����ߴ��� �� �� ����. 
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
