// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/JC_Door.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Components/BoxComponent.h"
#include "JC_Character.h"

// Sets default values
AJC_Door::AJC_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	customRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("customRoot"));
	RootComponent = customRootComponent;

	doorFrameComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("doorFrame"));
	doorFrameComponent->SetupAttachment(customRootComponent);
	doorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("door"));
	doorComponent->SetupAttachment(customRootComponent);

	MyTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));

	InterpFunction.BindUFunction(this, FName("TimelineFloatReturn"));
	TimelineFinished.BindUFunction(this, FName("OnTimelineFinished"));
	OpenAngle = -90.0f;
	DoorTag = "KeyA";
	
	KeyZoneCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("KeyZoneCollider"));
	KeyZoneCollider->SetupAttachment(RootComponent);
	KeyZoneCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	KeyZoneCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	KeyZoneCollider->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
}

// Called when the game starts or when spawned
void AJC_Door::BeginPlay()
{
	Super::BeginPlay();
	KeyZoneCollider->OnComponentBeginOverlap.AddDynamic(this, &AJC_Door::CheckKeyFromPlayer);
}

// Called every frame
void AJC_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AJC_Door::TimelineFloatReturn(float value)
{
	doorComponent->SetRelativeRotation(FMath::Lerp(StartAngle,EndAngle,value));
}

void AJC_Door::OnTimelineFinished()
{
	if(MyTimeline->GetPlaybackPosition() == 0.0f)
	{
		GLog->Log("Stop");
		MyTimeline->Stop();
	}else if(MyTimeline->GetPlaybackPosition() == this->MyTimeline->GetTimelineLength())
	{
		GLog->Log("reverse");
		GetWorldTimerManager().SetTimer(MyTimerHandle, this, &AJC_Door::ReverseTimeLine, 0.5f, false);
	}
}

void AJC_Door::ReverseTimeLine()
{
	MyTimeline->Reverse();
}

void AJC_Door::CheckKeyFromPlayer(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(IsValid(OtherActor))
	{
		AJC_Character* OverlapCharacter = Cast<AJC_Character>(OtherActor);

		if(IsValid(OverlapCharacter))
		{
			if(OverlapCharacter->HasKey(DoorTag))
			{
				if (fCurve)
				{
					MyTimeline->AddInterpFloat(fCurve, InterpFunction, FName("Alpha"));
					MyTimeline->SetTimelineFinishedFunc(TimelineFinished);
				}

				StartAngle = doorComponent->GetRelativeTransform().Rotator();
				EndAngle = FRotator(StartAngle.Pitch, OpenAngle, StartAngle.Roll);

				MyTimeline->SetLooping(false);
				MyTimeline->SetIgnoreTimeDilation(true);
				MyTimeline->Play();
			}
		}
	}
}