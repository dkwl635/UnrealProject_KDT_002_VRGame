// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainUI.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Slate/SlateGameResources.h"

void UMainUI::SetBloodUI(float PlayerPoint)
{
	float a = (100.0f - PlayerPoint);
	if (a < 0.0f)
	{
		a = 0;
	}
	else
	{
		a = a / 100.0f;
	}

    if (Blood)
    {
		 FLinearColor NewColor = FLinearColor(1.0f, 0.0f, 0.0f ,a);
		 Blood->SetBrushTintColor(NewColor);
    }
}

void UMainUI::ShowGameOver()
{
	GameOverTextBlock->SetVisibility(ESlateVisibility::Visible);
}

void UMainUI::ShowGameClear()
{
	GameClearTextBlock->SetVisibility(ESlateVisibility::Visible);
}

