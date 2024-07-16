// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"

// TODO
#include "Components/ProgressBar.h"

#include "MyStatComponent.h"


void UMyUserWidget::BindHp(class UMyStatComponent* StatComp)
{
	CurrentStatComponent = StatComp;

	// StatComp가 들고있는 델리게이트 중에 HP변동시 브로드케스트 날리는 놈한테 델리게이트 함수 연결
	StatComp->OnHpChange.AddUObject(this, &UMyUserWidget::UpdateHp);


}

void UMyUserWidget::UpdateHp()
{
	if (CurrentStatComponent.IsValid())
		PB_HpBar->SetPercent(CurrentStatComponent->GetHpRatio());
}
