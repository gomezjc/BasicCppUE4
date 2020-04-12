// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JC_Item.generated.h"

UCLASS()
class CPPBASICUE4_API AJC_Item : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* MainColliderComponent;
public:	
	// Sets default values for this actor's properties
	AJC_Item();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PickUp(class AJC_Character* PickupPlayer);

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable,Category="Item")
	void BP_Pickup(class AJC_Character* PickUpActor);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
