// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"

// TODO
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MyCharacter.h"

UMyAnimInstance::UMyAnimInstance()
{
	// [Anim Montage setting]
	static ConstructorHelpers::FObjectFinder<UAnimMontage> AM(TEXT("/Script/Engine.AnimMontage'/Game/Animations/Greystone_Skeleton_Montage.Greystone_Skeleton_Montage'"));
	if (AM.Succeeded())
	{
		AttackMontage = AM.Object;
	}
}

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

		
		auto Character = Cast<AMyCharacter>(Pawn);
		if (Character)
		{	// isFalling ������ �𸮾󿡼� ������. 
			IsFalling = Character->GetMovementComponent()->IsFalling();

			// Blend Space 
			Vertical = Character->UpDownValue;
			Horizontal = Character->LeftRightValue;
		}
	}
}

void UMyAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, 1.f);	
	}
}

FName UMyAnimInstance::GetAttackMontageName(int32 SectionIndex)
{
	return FName(*FString::Printf(TEXT("Attack%d"), SectionIndex));
}

void UMyAnimInstance::JumpToSection(int32 SectionIndex)
{
	FName Name = GetAttackMontageName(SectionIndex);
	Montage_JumpToSection(Name, AttackMontage);
}

void UMyAnimInstance::AnimNotify_AttackHit()
{
	UE_LOG(LogTemp, Warning, TEXT("NOTIFY_AttackHit"));
}
