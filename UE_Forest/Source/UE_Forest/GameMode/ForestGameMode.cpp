// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/ForestGameMode.h"
#include "UI/MainUI.h"
#include	"Interface/GameStart.h"
#include "Kismet/GameplayStatics.h"
#include "HeadMountedDisplayFunctionLibrary.h"
APlayerController* AForestGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	const bool bVR = UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled();
	//if (bVR)
	if (true)
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

	if (MainUIWidgetClass != nullptr)
	{
		MainUI = CreateWidget<UMainUI>(GetWorld(), MainUIWidgetClass);
		if (MainUI != nullptr)
		{
			MainUI->AddToViewport();
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
	MainUI->SetBloodUI(PlayerPoint);
}

void AForestGameMode::TakeDamageCharacter()
{

	PlayerPoint -= 10.0f;
	MainUI->SetBloodUI(PlayerPoint);

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


