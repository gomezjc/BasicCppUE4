// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JC_FloatingPlatform.generated.h"

class UStaticMeshComponent;
class USceneComponent;

UCLASS()
class CPPBASICUE4_API AJC_FloatingPlatform : public AActor
{
	GENERATED_BODY()
	
	USceneComponent* customRootComponent;

	UPROPERTY(VisibleAnywhere,Category="Platform")
	UStaticMeshComponent* platformComponent;

	UPROPERTY(EditAnywhere,Category="Platform")
	bool bIsGoingUp;
	
	UPROPERTY(EditAnywhere, Category = "Platform")
	float Speed;

	UPROPERTY(EditAnywhere, Category = "Platform")
	float MinHeight;

	UPROPERTY(EditAnywhere, Category = "Platform")
	float MaxHeight;
	
public:	
	// Sets default values for this actor's properties
	AJC_FloatingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Platform")
	void move();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
