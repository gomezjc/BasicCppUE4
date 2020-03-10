// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/JC_FloatingPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AJC_FloatingPlatform::AJC_FloatingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	customRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("customRoot"));
	RootComponent = customRootComponent;

	platformComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform"));
	platformComponent->SetupAttachment(customRootComponent);

	bIsGoingUp = true;
	Speed = 10.0f;
	MinHeight = 0.0f;
	MaxHeight = 50.0f;
}

// Called when the game starts or when spawned
void AJC_FloatingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

void AJC_FloatingPlatform::move()
{
	FVector upDirection = UKismetMathLibrary::GetUpVector(GetActorRotation());

	upDirection = bIsGoingUp ? upDirection : upDirection * -1;

	FVector currentVelocity = upDirection * Speed;
	FVector newPosition = GetActorLocation() + currentVelocity;
	SetActorLocation(newPosition);

	if((bIsGoingUp && newPosition.Z >= MaxHeight) || (!bIsGoingUp && newPosition.Z <= MinHeight))
	{
		bIsGoingUp = !bIsGoingUp;
	}
}

// Called every frame
void AJC_FloatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	move();
}

