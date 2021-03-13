// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JC_HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FOnHealthChangeSignature, UJC_HealthComponent*, HealthComponent, AActor*, DamagedActor, float, Damage, const UDamageType*, DamageType, AController*, InstigatedBy, AActor*, DamageCauser);

UCLASS( ClassGroup=(JC), meta=(BlueprintSpawnableComponent) )
class CPPBASICUE4_API UJC_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, Category = "HealthComponent")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent", meta=(ClampMin=0.0, UIMin=0.0) )
	float MaxHealth;

	UPROPERTY(BlueprintReadWrite, Category = "HealthComponent")
	class AActor* MyOwner;

	UPROPERTY(BlueprintReadOnly, Category="HealthComponent")
	bool bIsDead;

public:	
	// Sets default values for this component's properties
	UJC_HealthComponent();

	UPROPERTY(BlueprintAssignable)
	FOnHealthChangeSignature OnHealthChangeDelegate;

	UFUNCTION(BlueprintCallable)
	bool IsDead() { return bIsDead; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void TakingDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	
};
