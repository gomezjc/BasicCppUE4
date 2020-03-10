// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JC_Door.generated.h"

class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class CPPBASICUE4_API AJC_Door : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJC_Door();

	USceneComponent* customRootComponent;

	UPROPERTY(VisibleAnywhere,Category="Door")
	UStaticMeshComponent* doorFrameComponent;
	
	UPROPERTY(VisibleAnywhere, Category = "Door")
	UStaticMeshComponent* doorComponent;

	UPROPERTY(EditAnywhere,Category="Door")
	float OpenAngle;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void openDoor();

};
