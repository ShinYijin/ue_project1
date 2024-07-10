// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

#include "GameFramework/FloatingPawnMovement.h" 

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 1. �޽� ������Ʈ �ٿ����� 
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH")); // �̰� �̸��� �콬��������. ��ġ�� �ʰ��ؾ���. 
	// TEXT()�� L""���� �ٱ��ִ°ǵ� �̰� ����? �����쿡�� ���� Ÿ�� �װ� �ΰŰ���. ũ�ν��÷����� �����. 

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT")); // �̰� �̸��� �콬��������. ��ġ�� �ʰ��ؾ���. 

// 2. ���ҽ� �ε��ؼ� �ƿ� �� Ŭ������ �ھƹ����� �ǽ� 
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_Chair.SM_Chair'"/*�޽� ���ҽ� ���*/));

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

