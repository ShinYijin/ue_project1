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

	/* �ϰ��� ��� (�����̺�� Ʈ�� �����ϴ� ��� �̷��� ���� �ڵ� �ۼ��ص� ��.)*/
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle/*�ڵ� ���*/, this, &AMyAIController::RandomMove, 3.f, true);

	/* Behavior tree�� ����ϴ� ���*/
	// ����� ������ ����
	UBlackboardComponent* BlackboardComp = Blackboard;
	if (UseBlackboard(BlackboardData, BlackboardComp)) // BlackBoard�� AI ControllerŬ������ �⺻ �����. 
	{	// ����� �����̺�� Ʈ�� ���� 
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

	/* �����̺�� Ʈ�� �����ϴ� ��� ����ߴ� Ÿ�̸� ����*/
	//GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void AMyAIController::RandomMove()
{
	auto CurrentPawn = GetPawn();

	// �׺���̼� �޽��� �ʿ���. �����ִ� ���� ���� �˼� �־�ߵǴϱ�. 
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (NavSystem == nullptr)
		return;

	// �� ��ġ�κ��� ������ ���� ��ǥ �̾��ٰ���
	FNavLocation RandomLocation;
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.f/*����*/, RandomLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, RandomLocation);
	}
}
