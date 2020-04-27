// Fill out your copyright notice in the Description page of Project Settings.


#include "JC_Weapon.h"
#include "GameFramework/Character.h"

// Sets default values
AJC_Weapon::AJC_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Damage = 20.0f;
}

// Called when the game starts or when spawned
void AJC_Weapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJC_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJC_Weapon::SetCharacterOwner(ACharacter* NewOwner)
{
	if(IsValid(NewOwner))
	{
		SetOwner(NewOwner);
		OwnerCharacter = NewOwner;
	}

}

