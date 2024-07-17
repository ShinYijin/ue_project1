// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attak.h"

// TODO 
#include "MyCharacter.h"
#include "MyAIController.h"

UBTTask_Attak::UBTTask_Attak()
{
	// task node name 설정
	NodeName = TEXT("Attack");

	// TickTack가 실행되도록 설정
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Attak::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Task가 발생하면 실행
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto MyCharacter = Cast<AMyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (MyCharacter == nullptr) 
		return EBTNodeResult::Failed;

	MyCharacter->Attack();
	bIsAttacking = true; 


	/* 공격이 끝나면 bIsAttacking를 false로 꺼줘야하는데 이건 누가할까?
	공격은 몽타주 애니메이션으로 만들었었고, 그 몽타주는 MyCharacter에서 OnAttackMontageEnded라는 함수에서 몽타주가 끝나는
	감지하고 있었다. 그러니까 거기서 false로 내려주면됨. 
		여기서 또 두가지 선택지가 있음. 
		1. MyCharacter에서 이 TaskNode클래스에 접근을 시도해서 bIsAttacking을 바꿔줘도 되고
		2. MyCharacter쪽에서 delegate를 만들고, 이 Task가 구독한 다음, Attack몽타주 종료시 브로드케스트 날린걸 여기서 잡아도되고. 리스너 패턴 사용해도되고. (이걸로 할거임)*/

	// MyCharacter의 OnAttackEnd델리게이트 구독신청하기 
	MyCharacter->OnAttackEnd.AddLambda([this]() 
		{
			bIsAttacking = false;
		});

	return Result;
}

void UBTTask_Attak::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// Tick마다 실행
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	//  공격이 끝났으면 이 task를 종료 처리 하기 
	if (bIsAttacking == false)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}
