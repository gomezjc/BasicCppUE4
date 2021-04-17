// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JC_SpectatingCamera.generated.h"

UENUM(Blueprintable)
enum class EJC_SpectatingCameraType : uint8
{
	CameraType_None UMETA(DisplayName="None"),
	CameraType_Victory UMETA(DisplayName = "Victory"),
	CameraType_GameOver UMETA(DisplayName = "GameOver")
};

UCLASS()
class CPPBASICUE4_API AJC_SpectatingCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJC_SpectatingCamera();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spectating Camera")
		EJC_SpectatingCameraType CameraType;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* SpectatingCameraComponent;

public:
	EJC_SpectatingCameraType GetCameraType() { return CameraType; }
};
