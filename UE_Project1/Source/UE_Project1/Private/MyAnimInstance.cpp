// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"

// TODO
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

/*  
* �� �Լ��� ���� �̸��� ��� ���� �� �ƴϴ�.
* �𸮾��� ��ǲ ���� �Լ� ���� > ������ ���� ���� > �ִ� �ν��Ͻ��� ������Ʈ �Լ� ȣ�� �̷��� �����Ѵ�.
* NativeUpdateAnimation�� �ִ� �ν��Ͻ��� ������Ʈ �Լ��̴�. ���� ���� �� �����ӿ� ���� �ѹ� ���´�. 
*/
void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// �� ������Ʈ�� �پ��ִ� ���� Pawn�� ��������
	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{	// velocity�� pawn�� �⺻������ �������. ���� ����� �ƴ϶�. 
		Speed = Pawn->GetVelocity().Size();	

		
		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{	// isFalling ������ �𸮾󿡼� ������. 
			IsFalling = Character->GetMovementComponent()->IsFalling();
		}
	}
}
