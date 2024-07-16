// Fill out your copyright notice in the Description page of Project Settings.


#include "MyStatComponent.h"

// TODO 
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMyStatComponent::UMyStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false; // tick 마다 뭔가 할 필요는 없는 컴포넌트
	bWantsInitializeComponent = true;	// InitializeComponent를 사용하기 위해 이걸 true로 해줘야함

	Level = 1;
	// 나머지 데이터는 읽어올거임. 
}


// Called when the game starts
void UMyStatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UMyStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetLevel(Level);
}

void UMyStatComponent::SetLevel(int32 NewLevel)
{
	// 현재 플레이어의 레벨에 해당하는 데이터 가져와서 세팅하기. (각 레벨마다 설정해둔 maxhp랑 공격력이 있을거아냐)

	auto MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (MyGameInstance)
	{
		auto StatData = MyGameInstance->GetStatData(NewLevel);
		if (StatData)
		{
			NewLevel = StatData->Level;
			SetHp(Hp = StatData->MaxHP);
			MaxHp = StatData->MaxHP;
			Attack = StatData->Attack;
		}
	}
}

void UMyStatComponent::SetHp(int32 NewHp)
{
	Hp += NewHp;
	if (Hp < 0) Hp = 0;

	// HpBar UI연동이 필요함->델리게이트로 처리할 것이다. 구독하고 있던 모든 객체에게 신호가 가도록 
	OnHpChange.Broadcast();


}

void UMyStatComponent::OnAttacked(float DamageAmount)
{
	SetHp(Hp - DamageAmount);

	UE_LOG(LogTemp, Warning, TEXT("OnAttacked %d"), Hp);

}

