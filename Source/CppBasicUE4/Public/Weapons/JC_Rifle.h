// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/JC_Weapon.h"
#include "JC_Rifle.generated.h"

/**
 * 
 */
UCLASS()
class CPPBASICUE4_API AJC_Rifle : public AJC_Weapon
{
	GENERATED_BODY()

public:

	AJC_Rifle();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LineTrace")
	float TraceLength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LineTrace|Debug")
	bool bDrawTrace;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="SFX")
	class UParticleSystem* MuzzleEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SFX")
	class UParticleSystem* ImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SFX")
    class UParticleSystem* TraceEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SFX")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SFX")
	FName TraceParamName;
	
protected:

	virtual void StartFire() override;
	
	virtual void StopFire() override;
};
