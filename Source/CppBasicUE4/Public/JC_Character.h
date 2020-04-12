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

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Key")
	TArray<FName> DoorKeys;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aiming")
	FName FpsCameraSocketName;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCameraComponent* FpsCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCameraComponent* TpsCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USpringArmComponent* SprintArmComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AddKey(FName NewKey);

	bool HasKey(FName KeyTag);
};
