// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

// Delegate declear
DECLARE_MULTICAST_DELEGATE(FOnAttackHit); 


UCLASS()
class UE_PROJECT1_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

// TODO
public:
	UMyAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
public:
	// 애니메이션 몽타주 플레이 
	void PlayAttackMontage();

	// 애니메이션 몽타주 섹션 플레이
	FName GetAttackMontageName(int32 SectionIndex);
	void JumpToSection(int32 SectionIndex);

private:
	// 애니메이션 노티파이 
	UFUNCTION()
	void AnimNotify_AttackHit(); // 이름 규칙있음. 

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", Meta=(AllowPrivateAccess=true))
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", Meta = (AllowPrivateAccess = true))
	bool IsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", Meta = (AllowPrivateAccess = true))
	float Horizontal;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", Meta = (AllowPrivateAccess = true))
	float Vertical;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pawn", Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;	// 생성자에서 세팅함. 

public: 
	// collition
	FOnAttackHit OnAttackHit;
};
