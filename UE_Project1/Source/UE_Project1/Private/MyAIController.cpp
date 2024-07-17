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

	// 일감을 등록
	GetWorld()->GetTimerManager().SetTimer(TimerHandle/*핸들 등록*/, this, &AMyAIController::RandomMove, 3.f, true);
}

void AMyAIController::OnUnPossess()
{
	Super::OnUnPossess();

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
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
