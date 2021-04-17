// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JC_Weapon.generated.h"

UCLASS()
class CPPBASICUE4_API AJC_Weapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJC_Weapon();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Damage")
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon|Damage")
	TSubclassOf<class UDamageType> DamageType;

	class ACharacter* OwnerCharacter;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetCharacterOwner(class ACharacter* NewOwner);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void BP_StartFire();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void BP_StopFire();
	
	UFUNCTION(BlueprintCallable)
	virtual void StartFire() { BP_StartFire(); };

	UFUNCTION(BlueprintCallable)
	virtual void StopFire() { BP_StopFire(); };
};
