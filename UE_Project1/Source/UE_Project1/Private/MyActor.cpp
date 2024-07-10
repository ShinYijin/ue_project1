// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
//#include "Components/StaticMeshComponent.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 1. 메쉬 컴포넌트 붙여보기 
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH")); // 이거 이름은 헤쉬값같은것. 겹치지 않게해야함. 
	// TEXT()는 L""으로 바궈주는건데 이거 알지? 윈도우에서 쓰는 타입 그거 인거같음. 크로스플렛폼을 고려한. 

	// 2. 리소스 로드해서 아예 이 클래스에 박아버리는 실습 
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_Chair.SM_Chair'"/*메쉬 리소스 경로*/));
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

