// Fill out your copyright notice in the Description page of Project Settings.


#include "JC_ANEnabledAction.h"
#include "JC_Character.h"

void UJC_ANEnabledAction::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* CharacterActor = MeshComp->GetOwner();

	if (IsValid(CharacterActor))
	{
		AJC_Character* Character = Cast<AJC_Character>(CharacterActor);

		if (IsValid(Character))
		{
			Character->SetActionState(false);
		}
	}
}
