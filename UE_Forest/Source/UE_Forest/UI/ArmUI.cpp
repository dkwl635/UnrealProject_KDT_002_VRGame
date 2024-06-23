// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/ArmUI.h"
#include "GameMode/ForestGameMode.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UArmUI::BeginPlay()
{

	AForestGameMode* GameMode = Cast<AForestGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->ArmUI = this;
	}

}

void UArmUI::SetCount(int8 Count)
{
	CurrentCount->SetText(FText::FromString(FString::FromInt(Count)));
}

void UArmUI::SetPercent(float Percent)
{
	HpBar->SetPercent(Percent);
}
