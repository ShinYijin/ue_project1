// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWeapon.h"

//TODO
#include "Components/BoxComponent.h"
#include "MyCharacter.h"

// Sets default values
AMyWeapon::AMyWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;	// tick�� �ʿ�����ϱ� ����. 

	// ���� �޽� ������Ʈ ���� �� ���� 
	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEAPON"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SW(TEXT("/Script/Engine.StaticMesh'/Game/ParagonGreystone/FX/Meshes/Heroes/Greystone/SM_Greystone_Blade_01.SM_Greystone_Blade_01'"));
	if (SW.Succeeded())
	{
		Weapon->SetStaticMesh(SW.Object);
	}

	// Ʈ���� ������Ʈ ���� �� ���� 
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Trigger->SetBoxExtent(FVector(30.f, 30.f, 30.f)); 
	
	// ������Ʈ���� �������� ���� 
	Weapon->SetupAttachment(RootComponent);
	Trigger->SetupAttachment(Weapon);

	// �浹 ����
	Weapon->SetCollisionProfileName(TEXT("MyCollectible"));
	Trigger->SetCollisionProfileName(TEXT("MyCollectible"));

}

// Called when the game starts or when spawned
void AMyWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyWeapon::PostInitializeComponents()
{
	// BeginPlay���� ��� ������Ʈ���� �ʱ�ȭ�� �Ϸ�� ����. 

	Super::PostInitializeComponents();

	// Trigger�� �浹�� �����Ѱ��(������ ������ ���۵Ǹ�) ������ �Լ� ����. 
	// delegate�� ����ϴ� ���̱� ������ OnComponentBeginOverlap ������ �������.  
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMyWeapon::OnCharacterOverlap);
}

void AMyWeapon::OnCharacterOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor /*���� �浹�� ��� Actor*/ , UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// My Character�� ���⸦ �ֿ�� �´��� Ȯ���ϱ� 
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor); // Cast()�̰� ���̳��� �ɽ�Ʈ�� ����ϴ�. ĳ������ �ȵǸ� �׳� null�� ��ȯ��. 
	if (MyCharacter)
	{
		FName WeaponSocket(TEXT("hand_l_socket"));
		UE_LOG(LogTemp, Warning, TEXT("OnCharacterOverlap"));

		// ���� �浹�ؿ� ���޽�(MyCharacter�� ���Ͽ� ����) 
		AttachToComponent(MyCharacter->GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			WeaponSocket);
	}
}

