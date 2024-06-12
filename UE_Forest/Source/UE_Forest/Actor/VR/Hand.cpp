// Fill out your copyright notice in the Description page of Project Settings.
#include "Actor/VR/Hand.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "MotionControllerComponent.h"


// Sets default values
AHand::AHand()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("HandMesh");
	SphereComponent = CreateDefaultSubobject <USphereComponent>("HandTrigger");

	MotionControllerComponent = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController"));

	SetRootComponent(MotionControllerComponent);
	SkeletalMeshComponent->SetupAttachment(GetRootComponent());
	SphereComponent->SetupAttachment(GetRootComponent());
	MotionControllerComponent->SetTrackingMotionSource(TEXT("LeftGrip"));

}

// Called when the game starts or when spawned
void AHand::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHand::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

