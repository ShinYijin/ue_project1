// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPatrolPosNode.h"

// TODO
#include "MyAIController.h"

#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_FindPatrolPosNode::UBTTask_FindPatrolPosNode()
{
	// task node name 설정
	NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UBTTask_FindPatrolPosNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	
	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (CurrentPawn == nullptr)
		return EBTNodeResult::Failed;

	// 네비게이션 메쉬가 필요함. 갈수있는 길이 뭔지 알수 있어야되니까. 
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (NavSystem == nullptr)
		return EBTNodeResult::Failed;

	// 내 위치로부터 인접한 랜덤 좌표 뽑아줄거임
	FNavLocation RandomLocation;
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.f/*범위*/, RandomLocation))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("PatrolPos")), RandomLocation.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
