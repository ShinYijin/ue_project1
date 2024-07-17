// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"

// TODO
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

AMyAIController::AMyAIController()
{
	struct ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Script/AIModule.BehaviorTree'/Game/AI/BT_MyCharacter.BT_MyCharacter'"));
	if (BT.Succeeded())
	{
		BehaviorTree = BT.Object;
	}
	struct ConstructorHelpers::FObjectFinder<UBlackboardData> BD(TEXT("/Script/AIModule.BlackboardData'/Game/AI/BB_MyCharacter.BB_MyCharacter'"));
	if (BD.Succeeded())
	{
		BlackboardData = BD.Object;
	}
}

void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	/* 일감을 등록 (비헤이비어 트리 사용안하는 경우 이렇게 냅다 코드 작성해도 됨.)*/
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle/*핸들 등록*/, this, &AMyAIController::RandomMove, 3.f, true);

	/* Behavior tree를 사용하는 경우*/
	// 사용할 블랙보드 설정
	UBlackboardComponent* BlackboardComp = Blackboard;
	if (UseBlackboard(BlackboardData, BlackboardComp)) // BlackBoard는 AI Controller클래스의 기본 멤버임. 
	{	// 사용할 비헤이비어 트리 설정 
		if (RunBehaviorTree(BehaviorTree))
		{
			// TODO 
			UE_LOG(LogTemp, Warning, TEXT("Run Behavior tree"));
		}
	}
}

void AMyAIController::OnUnPossess()
{
	Super::OnUnPossess();

	/* 비헤이비어 트리 사용안하는 경우 사용했던 타이머 해제*/
	//GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void AMyAIController::RandomMove()
{
	auto CurrentPawn = GetPawn();

	// 네비게이션 메쉬가 필요함. 갈수있는 길이 뭔지 알수 있어야되니까. 
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (NavSystem == nullptr)
		return;

	// 내 위치로부터 인접한 랜덤 좌표 뽑아줄거임
	FNavLocation RandomLocation;
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.f/*범위*/, RandomLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, RandomLocation);
	}
}
