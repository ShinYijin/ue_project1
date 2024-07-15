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
	// �ִϸ��̼� ��Ÿ�� �÷��� 
	void PlayAttackMontage();

	// �ִϸ��̼� ��Ÿ�� ���� �÷���
	FName GetAttackMontageName(int32 SectionIndex);
	void JumpToSection(int32 SectionIndex);

private:
	// �ִϸ��̼� ��Ƽ���� 
	UFUNCTION()
	void AnimNotify_AttackHit(); // �̸� ��Ģ����. 

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
	UAnimMontage* AttackMontage;	// �����ڿ��� ������. 

public: 
	// collition
	FOnAttackHit OnAttackHit;
};
