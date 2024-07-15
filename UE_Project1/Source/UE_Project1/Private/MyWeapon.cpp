// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWeapon.h"

//TODO
#include "Components/BoxComponent.h"
#include "MyCharacter.h"

// Sets default values
AMyWeapon::AMyWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;	// tick이 필요없으니까 끈다. 

	// 무기 메쉬 컴포넌트 생성 및 세팅 
	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEAPON"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SW(TEXT("/Script/Engine.StaticMesh'/Game/ParagonGreystone/FX/Meshes/Heroes/Greystone/SM_Greystone_Blade_01.SM_Greystone_Blade_01'"));
	if (SW.Succeeded())
	{
		Weapon->SetStaticMesh(SW.Object);
	}

	// 트리거 컴포넌트 생성 및 세팅 
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Trigger->SetBoxExtent(FVector(30.f, 30.f, 30.f)); 
	
	// 컴포넌트들의 계층구조 설정 
	Weapon->SetupAttachment(RootComponent);
	Trigger->SetupAttachment(Weapon);

	// 충돌 설정
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
	// BeginPlay에서 모든 컴포넌트들의 초기화가 완료된 시점. 

	Super::PostInitializeComponents();

	// Trigger가 충돌을 인지한경우(오버랩 반응이 시작되면) 실행할 함수 맵핑. 
	// delegate를 사용하는 것이기 때문에 OnComponentBeginOverlap 형식을 따라야함.  
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMyWeapon::OnCharacterOverlap);
}

void AMyWeapon::OnCharacterOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor /*나랑 충돌한 상대 Actor*/ , UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// My Character가 무기를 주운게 맞는지 확인하기 
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(OtherActor); // Cast()이건 다이나믹 케스트랑 비슷하다. 캐스팅이 안되면 그냥 null을 반환함. 
	if (MyCharacter)
	{
		FName WeaponSocket(TEXT("hand_l_socket"));
		UE_LOG(LogTemp, Warning, TEXT("OnCharacterOverlap"));

		// 나를 충돌해온 상대메쉬(MyCharacter의 소켓에 붙임) 
		AttachToComponent(MyCharacter->GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			WeaponSocket);
	}
}

