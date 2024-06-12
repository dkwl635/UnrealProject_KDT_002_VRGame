// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Object/Orb.h"
#include "GameMode//ForestGameMode.h"

// Sets default values
AOrb::AOrb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AOrb::AddOrb()
{
	AForestGameMode* GameMode = Cast<AForestGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->AddOrb();
	}


	this->Destroy();

}



