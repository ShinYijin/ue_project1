// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

#include "MyPawn.h"

AMyGameModeBase::AMyGameModeBase()
{
	// 디폴트 폰을 내가 만든 폰 클래스로 바꿔주기 
	DefaultPawnClass = AMyPawn::StaticClass();
}