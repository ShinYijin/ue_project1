// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

// TODO 

/**
 * 
 */
UCLASS()
class UE_PROJECT1_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindHp(class UMyStatComponent* StatComp); // stat component�� ������ ��������� �׳� �긦 ���ε����ֱ�. �� �̷� ����� �ִ°� �翬�� �ƴ�. 

private:
	TWeakObjectPtr<class UMyStatComponent> CurrentStatComponent;///����Ʈ �����ͷ� ����ְڴٴ� ����. 
	
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_HpBar;	// �̸��� �������Ʈ���� �صаͰ� �Ȱ��� �ϰ�, ���� ��Ÿ�� bindwidget���� �ۼ��ϸ� �˾Ƽ� ã�Ƽ� ���ε�����.

private:

	void UpdateHp();
};
 