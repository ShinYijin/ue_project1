// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

// TODO 
// [Component]
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"// GetCapsuleComponent()�� ����ϱ� ����. 
										// �̰� �Ⱦ��� �Ƹ� CapsuleComponent��� Ÿ���� �� ���� �ڵ� ����ȯ�� �ȵǴ� ��. �׷��� SpringArm->SetupAttachment(GetCapsuleComponent()); ���� ������. 
#include "MyAnimInstance.h"
#include "MyWeapon.h"

#include "DrawDebugHelpers.h" // ������ϱ� ���ϰ� �����ִ� ���̺귯�� 

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// [�޽� �ε�]
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"/*�޽� ���ҽ� ���*/));
	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}
	
	// [Component setting]
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	// [Setting Root]
	// ������Ʈ��  �θ� ������Ʈ�� ��������. �θ� �׳� �� ��ü��ü�� �ƴ϶� �� ��ü�� ����ִ� ������Ʈ�� �����Ǿ���ϳ���. 
	SpringArm->SetupAttachment(GetCapsuleComponent()); 
	Camera->SetupAttachment(SpringArm);

	// [Setting Spring Arm]
	SpringArm->TargetArmLength = 500.f; // ��ī���� ���� 
	SpringArm->SetRelativeRotation(FRotator(-35.f, 0.f, 0.f));	// ��ī���� ���� 

	// [Mesh local transform setting]
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0.f, -90.f, 0.f));

	// ���Ͽ� ���� ���̱�(���⸦ ���� ���� Ŭ������ �������� �ʴ� ���) 
	/*FName WeaponSocket(TEXT("hand_l_socket")); // ���� �̸� ���� 
	if (GetMesh()->DoesSocketExist(WeaponSocket)) // ������ �ִ��� Ȯ�� 
	{
		Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEAPON"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SW(TEXT("/Script/Engine.StaticMesh'/Game/ParagonGreystone/FX/Meshes/Heroes/Greystone/SM_Greystone_Blade_01.SM_Greystone_Blade_01'"));
		if (SW.Succeeded())
		{
			Weapon->SetStaticMesh(SW.Object);
		}
		// �츮�� ���ϴ� ���Ͽ� -> Weapon�� ���̱� 
		Weapon->SetupAttachment(GetMesh(), WeaponSocket);
	}*/


}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	// ���� Ŭ������ �����Ǵ� ���⸦ �����ؼ� �����ϴ� ��� 
	/*FName WeaponSocket(TEXT("hand_l_socket"));
	auto CurrentWeapon = GetWorld()->SpawnActor<AMyWeapon>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (CurrentWeapon)
	{	// ���Ͽ� ���� ���̱� 
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
		// �ִϸ��̼� ��Ÿ�� ���� delegate ���̱�
		AnimInstance->OnMontageEnded.AddDynamic(this, &AMyCharacter::OnAttackMontageEnded); // OnMontageEnded()�̰� AnimInstance�� �����Ǿ��ִ� ��������Ʈ Ÿ����. 
		// �浹 ���� delegate ���̱� 
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

	// �� ���ε� 
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AMyCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AMyCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("Yaw"), this, &AMyCharacter::Yaw);
	
	// �׼� ���ε� 
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AMyCharacter::Jump); // Jump�� ACharacter���� ������. 
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

	// animtion attack ��Ÿ�ָ� �÷���. (anim instance�� ã�Ƽ� �ű��ִ� play�Լ� �����ϱ�)	
	AnimInstance->PlayAttackMontage();

	// ���ϸ��̼� ���� ����
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

	// ä���� �̿��ؼ� ������ �ϰڴ�. 
	bool bResult = GetWorld()->SweepSingleByChannel(
		OUT HitResult,
		GetActorLocation(), // ���� ��ġ 
		GetActorLocation() + GetActorForwardVector() * AttackRange, // ������ ��ġ 
		FQuat::Identity, // ȸ�� ���ҰŶ� ȸ���� (��� identity�� ä��) 
		ECollisionChannel::ECC_GameTraceChannel2, // ä��
			/* ä���� �����ΰ�. 
				������Ʈ ������ config > DefaultEngine.ini�̶�� ���������� ��ȸ�غ���
				������� Attack Ʈ���̽� ä���� ECC_GameTraceChannel2�� �����Ǿ��ִ�. */
		FCollisionShape::MakeSphere(AttackRadius),// �浹 ���� ���
		Params); 

	// �浹 ���� �ð������� ǥ�����ֱ� 
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
