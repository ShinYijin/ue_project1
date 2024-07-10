// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class UE_PROJECT1_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; 
		// ���Ϳ��� ����, ���� ��ӹ����� ����� �Լ�. �̰� �Է��� �޾Ƽ� �����̰� �ϴ� �κ��̴�. 

// TODO
private:

	UPROPERTY(VisibleAnywhere)	// "�� ������Ƽ�� �𸮾󿡼� �ڵ����� �����ϴ� �޸𸮴�" ��� �ǹ�. -> �̰� ������ �׳� new�� �������ϰ� CreateDefaultSubObject��� �Լ��� �̿��ؼ� ��ü �����ؾ���. 
								// VisibleAnywhere�� ��𿡼��� ������ �� �ֵ��� ���������ϴ� ��. UE���� ������Ƽ ���� ��� ������ �� �� �ְ� �ϴ� �� ����. ����Ƽ SerializeField����. 
	UStaticMeshComponent* Mesh;
	
	// ��� CoreMinimal.h�� ���ԵǾ����� �ʾƼ� ���� include�������
	UPROPERTY(VisibleAnywhere)
	class UFloatingPawnMovement* Movement;
	
	UPROPERTY(EditAnywhere, Category = BattleStat) // �̰� visible���ؼ��� ue���� �ٷ� ������ �ȵ�. editanywhere�� �ؾ���
		int32 Hp;
	UPROPERTY(EditAnywhere, Category = BattleStat)
	int32 Mp;
	UPROPERTY(EditAnywhere, Category = BattleStat)
	float RotateSpeed = 30.f;

	

public:
	void UpDown(float Value);
	void LeftRight(float Value);
};
