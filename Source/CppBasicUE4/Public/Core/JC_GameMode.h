// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JC_GameMode.generated.h"

class AJC_Character;

UCLASS()
class CPPBASICUE4_API AJC_GameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spectating Camera")
	float SpectatingBlendTime;
	
	UPROPERTY(BlueprintReadOnly, Category = "Spectating Camera")
	class AJC_SpectatingCamera* VictoryCamera;

	UPROPERTY(BlueprintReadOnly, Category = "Spectating Camera")
	class AJC_SpectatingCamera* GameOverCamera;

protected:
	
	virtual void BeginPlay() override;
	
	void SetupSpectatingCameras();

	void MoveCameraToSpectatingPoint(class AJC_Character* Character, class AJC_SpectatingCamera* SpectatingCamera);

public:

	UFUNCTION()
	void Victory(AJC_Character* Character);

	UFUNCTION()
	void GameOver(AJC_Character* Character);

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void BP_Victory(AJC_Character* Character);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BP_GameOver(AJC_Character* Character);

};
