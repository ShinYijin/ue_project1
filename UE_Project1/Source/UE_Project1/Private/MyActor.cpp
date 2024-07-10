// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
//#include "Components/StaticMeshComponent.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 1. �޽� ������Ʈ �ٿ����� 
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH")); // �̰� �̸��� �콬��������. ��ġ�� �ʰ��ؾ���. 
	// TEXT()�� L""���� �ٱ��ִ°ǵ� �̰� ����? �����쿡�� ���� Ÿ�� �װ� �ΰŰ���. ũ�ν��÷����� �����. 

	// 2. ���ҽ� �ε��ؼ� �ƿ� �� Ŭ������ �ھƹ����� �ǽ� 
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_Chair.SM_Chair'"/*�޽� ���ҽ� ���*/));
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

