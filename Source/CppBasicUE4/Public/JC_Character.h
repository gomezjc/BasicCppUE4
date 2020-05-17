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

	class UAnimInstance* AnimInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCapsuleComponent* MeleeDetectorComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	FName MeleeSocketName;

	UFUNCTION()
	void MakeMeleeDamage(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
		void CheckPlayerEnter(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

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
};
