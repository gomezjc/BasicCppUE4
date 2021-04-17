// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/JC_GameMode.h"
#include "JC_Character.h"
#include "JC_SpectatingCamera.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"


void AJC_GameMode::BeginPlay()
{
	Super::BeginPlay();
	SetupSpectatingCameras();
}

void AJC_GameMode::SetupSpectatingCameras()
{
	TArray<AActor*> SpectatingCameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AJC_SpectatingCamera::StaticClass(), SpectatingCameraActors);

	if (SpectatingCameraActors.Num() > 0)
	{
		for (AActor* SpectatingActor : SpectatingCameraActors)
		{
			AJC_SpectatingCamera* SpectatingCamera = Cast<AJC_SpectatingCamera>(SpectatingActor);

			if (IsValid(SpectatingCamera))
			{
				switch (SpectatingCamera->GetCameraType())
				{
				case EJC_SpectatingCameraType::CameraType_Victory:
					VictoryCamera = SpectatingCamera;
					break;
				case EJC_SpectatingCameraType::CameraType_GameOver:
					GameOverCamera = SpectatingCamera;
					break;
				default:
					break;
				}
			}
		}
	}
}

void AJC_GameMode::MoveCameraToSpectatingPoint(AJC_Character* Character, AJC_SpectatingCamera* SpectatingCamera)
{
	if(IsValid(Character) && IsValid(SpectatingCamera))
	{
		AController* CharacterController = Character->GetController();
		if (IsValid(CharacterController))
		{
			APlayerController* PlayerController = Cast<APlayerController>(CharacterController);
			if (IsValid(PlayerController))
			{
				PlayerController->SetViewTargetWithBlend(SpectatingCamera, SpectatingBlendTime, EViewTargetBlendFunction::VTBlend_Cubic);
			}
		}
	}
}

void AJC_GameMode::Victory(AJC_Character* Character)
{
	Character->DisableInput(nullptr);
	MoveCameraToSpectatingPoint(Character, VictoryCamera);
	BP_Victory(Character);
}

void AJC_GameMode::GameOver(AJC_Character* Character)
{
	Character->GetMovementComponent()->StopMovementImmediately();
	Character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if(Character->HasToDestroy())
	{
		Character->DetachFromControllerPendingDestroy();
		Character->SetLifeSpan(5.0f);
	}else{
		Character->DisableInput(nullptr);
		MoveCameraToSpectatingPoint(Character, GameOverCamera);
	}
	
	BP_GameOver(Character);
}
