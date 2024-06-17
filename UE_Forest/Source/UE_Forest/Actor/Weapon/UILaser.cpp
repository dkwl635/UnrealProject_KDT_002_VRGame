// Fill out your copyright notice in the Description page of Project Settings.
#include "Actor/Weapon/UILaser.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetInteractionComponent.h"

// Sets default values
AUILaser::AUILaser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	WidgetInteractionComponent = CreateDefaultSubobject<UWidgetInteractionComponent>("WidgetInteractionComponent");

	SetRootComponent(StaticMeshComponent);
	WidgetInteractionComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AUILaser::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUILaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUILaser::CheckGrab(bool InHand)
{
}

void AUILaser::Grab(UVRHandSkeletalMeshComponent* Hand)
{
}

void AUILaser::VRTriggerStart()
{
}

void AUILaser::VRTrigger(float ActionValue)
{
}

void AUILaser::VRTriggerCompleted()
{
}

void AUILaser::Release()
{
}

void AUILaser::VRAction1()
{
}

void AUILaser::VRAction2()
{
}

void AUILaser::VRStick()
{
}

