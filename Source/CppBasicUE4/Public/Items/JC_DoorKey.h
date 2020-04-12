// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/JC_Item.h"
#include "JC_DoorKey.generated.h"

/**
 * 
 */
UCLASS()
class CPPBASICUE4_API AJC_DoorKey : public AJC_Item
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* KeyMeshComponent;

protected:
	virtual void PickUp(class AJC_Character* PickupPlayer) override;

	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Key")
	FName KeyTag;

public:
	AJC_DoorKey();

public:

	UFUNCTION(BlueprintCallable,Category="Getter")
	FName GetKeyTag() { return KeyTag; };
	
};
