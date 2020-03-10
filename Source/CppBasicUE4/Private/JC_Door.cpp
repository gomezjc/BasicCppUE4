// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/JC_Door.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AJC_Door::AJC_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	customRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("customRoot"));
	RootComponent = customRootComponent;

	doorFrameComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("doorFrame"));
	doorFrameComponent->SetupAttachment(customRootComponent);
	doorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("door"));
	doorComponent->SetupAttachment(customRootComponent);

	OpenAngle = -90.0f;
}

// Called when the game starts or when spawned
void AJC_Door::BeginPlay()
{
	Super::BeginPlay();
	openDoor();
	
}

void AJC_Door::openDoor()
{
	FRotator newRotation = FRotator(0.0f, OpenAngle, 0.0f);
	doorComponent->SetRelativeRotation(newRotation);
}

// Called every frame
void AJC_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

