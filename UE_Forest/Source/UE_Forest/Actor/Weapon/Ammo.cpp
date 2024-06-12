// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Weapon/Ammo.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AAmmo::AAmmo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerComponent = CreateDefaultSubobject<USphereComponent>("TriggerSphereComponent");
	AmmoSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("AmmoMesh");

	SetRootComponent(TriggerComponent);
	AmmoSkeletalMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AAmmo::BeginPlay()
{
	Super::BeginPlay();
	
}


