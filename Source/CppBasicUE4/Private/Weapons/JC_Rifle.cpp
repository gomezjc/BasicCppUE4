// Fill out your copyright notice in the Description page of Project Settings.


#include "JC_Rifle.h"

#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

AJC_Rifle::AJC_Rifle()
{
	TraceLength = 10000.0f;
	MuzzleSocketName = "SKC_Muzzle";
}

void AJC_Rifle::StartFire()
{
	Super::StartFire();

	AActor* CurrentOwner = GetOwner();

	if(IsValid(CurrentOwner))
	{
		FVector EyeLocation;
		FRotator EyeRotator;
		CurrentOwner->GetActorEyesViewPoint(EyeLocation, EyeRotator);
		FVector ShotDirection = EyeRotator.Vector();
		FVector TraceEnd = EyeLocation + (ShotDirection * TraceLength);
		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		QueryParams.AddIgnoredActor(CurrentOwner);
		QueryParams.bTraceComplex = true;

		FVector TraceEndPoint = TraceEnd;
		
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, EyeLocation, TraceEnd, ECC_Visibility, QueryParams);

		if(bHit)
		{
			AActor* HitActor = HitResult.GetActor();
			if(IsValid(HitActor))
			{
				UGameplayStatics::ApplyPointDamage(HitActor, Damage,ShotDirection,HitResult,CurrentOwner->GetInstigatorController(),this,DamageType);
			}

			TraceEndPoint = HitResult.ImpactPoint;

			if(IsValid(ImpactEffect))
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, TraceEndPoint,HitResult.ImpactNormal.Rotation());
			}
		}

		if(bDrawTrace)
		{
			DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::White, false, 1.0f, 0.0f, 1.0f);
		}

		if(IsValid(MuzzleEffect))
		{
			UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, OwnerCharacter->GetMesh(), MuzzleSocketName);
		}

		if (IsValid(TraceEffect))
		{
			USkeletalMeshComponent* CharacterMeshComponent = OwnerCharacter->GetMesh();
			if(IsValid(CharacterMeshComponent))
			{
				FVector MuzzleSocketLocation = CharacterMeshComponent->GetSocketLocation(MuzzleSocketName);
				UParticleSystemComponent* TraceComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TraceEffect, MuzzleSocketLocation);
				if(IsValid(TraceComponent))
				{
					TraceComponent->SetVectorParameter(TraceParamName, TraceEndPoint);
				}
			}
		}
	}
}

void AJC_Rifle::StopFire()
{
	Super::StopFire();
}
