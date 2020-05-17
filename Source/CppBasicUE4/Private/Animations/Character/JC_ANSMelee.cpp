// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Animations/Character/JC_ANSMelee.h"
#include "JC_Character.h"

void UJC_ANSMelee::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	AActor* CharacterActor = MeshComp->GetOwner();

	if(IsValid(CharacterActor))
	{
		AJC_Character* Character = Cast<AJC_Character>(CharacterActor);

		if(IsValid(Character))
		{
			Character->SetMeleeDetectorCollision(ECollisionEnabled::QueryOnly);
		}
	}
}

void UJC_ANSMelee::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AActor* CharacterActor = MeshComp->GetOwner();

	if (IsValid(CharacterActor))
	{
		AJC_Character* Character = Cast<AJC_Character>(CharacterActor);

		if (IsValid(Character))
		{
			Character->SetMeleeDetectorCollision(ECollisionEnabled::NoCollision);
		}
	}
}
