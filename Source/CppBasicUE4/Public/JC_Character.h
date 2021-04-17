// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JC_Character.generated.h"

UCLASS()
class CPPBASICUE4_API AJC_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AJC_Character();

	virtual FVector GetPawnViewLocation() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);

	void MoveRight(float Value);
	
	virtual void Jump() override;
	virtual void StopJumping() override;

	virtual void AddControllerPitchInput(float value) override;

	FTimerHandle TimeHandle_Ultimate;

	FTimerHandle TimeHandle_AutomaticShoot;

	FTimerHandle TimeHandle_BeginUltimateBehaviour;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category="Aiming")
	bool bIsLookInversion;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Aiming")
	bool bUseFirstPersonView;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	float MeleeDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	bool bCanMakeCombo;

	UPROPERTY(BlueprintReadOnly, Category = "Melee")
	bool bIsComboEnabled;

	UPROPERTY(EditDefaultsOnly, Category = "Melee",meta=(EditCondition= bCanMakeCombo,ClampMin=1.0,UIMin=1.0))
	float MaxNumComboMultiplier;

	UPROPERTY(EditDefaultsOnly, Category = "Melee", meta = (EditCondition = bCanMakeCombo, ClampMin = 1.0, UIMin = 1.0))
	float CurrentComboMultiplier;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Key")
	TArray<FName> DoorKeys;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Aiming")
	FName FpsCameraSocketName;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCameraComponent* FpsCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCameraComponent* TpsCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USpringArmComponent* SprintArmComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Melee")
	bool bIsDoingMelee;

	UPROPERTY(BlueprintReadOnly, Category = "Melee")
	bool bCanUseWeapon;

	void StartFireWeapon();
	
	void StopFireWeapon();

	void StartMelee();

	void StopMelee();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Weapon")
	TSubclassOf<class AJC_Weapon> InitialWeaponClass;

	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
	class AJC_Weapon* CurrentWeapon;

	void CreateInitialWeapon();
	
	void InitializeReferences();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	class UAnimMontage* MeleeMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	class UAnimMontage* UltimateMontage;
	
	class UAnimInstance* AnimInstance;

	class AJC_GameMode* GameModeRef;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ultimate", meta=(ClampMin=0.0, UIMin=0.0))
	float MaxUltimateXp;

	UPROPERTY(BlueprintReadOnly, Category = "Ultimate")
	float CurrentUltimateXp;

	UPROPERTY(BlueprintReadOnly, Category = "Ultimate")
	bool bCanUseUltimate;

	UPROPERTY(BlueprintReadOnly, Category = "Ultimate")
	bool bIsUsingUltimate;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Over")
	bool bHasToDestroy;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ultimate")
	bool bUltimateWithTick;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ultimate|Time", meta = (ClampMin = 0.0, UIMin = 0.0))
	float MaxUltimateDuration;

	UPROPERTY(BlueprintReadOnly, Category = "Ultimate|Time")
	float CurrentUltimateDuration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ultimate|Time")
	float UltimateFrequency;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ultimate|Abilities", meta = (ClampMin = 0.0, UIMin = 0.0))
	float UltimateWalkSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Ultimate|Abilities")
	float NormalWalkSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ultimate|Abilities", meta = (ClampMin = 0.0, UIMin = 0.0))
	float UltimatePlayRate;

	UPROPERTY(BlueprintReadOnly, Category = "Ultimate|Abilities")
	float PlayRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ultimate|Abilities", meta = (ClampMin = 0.0, UIMin = 0.0))
	float UltimateShootFrequency;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCapsuleComponent* MeleeDetectorComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	FName MeleeSocketName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UJC_HealthComponent* HealthComponent3;

	UFUNCTION()
	void MakeMeleeDamage(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void CheckPlayerEnter(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnHealthChange(UJC_HealthComponent* HealthComponent, AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AddKey(FName NewKey);

	bool HasKey(FName KeyTag);

	void SetMeleeDetectorCollision(ECollisionEnabled::Type NewCollisionState);

	void SetActionState(bool NewState);

	UFUNCTION(BlueprintCallable)
	void SetComboEnabled(bool NewState);

	UFUNCTION(BlueprintCallable)
	void ResetCombo();

	UFUNCTION(BlueprintCallable)
	void GainUltimateXp(float XpGained);

	bool HasToDestroy() { return bHasToDestroy; }

	void UpdateUltimateDuration(float Value);

	void UpdateUltimateDurationTimer();

	void BeginUltimateBehaviour();
	
protected:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_GainUltimateXp(float XpGained);

	void StartUltimate();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_StartUltimate();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_StopUltimate();


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_UpdateUltimateDuration(float Value);
	
};