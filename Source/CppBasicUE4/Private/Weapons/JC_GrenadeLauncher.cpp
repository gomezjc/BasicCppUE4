// Fill out your copyright notice in the Description page of Project Settings.


#include "JC_GrenadeLauncher.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "Weapons/JC_Projectile.h"
#include "GameFramework/Character.h"


AJC_GrenadeLauncher::AJC_GrenadeLauncher()
{
	MuzzleSocketName = "SKC_Muzzle";
}

void AJC_GrenadeLauncher::StartFire()
{
	Super::StartFire();

	if(IsValid(OwnerCharacter))
	{
		USkeletalMeshComponent* CharacterMeshComponent = OwnerCharacter->GetMesh();
		if (IsValid(CharacterMeshComponent))
		{
			FVector MuzzleSocketLocation = CharacterMeshComponent->GetSocketLocation(MuzzleSocketName);
			FRotator MuzzleSocketRotation = CharacterMeshComponent->GetSocketRotation(MuzzleSocketName);
			AJC_Projectile* CurrentProjectile = GetWorld()->SpawnActor<AJC_Projectile>(ProjectileClass, MuzzleSocketLocation, MuzzleSocketRotation);
		}
	}	
}

void AJC_GrenadeLauncher::StopFire()
{
	Super::StopFire();
}