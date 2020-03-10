// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/JC_Door.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

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
	
	
}

// Called when the game starts or when spawned
void AJC_Door::BeginPlay()
{
	Super::BeginPlay();

	if(fCurve)
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
