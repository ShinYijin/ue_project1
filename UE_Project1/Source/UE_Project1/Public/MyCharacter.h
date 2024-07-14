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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// TODO
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

public:
	// bind axis function
	void UpDown(float Value);
	void LeftRight(float Value);
	void Yaw(float Value);

	// bind action function
	void Attack();

	// delegate functions
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

};
