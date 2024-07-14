// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

//#include "MyPawn.h"
#include "MyCharacter.h"

AMyGameModeBase::AMyGameModeBase()
{
	// ����Ʈ ���� ���� ���� �� Ŭ������ �ٲ��ֱ� 
	//DefaultPawnClass = AMyPawn::StaticClass();
	//DefaultPawnClass = AMyCharacter::StaticClass();

	// ����Ʈ ���� �������Ʈ Ŭ������ �ٲ��ֱ� 
	// ����: ��� �����ؿ��� �� �Ȱ����� ����  _C�� �� �ٿ��� �Ѵ�. �׳� �𸮾� ��Ģ��. 
	static ConstructorHelpers::FClassFinder<ACharacter> BP_Character(TEXT("/Script/Engine.Blueprint'/Game/BluePrints/BP_MyCharacter.BP_MyCharacter_C'"));
	if (BP_Character.Succeeded())
		DefaultPawnClass = BP_Character.Class;
	else
		UE_LOG(LogTemp, Error, TEXT("Find BP Fail"));
}