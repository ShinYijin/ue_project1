// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS() // 이런거 뭐 하는 얘냐면, C++에는 원래 Reflection이 없었는데, 그 역할을 할 수 있게 하는것. 
/* Reflection은 컴파일러가 읽을 수 있는 주석임.런타임에 여기에 기입한 정보(클래스의 메타 데이터)를 추출해서 사용할 수 있다.
 한마디로 이건 그냥 언리얼측에서 reflection 기능을 만들어주는 거임. 이건 언리얼측에서 제작한 빌드 툴이 해석하는 것. */
class UE_PROJECT1_API AMyActor : public AActor // UE_PROJECT1_API: 빌드할 때 사용되는 모듈 / Actor앞에 A가 붙은건 그냥 언리얼에서 정한 네이밍 컨벤션 
{
	GENERATED_BODY() // 야가 UCLASS()와 짝꿍임. 
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


// TODO

private:

	UPROPERTY(VisibleAnywhere) // "이 프로퍼티는 언리얼에서 자동으로 관리하는 메모리다" 라는 의미. -> 이게 붙으면 그냥 new로 생성못하고 CreateDefaultSubObject라는 함수를 이용해서 객체 생성해야함. 
		// VisibleAnywhere는 어디에서도 수정할 수 있도록 보여지게하는 것. UE에서 프로퍼티 내부 멤버 수정을 할 수 있게 하는 것 같음. 유니티 SerializeField같음. 
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category=BattleStat) // 이건 visible만해서는 ue에서 바로 수정은 안됨. editanywhere로 해야함
	int32 Hp;
	UPROPERTY(EditAnywhere, Category = BattleStat)
	int32 Mp;
	UPROPERTY(EditAnywhere, Category = BattleStat)
	float RotateSpeed = 30.f;

};
