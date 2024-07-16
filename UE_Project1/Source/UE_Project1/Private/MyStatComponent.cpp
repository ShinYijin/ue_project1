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
	PrimaryComponentTick.bCanEverTick = false; // tick ���� ���� �� �ʿ�� ���� ������Ʈ
	bWantsInitializeComponent = true;	// InitializeComponent�� ����ϱ� ���� �̰� true�� �������

	Level = 1;
	// ������ �����ʹ� �о�ð���. 
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
	// ���� �÷��̾��� ������ �ش��ϴ� ������ �����ͼ� �����ϱ�. (�� �������� �����ص� maxhp�� ���ݷ��� �����žƳ�)

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

	// HpBar UI������ �ʿ���->��������Ʈ�� ó���� ���̴�. �����ϰ� �ִ� ��� ��ü���� ��ȣ�� ������ 
	OnHpChange.Broadcast();


}

void UMyStatComponent::OnAttacked(float DamageAmount)
{
	SetHp(Hp - DamageAmount);

	UE_LOG(LogTemp, Warning, TEXT("OnAttacked %d"), Hp);

}
