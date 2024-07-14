// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

//#include "MyPawn.h"
#include "MyCharacter.h"

AMyGameModeBase::AMyGameModeBase()
{
	// 디폴트 폰을 내가 만든 폰 클래스로 바꿔주기 
	//DefaultPawnClass = AMyPawn::StaticClass();
	//DefaultPawnClass = AMyCharacter::StaticClass();

	// 디폴트 폰을 블루프린트 클래스로 바꿔주기 
	// 주의: 경로 복사해오는 건 똑같은데 끝에  _C를 꼭 붙여야 한다. 그냥 언리얼 규칙임. 
	static ConstructorHelpers::FClassFinder<ACharacter> BP_Character(TEXT("/Script/Engine.Blueprint'/Game/BluePrints/BP_MyCharacter.BP_MyCharacter_C'"));
	if (BP_Character.Succeeded())
		DefaultPawnClass = BP_Character.Class;
	else
		UE_LOG(LogTemp, Error, TEXT("Find BP Fail"));
}