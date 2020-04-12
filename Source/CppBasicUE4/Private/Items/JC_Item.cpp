// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/JC_Item.h"
#include "Components/SphereComponent.h"
#include "JC_Character.h"

// Sets default values
AJC_Item::AJC_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainColliderComponent = CreateDefaultSubobject<USphereComponent>(TEXT("MainColliderComponent"));
	RootComponent = MainColliderComponent;

	MainColliderComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MainColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	MainColliderComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	
}

// Called when the game starts or when spawned
void AJC_Item::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJC_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJC_Item::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (IsValid(OtherActor))
	{
		AJC_Character* OverlapCharacter = Cast<AJC_Character>(OtherActor);

		if(IsValid(OverlapCharacter))
		{
			PickUp(OverlapCharacter);
		}	
	}
}

void AJC_Item::PickUp(AJC_Character* PickupPlayer)
{
	BP_Pickup(PickupPlayer);
}