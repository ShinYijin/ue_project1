// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"

// TODO
#include "Components/ProgressBar.h"

#include "MyStatComponent.h"


void UMyUserWidget::BindHp(class UMyStatComponent* StatComp)
{
	CurrentStatComponent = StatComp;

	// StatComp�� ����ִ� ��������Ʈ �߿� HP������ ��ε��ɽ�Ʈ ������ ������ ��������Ʈ �Լ� ����
	StatComp->OnHpChange.AddUObject(this, &UMyUserWidget::UpdateHp);


}

void UMyUserWidget::UpdateHp()
{
	if (CurrentStatComponent.IsValid())
		PB_HpBar->SetPercent(CurrentStatComponent->GetHpRatio());
}
