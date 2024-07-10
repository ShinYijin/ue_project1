// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS() // �̷��� �� �ϴ� ��ĸ�, C++���� ���� Reflection�� �����µ�, �� ������ �� �� �ְ� �ϴ°�. 
/* Reflection�� �����Ϸ��� ���� �� �ִ� �ּ���.��Ÿ�ӿ� ���⿡ ������ ����(Ŭ������ ��Ÿ ������)�� �����ؼ� ����� �� �ִ�.
 �Ѹ���� �̰� �׳� �𸮾������� reflection ����� ������ִ� ����. �̰� �𸮾������� ������ ���� ���� �ؼ��ϴ� ��. */
class UE_PROJECT1_API AMyActor : public AActor // UE_PROJECT1_API: ������ �� ���Ǵ� ��� / Actor�տ� A�� ������ �׳� �𸮾󿡼� ���� ���̹� ������ 
{
	GENERATED_BODY() // �߰� UCLASS()�� ¦����. 
	
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

	UPROPERTY(VisibleAnywhere) // "�� ������Ƽ�� �𸮾󿡼� �ڵ����� �����ϴ� �޸𸮴�" ��� �ǹ�. -> �̰� ������ �׳� new�� �������ϰ� CreateDefaultSubObject��� �Լ��� �̿��ؼ� ��ü �����ؾ���. 
		// VisibleAnywhere�� ��𿡼��� ������ �� �ֵ��� ���������ϴ� ��. UE���� ������Ƽ ���� ��� ������ �� �� �ְ� �ϴ� �� ����. ����Ƽ SerializeField����. 
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category=BattleStat) // �̰� visible���ؼ��� ue���� �ٷ� ������ �ȵ�. editanywhere�� �ؾ���
	int32 Hp;
	UPROPERTY(EditAnywhere, Category = BattleStat)
	int32 Mp;
	UPROPERTY(EditAnywhere, Category = BattleStat)
	float RotateSpeed = 30.f;

};
