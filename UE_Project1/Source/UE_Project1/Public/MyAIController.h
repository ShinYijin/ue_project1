// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class UE_PROJECT1_API AMyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMyAIController();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
 	
private:
	void RandomMove();

private:
	FTimerHandle TimerHandle;

private:
	// Behavior tree
	UPROPERTY(VisibleAnywhere)
	class UBehaviorTree* BehaviorTree;
	UPROPERTY(VisibleAnywhere)
	class UBlackboardData* BlackboardData;
};
