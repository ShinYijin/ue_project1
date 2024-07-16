// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

// TODO 
// [Component]
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"// GetCapsuleComponent()�� ����ϱ� ����. 
										// �̰� �Ⱦ��� �Ƹ� CapsuleComponent��� Ÿ���� �� ���� �ڵ� ����ȯ�� �ȵǴ� ��. �׷��� SpringArm->SetupAttachment(GetCapsuleComponent()); ���� ������. 
#include "Components/WidgetComponent.h"
#include "Engine/DamageEvents.h"

#include "MyAnimInstance.h"
#include "MyWeapon.h"
#include "MyStatComponent.h"
#include "MyUserWidget.h"

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
	Stat = CreateDefaultSubobject<UMyStatComponent>(TEXT("STAT"));
	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));

	// [Setting Root]
	// ������Ʈ��  �θ� ������Ʈ�� ��������. �θ� �׳� �� ��ü��ü�� �ƴ϶� �� ��ü�� ����ִ� ������Ʈ�� �����Ǿ���ϳ���. 
	SpringArm->SetupAttachment(GetCapsuleComponent()); 
	Camera->SetupAttachment(SpringArm);
	HpBar->SetupAttachment(GetMesh());

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

	// [Setting User Widget Component]
	HpBar->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
	HpBar->SetWidgetSpace(EWidgetSpace::Screen); //screen�� ����� �߸��� �ʰ� �׻� ���̴°�. world�� �ݴ�. 
	static ConstructorHelpers::FClassFinder<UUserWidget> UM(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/UI/WBP_Hpbar.WBP_Hpbar_C'"));
	if(UM.Succeeded())
	{
		HpBar->SetWidgetClass(UM.Class);
		HpBar->SetDrawSize(FVector2D(200.f, 10.f));
	}
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

	HpBar->InitWidget();	// ���� �ʱ�ȭ. �̰� �����ָ� ������ ����� ������ ����. Ȯ���� �ϱ� ���� �׳� ����. 	
	auto HpWidget = Cast<UMyUserWidget>(HpBar->GetUserWidgetObject());
	if (HpWidget)
	{
		HpWidget->BindHp(Stat);
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
	if (bResult) 
		DrawColor = FColor::Green;
	else 
		DrawColor = FColor::Red;
	DrawDebugCapsule(GetWorld(), Center, HalfHeight, AttackRadius, Rotation, DrawColor, false, 2.f);


	if (bResult && HitResult.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor %s"), *HitResult.GetActor()->GetName());

		FDamageEvent DamageEvent;
		HitResult.GetActor()->TakeDamage(Stat->GetAttack(), DamageEvent, GetController(), this/*���� �긦 �����ϰ� �ִ� �Ŵϱ� this�� �Ѱ��ش�*/);
			// TakeDamage�� Actor�ȿ� �⺻������ ���ִ� �����Լ�. 
	}
}

void AMyCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
}

float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	Stat->OnAttacked(DamageAmount);
	return DamageAmount;
}
