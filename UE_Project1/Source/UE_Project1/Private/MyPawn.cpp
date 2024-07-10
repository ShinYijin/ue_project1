// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

#include "GameFramework/FloatingPawnMovement.h" 

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 1. 메쉬 컴포넌트 붙여보기 
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH")); // 이거 이름은 헤쉬값같은것. 겹치지 않게해야함. 
	// TEXT()는 L""으로 바궈주는건데 이거 알지? 윈도우에서 쓰는 타입 그거 인거같음. 크로스플렛폼을 고려한. 

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT")); // 이거 이름은 헤쉬값같은것. 겹치지 않게해야함. 

// 2. 리소스 로드해서 아예 이 클래스에 박아버리는 실습 
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_Chair.SM_Chair'"/*메쉬 리소스 경로*/));

	if (SM.Succeeded())
	{
		Mesh->SetStaticMesh(SM.Object);
	}
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyPawn::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyPawn::LeftRight);
}

void AMyPawn::UpDown(float Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("UpDown %f"), Value);

	if (Value == 0.f) return;

	AddMovementInput(GetActorForwardVector(), Value);
}

void AMyPawn::LeftRight(float Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("LeftRight %f"), Value);

	if (Value == 0.f) return;
	AddMovementInput(GetActorRightVector(), Value);
}

