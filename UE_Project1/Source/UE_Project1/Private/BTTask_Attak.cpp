// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attak.h"

// TODO 
#include "MyCharacter.h"
#include "MyAIController.h"

UBTTask_Attak::UBTTask_Attak()
{
	// task node name ����
	NodeName = TEXT("Attack");

	// TickTack�� ����ǵ��� ����
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Attak::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Task�� �߻��ϸ� ����
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto MyCharacter = Cast<AMyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (MyCharacter == nullptr) 
		return EBTNodeResult::Failed;

	MyCharacter->Attack();
	bIsAttacking = true; 


	/* ������ ������ bIsAttacking�� false�� ������ϴµ� �̰� �����ұ�?
	������ ��Ÿ�� �ִϸ��̼����� ���������, �� ��Ÿ�ִ� MyCharacter���� OnAttackMontageEnded��� �Լ����� ��Ÿ�ְ� ������
	�����ϰ� �־���. �׷��ϱ� �ű⼭ false�� �����ָ��. 
		���⼭ �� �ΰ��� �������� ����. 
		1. MyCharacter���� �� TaskNodeŬ������ ������ �õ��ؼ� bIsAttacking�� �ٲ��൵ �ǰ�
		2. MyCharacter�ʿ��� delegate�� �����, �� Task�� ������ ����, Attack��Ÿ�� ����� ��ε��ɽ�Ʈ ������ ���⼭ ��Ƶ��ǰ�. ������ ���� ����ص��ǰ�. (�̰ɷ� �Ұ���)*/

	// MyCharacter�� OnAttackEnd��������Ʈ ������û�ϱ� 
	MyCharacter->OnAttackEnd.AddLambda([this]() 
		{
			bIsAttacking = false;
		});

	return Result;
}

void UBTTask_Attak::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// Tick���� ����
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	//  ������ �������� �� task�� ���� ó�� �ϱ� 
	if (bIsAttacking == false)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}
