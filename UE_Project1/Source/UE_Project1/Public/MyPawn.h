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
		// 엑터에는 없고, 폰을 상속받으면 생기는 함수. 이게 입력을 받아서 움직이게 하는 부분이다. 

// TODO
private:

	UPROPERTY(VisibleAnywhere)	// "이 프로퍼티는 언리얼에서 자동으로 관리하는 메모리다" 라는 의미. -> 이게 붙으면 그냥 new로 생성못하고 CreateDefaultSubObject라는 함수를 이용해서 객체 생성해야함. 
								// VisibleAnywhere는 어디에서도 수정할 수 있도록 보여지게하는 것. UE에서 프로퍼티 내부 멤버 수정을 할 수 있게 하는 것 같음. 유니티 SerializeField같음. 
	UStaticMeshComponent* Mesh;
	
	// 얘는 CoreMinimal.h에 포함되어있지 않아서 직접 include해줘야함
	UPROPERTY(VisibleAnywhere)
	class UFloatingPawnMovement* Movement;
	
	UPROPERTY(EditAnywhere, Category = BattleStat) // 이건 visible만해서는 ue에서 바로 수정은 안됨. editanywhere로 해야함
		int32 Hp;
	UPROPERTY(EditAnywhere, Category = BattleStat)
	int32 Mp;
	UPROPERTY(EditAnywhere, Category = BattleStat)
	float RotateSpeed = 30.f;

	

public:
	void UpDown(float Value);
	void LeftRight(float Value);
};
