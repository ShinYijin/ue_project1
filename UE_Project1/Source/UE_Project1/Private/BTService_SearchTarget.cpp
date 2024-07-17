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

	// TickNode�� ����� �ֱ⸦ ����
	Interval = 1.0f;
}

void UBTService_SearchTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// Ÿ���� �ִ��� Ȯ�� (���� �����̴ϱ� �÷��̾ �����ϴ��� Ȯ���ϸ��.)
	auto CurrentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (CurrentPawn == nullptr)
		return;

	UWorld* World = CurrentPawn->GetWorld(); // ������ �ִ� world�� ������� ���ϱ� 
	if (World == nullptr)
		return;
	FVector Center = CurrentPawn->GetActorLocation();// ������ ��ġ �������� 
	float SearchRadius = 500.f;				// ��Ī �ݰ� ���ϱ�\

	/* �浹 �ý����� �̿��ؼ� �����Ұ���.*/
	TArray<FOverlapResult> OverlapResults; // �浹 �׽�Ʈ ����� �޾ƿ� ����
	FCollisionQueryParams QueryParams(NAME_None, false, CurrentPawn);// ���Ͱ� �����θ� ã�°� �����ϵ��� IgnoreActor�� currentpawn(�� �ڽ�)�� ����. 
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults, 
		Center, // ���� ��ġ 
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(SearchRadius),
		QueryParams
		);

	if (bResult)
	{
		for (auto& OverlapResult : OverlapResults)
		{
			// �ϴ� ������ ���Ͱ� �����Ұ� ���ۿ� �����ϱ� MyCharacterŸ������ �ɽ���
			AMyCharacter* MyCharacter = Cast<AMyCharacter>(OverlapResult.GetActor());
			// ��¥ �÷��̾����� ����üũ 
			if (MyCharacter && MyCharacter->GetController()->IsPlayerController())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("Target")/*�����忡�� ������� ������*/, MyCharacter);

				DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Green, false, 0.2f);

				return;
			}
		}
		DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Red, false, 0.2f);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName("Target")/*�����忡�� ������� ������*/, nullptr);
		DrawDebugSphere(World, Center, SearchRadius, 16, FColor::Red, false, 0.2f);
	}

}
