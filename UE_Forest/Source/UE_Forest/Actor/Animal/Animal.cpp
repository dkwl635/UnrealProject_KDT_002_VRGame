// Fill out your copyright notice in the Description page of Project Settings.
#include "Actor/Animal/Animal.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Animation/AnimInstance.h"
#include "GameMode/ForestGameMode.h"


// Sets default values
AAnimal::AAnimal()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	SetRootComponent(CapsuleComponent);
	SkeletalMeshComponent->SetupAttachment(GetRootComponent());
	FloatingPawnMovement->UpdatedComponent = GetRootComponent();	
}

// Called when the game starts or when spawned
void AAnimal::BeginPlay()
{
	Super::BeginPlay();

	AForestGameMode* GameMode = Cast<AForestGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		Target = &(GameMode->ForestCharacter);
	}

}


FVector AAnimal::GetNextMovePos()
{
	float x = 0;
	float y = 0;
	x = FMath::RandRange(-MapSize, MapSize);
	y = FMath::RandRange(-MapSize, MapSize);

	return FVector(x, y, GetActorLocation().Z);
}

FVector AAnimal::GetNextSpawnPos()
{
	FVector PlayerPos = (*Target)->GetActorLocation();
	FVector2D RandPos = (FMath::RandPointInCircle(1)) * 5000;

	return  FVector(PlayerPos.X + RandPos.X, PlayerPos.Y + RandPos.Y , GetActorLocation().Z);
}




void AAnimal::ForestGameStart()
{
	MoveToStart();
}

void AAnimal::ForestGameEnd()
{
}




