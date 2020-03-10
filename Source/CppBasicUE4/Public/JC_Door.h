// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/TimelineComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JC_Door.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UTimelineComponent;

UCLASS()
class CPPBASICUE4_API AJC_Door : public AActor
{
	GENERATED_BODY()

		class UTimelineComponent* MyTimeline;
	
public:	
	// Sets default values for this actor's properties
	AJC_Door();

	USceneComponent* customRootComponent;

	UPROPERTY(VisibleAnywhere,Category="Door")
	UStaticMeshComponent* doorFrameComponent;

	UPROPERTY(EditAnywhere, Category = "Timeline")
		class UCurveFloat* fCurve;

	UPROPERTY(VisibleAnywhere, Category = "Door")
		UStaticMeshComponent* doorComponent;

	UPROPERTY(EditAnywhere, Category = "Door")
		float OpenAngle;
	
	UPROPERTY()
		FRotator StartAngle;

	UPROPERTY()
		FRotator EndAngle;
	
	FOnTimelineFloat InterpFunction{};
	FOnTimelineEvent TimelineFinished{};
	FTimerHandle MyTimerHandle;

	UFUNCTION()
		void TimelineFloatReturn(float value);

	UFUNCTION()
		void OnTimelineFinished();

	UFUNCTION()
		void ReverseTimeLine();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
