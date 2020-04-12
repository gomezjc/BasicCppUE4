// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JC_Door.generated.h"

UCLASS()
class CPPBASICUE4_API AJC_Door : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJC_Door();

	class UTimelineComponent* MyTimeline;
	
	class USceneComponent* customRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Door")
	class UStaticMeshComponent* doorFrameComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Door")
	class UStaticMeshComponent* doorComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Door")
	class UBoxComponent* KeyZoneCollider;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	class UCurveFloat* fCurve;

	UPROPERTY(EditAnywhere, Category = "Door")
	float OpenAngle;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Door")
	FName DoorTag;
	
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
		bool bIsOpen;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void CheckKeyFromPlayer(class UPrimitiveComponent* OverlappedComponent,class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
