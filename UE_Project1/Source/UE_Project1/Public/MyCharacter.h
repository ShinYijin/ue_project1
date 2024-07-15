// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"


UCLASS()
class UE_PROJECT1_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// TODO
public:
	// Blend Space
	UPROPERTY(VisibleAnywhere)
	float UpDownValue = 0;
	UPROPERTY(VisibleAnywhere)
	float LeftRightValue = 0;

private:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;
	UPROPERTY()
	class UMyAnimInstance* AnimInstance;


private:
	UPROPERTY(VisibleAnywhere, Category = "Pawn")
	bool IsAttacking = false;

	// 애니메이션 섹션 실습
	UPROPERTY()
	int32 AttackIndex = 0;

	// 소켓에 무기 붙이기 실습 
	UPROPERTY(VisibleAnywhere, Category = "Pawn")
	UStaticMeshComponent* Weapon;

public:
	// bind axis function
	void UpDown(float Value);
	void LeftRight(float Value);
	void Yaw(float Value);

	// bind action function
	void Attack();

	// bind delegate function (for collition)
	void AttackCheck();

	// delegate functions
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

};
