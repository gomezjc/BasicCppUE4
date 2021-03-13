// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/JC_GameMode.h"
#include "JC_Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"

void AJC_GameMode::Victory(AJC_Character* Character)
{
	Character->DisableInput(nullptr);
	BP_Victory(Character);
}

void AJC_GameMode::GameOver(AJC_Character* Character)
{
	Character->GetMovementComponent()->StopMovementImmediately();
	Character->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Character->DetachFromControllerPendingDestroy();
	Character->SetLifeSpan(5.0f);
	
	BP_GameOver(Character);
}
