// Fill out your copyright notice in the Description page of Project Settings.


#include "JC_Character.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AJC_Character::AJC_Character()
{
	FpsCameraSocketName = "SCK_Camera";
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseFirstPersonView = true;
	
	FpsCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS_CameraComponent"));
	FpsCameraComponent->bUsePawnControlRotation = true;
	FpsCameraComponent->SetupAttachment(GetMesh(), FpsCameraSocketName);

	SprintArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SprintArmComponent"));
	SprintArmComponent->bUsePawnControlRotation = true;
	SprintArmComponent->SetupAttachment(RootComponent);

	TpsCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TPS_CameraComponent"));
	TpsCameraComponent->SetupAttachment(SprintArmComponent);

}

// Called when the game starts or when spawned
void AJC_Character::BeginPlay()
{
	Super::BeginPlay();
	
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

}

