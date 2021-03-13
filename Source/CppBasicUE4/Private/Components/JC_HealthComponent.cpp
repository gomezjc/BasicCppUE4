// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/JC_HealthComponent.h"

// Sets default values for this component's properties
UJC_HealthComponent::UJC_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	MaxHealth = 100.0f;
	Health = MaxHealth;
}


// Called when the game starts
void UJC_HealthComponent::BeginPlay()
{
	Super::BeginPlay();
	MyOwner = GetOwner();

	if(IsValid(MyOwner))
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UJC_HealthComponent::TakingDamage);
	}
}

void UJC_HealthComponent::TakingDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	if(Damage <= 0.0f || bIsDead)
	{
		return; 
	}
	
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);

	if (Health == 0.0f)
	{
		bIsDead = true;
	}

	OnHealthChangeDelegate.Broadcast(this, DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);
	UE_LOG(LogTemp, Log, TEXT("My Health is: %f"), Health);
}



