// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainUI.h"

#include "Components/CanvasPanel.h"
#include "Slate/SlateGameResources.h"
#include "GameMode/ForestGameMode.h"


void UMainUI::BeginPlay()
{
	AForestGameMode* GameMode = Cast<AForestGameMode>( GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->MainUI = this;
	}
}

void UMainUI::ShowGameOver()
{
	LosePanel->SetVisibility(ESlateVisibility::Visible);
	ButtonPanel->SetVisibility(ESlateVisibility::Visible);
}

void UMainUI::ShowGameClear()
{
	WinPanel->SetVisibility(ESlateVisibility::Visible);
	ButtonPanel->SetVisibility(ESlateVisibility::Visible);
}

