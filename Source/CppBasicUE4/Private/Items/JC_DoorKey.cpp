// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/JC_DoorKey.h"
#include "Components/StaticMeshComponent.h"
#include "Public/JC_Character.h"

AJC_DoorKey::AJC_DoorKey()
{
	KeyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMeshComponent"));
	KeyMeshComponent->SetupAttachment(RootComponent);
	KeyMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	KeyTag = "KeyA";
}

void AJC_DoorKey::PickUp(AJC_Character* PickupPlayer)
{
	Super::PickUp(PickupPlayer);
	PickupPlayer->AddKey(KeyTag);
	Destroy();
}