// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/JC_Weapon.h"
#include "JC_GrenadeLauncher.generated.h"

/**
 * 
 */
UCLASS()
class CPPBASICUE4_API AJC_GrenadeLauncher : public AJC_Weapon
{
	GENERATED_BODY()

public:
	AJC_GrenadeLauncher();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Grenade Launcher")
	TSubclassOf<class AJC_Projectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SFX")
	FName MuzzleSocketName;
	
protected:

	virtual void StartFire() override;

	virtual void StopFire() override;
};
