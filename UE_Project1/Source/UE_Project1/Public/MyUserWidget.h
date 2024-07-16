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
	void BindHp(class UMyStatComponent* StatComp); // stat component가 정보를 들고있으니 그냥 얘를 바인딩해주기. 꼭 이런 방법만 있는건 당연히 아님. 

private:
	TWeakObjectPtr<class UMyStatComponent> CurrentStatComponent;///스마트 포인터로 들고있겠다는 거임. 
	
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_HpBar;	// 이름을 블루프린트에서 해둔것과 똑같이 하고, 위에 메타를 bindwidget으로 작성하면 알아서 찾아서 바인딩해줌.

private:

	void UpdateHp();
};
 