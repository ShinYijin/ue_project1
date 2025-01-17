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
* 이 함수는 내가 이름을 지어서 만든 게 아니다.
* 언리얼은 인풋 관련 함수 실행 > 컨텐츠 로직 실행 > 애님 인스턴스의 업데이트 함수 호출 이렇게 진행한다.
* NativeUpdateAnimation가 애님 인스턴스의 업데이트 함수이다. 쉽게 말해 한 프레임에 여기 한번 들어온다. 
*/
void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// 이 컴포넌트가 붙어있는 주인 Pawn을 가져오기
	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{	// velocity는 pawn에 기본적으로 들어있음. 내가 만든게 아니라. 
		Speed = Pawn->GetVelocity().Size();	

		
		auto Character = Cast<AMyCharacter>(Pawn);
		if (Character)
		{	// isFalling 정도는 언리얼에서 제공함. 
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
	//UE_LOG(LogTemp, Warning, TEXT("NOTIFY_AttackHit"));
	OnAttackHit.Broadcast();
}
