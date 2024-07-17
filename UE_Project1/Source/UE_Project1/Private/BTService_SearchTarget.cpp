// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_SearchTarget.h"

// TODO
#include "MyCharacter.h"
#include "MyAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/OverlapResult.h"

#include "DrawDebugHelpers.h"

UBTService_SearchTarget::UBTService_SearchTarget()
{
	NodeName = TEXT("SearchTarget");

	// TickNode가 실행될 주기를 설정
	Interval = 1.0f;
}

void UBTService_SearchTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// 타겟이 있는지 확인 (몬스터 입장이니까 플레이어가 존재하는지 확인하면됨.)
	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (CurrentPawn == nullptr)
		return;

	UWorld* World = CurrentPawn->GetWorld(); // 본인이 있는 world가 어디인지 구하기 
	if (World == nullptr)
		return;
	FVector Center = CurrentPawn->GetActorLocation();// 본인의 위치 가져오기 
	float SearchRadius = 500.f;				// 서칭 반경 정하기\

	/* 충돌 시스템을 이용해서 감지할거임.*/
	TArray<FOverlapResult> OverlapResults; // 충돌 테스트 결과를 받아올 변수
	FCollisionQueryParams QueryParams(NAME_None, false, CurrentPawn);// 몬스터가 스스로를 찾는건 제외하도록 IgnoreActor로 currentpawn(나 자신)을 설정. 
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults, 
		Center, // 현재 위치 
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(SearchRadius),
		QueryParams
		);

	if (bResult)
	{
		for (auto& OverlapResult : OverlapResults)
		{
			// 일단 지금은 몬스터가 감지할게 나밖에 없으니까 MyCharacter타입으로 케스팅
			AMyCharacter* MyCharacter = Cast<AMyCharacter>(OverlapResult.GetActor());
			// 진짜 플레이어인지 더블체크 
			if (MyCharacter && MyCharacter->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("Target")/*블랙보드에서 만들어준 변수명*/, MyCharacter);

				DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Green, false, 0.2f);

				return;
			}
		}
		DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Red, false, 0.2f);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("Target")/*블랙보드에서 만들어준 변수명*/, nullptr);
		DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Red, false, 0.2f);
	}

}
