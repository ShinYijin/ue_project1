// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

// TODO 
// [Component]
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"// GetCapsuleComponent()를 사용하기 위함. 
										// 이걸 안쓰면 아마 CapsuleComponent라는 타입을 잘 몰라서 자동 형변환이 안되는 듯. 그래서 SpringArm->SetupAttachment(GetCapsuleComponent()); 에서 오류남. 
#include "MyAnimInstance.h"

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
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// 애니메이션 몽타주 관련 delegate 붙이기
	AnimInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInstance->OnMontageEnded.AddDynamic(this, &AMyCharacter::OnAttackMontageEnded); // OnMontageEnded()이게 AnimInstance에 구현되어있는 델리게이트 타입임. 
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

void AMyCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
}
