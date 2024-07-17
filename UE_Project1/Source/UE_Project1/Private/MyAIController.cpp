// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"

// TODO
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


AMyAIController::AMyAIController()
{
}

void AMyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// �ϰ��� ���
	GetWorld()->GetTimerManager().SetTimer(TimerHandle/*�ڵ� ���*/, this, &AMyAIController::RandomMove, 3.f, true);
}

void AMyAIController::OnUnPossess()
{
	Super::OnUnPossess();

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
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
