// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/JC_VictoryZone.h"

#include "JC_Character.h"
#include "JC_GameMode.h"
#include "Components/BoxComponent.h"

// Sets default values
AJC_VictoryZone::AJC_VictoryZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	VictoryZoneComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("VictoryZoneComponent"));
	RootComponent = VictoryZoneComponent;

	VictoryZoneComponent->SetBoxExtent(FVector(100.0f));
}

// Called when the game starts or when spawned
void AJC_VictoryZone::BeginPlay()
{
	Super::BeginPlay();
	GameModeRef = Cast<AJC_GameMode>(GetWorld()->GetAuthGameMode());
}

// Called every frame
void AJC_VictoryZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJC_VictoryZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if(IsValid(OtherActor) && IsValid(GameModeRef))
	{
		AJC_Character* JCharacter = Cast<AJC_Character>(OtherActor);

		if(IsValid(JCharacter))
		{
			GameModeRef->Victory(JCharacter);
		}
	}
}

