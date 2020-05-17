// Fill out your copyright notice in the Description page of Project Settings.


#include "JC_Character.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Weapons/JC_Weapon.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "Components/CapsuleComponent.h"
#include "CppBasicUE4.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AJC_Character::AJC_Character()
{	
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeleeSocketName = "SCK_Melee";
	FpsCameraSocketName = "SCK_Camera";
	bUseFirstPersonView = true;
	MeleeDamage = 10.0f;
	bCanUseWeapon = true;
	MaxNumComboMultiplier = 4.0f;
	CurrentComboMultiplier = 1.0f;
	
	FpsCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS_CameraComponent"));
	FpsCameraComponent->bUsePawnControlRotation = true;
	FpsCameraComponent->SetupAttachment(GetMesh(), FpsCameraSocketName);

	SprintArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SprintArmComponent"));
	SprintArmComponent->bUsePawnControlRotation = true;
	SprintArmComponent->SetupAttachment(RootComponent);

	TpsCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TPS_CameraComponent"));
	TpsCameraComponent->SetupAttachment(SprintArmComponent);


	MeleeDetectorComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MeleeDetector"));
	MeleeDetectorComponent->SetupAttachment(GetMesh(),MeleeSocketName);
	MeleeDetectorComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeleeDetectorComponent->SetCollisionResponseToChannel(COLLISION_ENEMY, ECR_Overlap);
	MeleeDetectorComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

FVector AJC_Character::GetPawnViewLocation() const
{
	
	if(IsValid(FpsCameraComponent) && bUseFirstPersonView)
	{
		return FpsCameraComponent->GetComponentLocation();
	}else if (IsValid(TpsCameraComponent) && !bUseFirstPersonView)
	{
		return TpsCameraComponent->GetComponentLocation();
	}

	return Super::GetPawnViewLocation();
}

// Called when the game starts or when spawned
void AJC_Character::BeginPlay()
{
	Super::BeginPlay();
	CreateInitialWeapon();
	InitializeReferences();
	MeleeDetectorComponent->OnComponentBeginOverlap.AddDynamic(this, &AJC_Character::MakeMeleeDamage);
}



void AJC_Character::CreateInitialWeapon()
{
	if (IsValid(InitialWeaponClass))
	{
		CurrentWeapon = GetWorld()->SpawnActor<AJC_Weapon>(InitialWeaponClass, GetActorLocation(), GetActorRotation());
		if (IsValid(CurrentWeapon))
		{
			CurrentWeapon->SetCharacterOwner(this);
			CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
	}
}

void AJC_Character::InitializeReferences()
{
	if(IsValid(GetMesh()))
	{
		AnimInstance = GetMesh()->GetAnimInstance();
	}
}

void AJC_Character::MakeMeleeDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(IsValid(OtherActor))
	{
		UGameplayStatics::ApplyPointDamage(OtherActor, MeleeDamage * CurrentComboMultiplier, SweepResult.Location, SweepResult, GetInstigatorController(), this, nullptr);
	}
}

// Called every frame
void AJC_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJC_Character::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector() * value);
}

void AJC_Character::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector() * value);
}

void AJC_Character::Jump()
{
	Super::Jump();
	
}

void AJC_Character::StopJumping()
{
	Super::StopJumping();
}

void AJC_Character::AddControllerPitchInput(float value)
{
	Super::AddControllerPitchInput(bIsLookInversion ? -value : value);	
}

// Called to bind functionality to input
void AJC_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward",this,&AJC_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&AJC_Character::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &AJC_Character::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight", this, &AJC_Character::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed,this, &AJC_Character::Jump);
	PlayerInputComponent->BindAction("StopJump", IE_Released,this, &AJC_Character::StopJumping);


	PlayerInputComponent->BindAction("FireWeapon", IE_Pressed, this, &AJC_Character::StartFireWeapon);
	PlayerInputComponent->BindAction("FireWeapon", IE_Released, this, &AJC_Character::StopFireWeapon);


	PlayerInputComponent->BindAction("Melee", IE_Pressed, this, &AJC_Character::StartMelee);
	PlayerInputComponent->BindAction("Melee", IE_Released, this, &AJC_Character::StopMelee);

}

void AJC_Character::AddKey(FName NewKey)
{
	DoorKeys.Add(NewKey);
}

bool AJC_Character::HasKey(FName KeyTag)
{
	return DoorKeys.Contains(KeyTag);
}

void AJC_Character::SetMeleeDetectorCollision(ECollisionEnabled::Type NewCollisionState)
{
	MeleeDetectorComponent->SetCollisionEnabled(NewCollisionState);
}


void AJC_Character::StartFireWeapon()
{
	if (!bCanUseWeapon) return;
	if(IsValid(CurrentWeapon))
	{
		CurrentWeapon->StartFire();
	}
}

void AJC_Character::StopFireWeapon()
{
	if (!bCanUseWeapon) return;
	if (IsValid(CurrentWeapon))
	{
		CurrentWeapon->StopFire();
	}
}

void AJC_Character::StartMelee()
{
	if (bIsDoingMelee && !bCanMakeCombo) return;

	if(bCanMakeCombo)
	{
		if(bIsDoingMelee)
		{
			if(bIsComboEnabled)
			{
				if(CurrentComboMultiplier < MaxNumComboMultiplier)
				{
					CurrentComboMultiplier++;
					SetComboEnabled(false);
				}else
				{
					return;
				}
			}else
			{
				return;
			}
		}
	}
	
	if(IsValid(AnimInstance) && IsValid(MeleeMontage))
	{
		AnimInstance->Montage_Play(MeleeMontage);
	}
	SetActionState(true);
}

void AJC_Character::StopMelee()
{
	
}

void AJC_Character::SetActionState(bool NewState)
{
	bIsDoingMelee = NewState;
	bCanUseWeapon = !NewState;
}

void AJC_Character::SetComboEnabled(bool NewState)
{
	bIsComboEnabled = NewState;
}

void AJC_Character::ResetCombo()
{
	SetComboEnabled(false);
	CurrentComboMultiplier = 1.0f;
}
