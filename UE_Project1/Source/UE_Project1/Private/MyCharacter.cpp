// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

// TODO 
// [Component]
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"// GetCapsuleComponent()를 사용하기 위함. 
										// 이걸 안쓰면 아마 CapsuleComponent라는 타입을 잘 몰라서 자동 형변환이 안되는 듯. 그래서 SpringArm->SetupAttachment(GetCapsuleComponent()); 에서 오류남. 
#include "MyAnimInstance.h"
#include "MyWeapon.h"

#include "DrawDebugHelpers.h" // 디버깅하기 편하게 도와주는 라이브러리 

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// [메쉬 로드]
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"/*메쉬 리소스 경로*/));
	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}
	
	// [Component setting]
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	// [Setting Root]
	// 컴포넌트의  부모 컴포넌트를 설정해줌. 부모가 그냥 이 객체자체가 아니라 이 객체가 들고있는 컴포넌트로 설정되어야하나봄. 
	SpringArm->SetupAttachment(GetCapsuleComponent()); 
	Camera->SetupAttachment(SpringArm);

	// [Setting Spring Arm]
	SpringArm->TargetArmLength = 500.f; // 셀카봉의 길이 
	SpringArm->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));	// 셀카봉의 각도 

	// [Mesh local transform setting]
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	// 소켓에 무기 붙이기(무기를 따로 엑터 클래스로 관리하지 않는 경우) 
	/*FName WeaponSocket(TEXT("hand_l_socket")); // 소켓 이름 변수 
	if (GetMesh()->DoesSocketExist(WeaponSocket)) // 소켓이 있는지 확인 
	{
		Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEAPON"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SW(TEXT("/Script/Engine.StaticMesh'/Game/ParagonGreystone/FX/Meshes/Heroes/Greystone/SM_Greystone_Blade_01.SM_Greystone_Blade_01'"));
		if (SW.Succeeded())
		{
			Weapon->SetStaticMesh(SW.Object);
		}
		// 우리가 원하는 소켓에 -> Weapon을 붙이기 
		Weapon->SetupAttachment(GetMesh(), WeaponSocket);
	}*/


}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 엑터 클래스로 관리되는 무기를 스폰해서 장착하는 경우 
	/*FName WeaponSocket(TEXT("hand_l_socket"));
	auto CurrentWeapon = GetWorld()->SpawnActor<AMyWeapon>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (CurrentWeapon)
	{	// 소켓에 엑터 붙이기 
		CurrentWeapon->AttachToComponent(GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			WeaponSocket);
	}*/
}

void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance)
	{
		// 애니메이션 몽타주 관련 delegate 붙이기
		AnimInstance->OnMontageEnded.AddDynamic(this, &AMyCharacter::OnAttackMontageEnded); // OnMontageEnded()이게 AnimInstance에 구현되어있는 델리게이트 타입임. 
		// 충돌 관련 delegate 붙이기 
		AnimInstance->OnAttackHit.AddUObject(this, &AMyCharacter::AttackCheck);
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 축 바인드 
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("Yaw"), this, &AMyCharacter::Yaw);
	
	// 액션 바인드 
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AMyCharacter::Jump); // Jump는 ACharacter에서 제공함. 
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AMyCharacter::Attack); 
}

void AMyCharacter::UpDown(float Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("UpDown %f"), Value);

	//if (Value == 0.f) return;

	UpDownValue = Value; // for blend space 
	AddMovementInput(GetActorForwardVector(), Value);
}

void AMyCharacter::LeftRight(float Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("LeftRight %f"), Value);

	//if (Value == 0.f) return;

	LeftRightValue = Value; // for blend space 
	AddMovementInput(GetActorRightVector(), Value);
}

void AMyCharacter::Yaw(float Value)
{
	AddControllerYawInput(Value);
}

void AMyCharacter::Attack()
{
	if (IsAttacking)
		return;

	// animtion attack 몽타주를 플레이. (anim instance를 찾아서 거기있는 play함수 실행하기)	
	AnimInstance->PlayAttackMontage();

	// 에니메이션 섹션 실행
	AnimInstance->JumpToSection(AttackIndex);
	AttackIndex = (AttackIndex + 1) % 3;

	IsAttacking = true;
}

void AMyCharacter::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);

	float AttackRange = 100.f;
	float AttackRadius = 50.f;

	// 채널을 이용해서 스윕핑 하겠다. 
	bool bResult = GetWorld()->SweepSingleByChannel(
		OUT HitResult,
		GetActorLocation(), // 시작 위치 
		GetActorLocation() + GetActorForwardVector() * AttackRange, // 끝나는 위치 
		FQuat::Identity, // 회전 안할거라 회전값 (없어서 identity로 채움) 
		ECollisionChannel::ECC_GameTraceChannel2, // 채널
			/* 채널이 무엇인가. 
				프로젝트 폴더에 config > DefaultEngine.ini이라는 설정파일을 조회해보면
				만들었던 Attack 트레이스 채널이 ECC_GameTraceChannel2로 설정되어있다. */
		FCollisionShape::MakeSphere(AttackRadius),// 충돌 범위 모양
		Params); 

	// 충돌 범위 시각적으로 표현해주기 
	FVector Vec = GetActorForwardVector() * AttackRange;
	FVector Center = GetActorLocation() + Vec * 0.5f;
	float HalfHeight = AttackRadius * 0.5f + AttackRadius;
	FQuat Rotation = FRotationMatrix::MakeFromZ(Vec).ToQuat();
	FColor DrawColor;
	if (bResult) DrawColor = FColor::Green;
	else DrawColor = FColor::Red;
	DrawDebugCapsule(GetWorld(), Center, HalfHeight, AttackRadius, Rotation, DrawColor, false, 2.f);


	if (bResult && HitResult.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor %s"), *HitResult.GetActor()->GetName());
	}
}

void AMyCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
}
