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

	if (SM.Succeeded())
	{
		Mesh->SetStaticMesh(SM.Object);
	}
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	// [로그 찍기] 
	// 카테고리, 로깅 수준, 형식, 인자 (로그 수준에 따라 파일에 출력할 로그를 따로 작성할 수도 있음. Saved>Logs폴더에 우리가 찍은 로그 남아있음)
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay %d"), 3);

}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//[로그 찍기]
	//UE_LOG(LogTemp, Error, TEXT("Tick %f"), DeltaTime);

	// 회전하기
	AddActorLocalRotation(FRotator(0.f, RotateSpeed * DeltaTime, 0.f));
}

