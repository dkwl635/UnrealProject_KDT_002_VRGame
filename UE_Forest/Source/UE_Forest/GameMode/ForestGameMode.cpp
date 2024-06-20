// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/ForestGameMode.h"
#include "UI/MainUI.h"
#include "UI/BloodUI.h"
#include "Interface/GameStart.h"
#include "Kismet/GameplayStatics.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "UI/ArmUI.h"

APlayerController* AForestGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	const bool bVR = UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled();
	if (bVR)
	//if (true)
	{
		DefaultPawnClass = VRPawn;
		//DefaultPawnClass = AVRCharacter::StaticClass();
		//PlayerControllerClass = VRPlayerControllerClass;
	}
	return Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);

}
void AForestGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (BloodWidgetClass != nullptr)
	{
		BloodUI = CreateWidget<UBloodUI>(GetWorld(), BloodWidgetClass);
		if (BloodUI != nullptr)
		{
			BloodUI->AddToViewport();
		}
	}

	bGamePlay = true;
}

void AForestGameMode::Tick(float DeltaSeconds)
{
	if (!bGamePlay) { return; }


	if (PlayerPoint > 100.0f)
	{
		return;
	}


	PlayerPoint += DeltaSeconds;

	if (BloodUI)
	{
		BloodUI->SetBloodUI(PlayerPoint);
	}
	


	if (ArmUI)
	{
		ArmUI->SetPercent(PlayerPoint * 0.01f);
	}
}

void AForestGameMode::TakeDamageCharacter()
{
	if (!bGamePlay) { return; }

	PlayerPoint -= 10.0f;

	if (PlayerPoint <= 0.0f)
	{
		GameOver();
	}

}

void AForestGameMode::AddOrb()
{
	OrbCount++;

	if (OrbCount == GoalCount)
	{
		GameClear();
	}

	if (ArmUI)
	{
		ArmUI->SetCount(OrbCount);
	}
}

void AForestGameMode::GameStart()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UGameStart::StaticClass(), FoundActors);
	
	for (AActor* Actor : FoundActors)
	{
		IGameStart* Interface = Cast<IGameStart>(Actor);
		if (Interface)
		{
			Interface->ForestGameStart();
		}
	}


	if (ArmUI)
	{
		ArmUI->SetPercent(1);
		ArmUI->SetCount(0);
	}


}

void AForestGameMode::GameClear()
{
	if (!bGamePlay) { return; }
	if (MainUI)
	{
		MainUI->ShowGameClear();
	}
	bGamePlay = false;
}

void AForestGameMode::GameOver()
{
	if (!bGamePlay) { return; }
	if (MainUI)
	{
		MainUI->ShowGameOver();
	}
	
	bGamePlay = false;
}


