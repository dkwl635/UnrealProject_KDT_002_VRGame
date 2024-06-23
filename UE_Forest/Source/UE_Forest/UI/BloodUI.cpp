// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/BloodUI.h"
#include "Components/Image.h"

void UBloodUI::SetBloodUI(float PlayerPoint)
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
		FLinearColor NewColor = FLinearColor(1.0f, 0.0f, 0.0f, a);
		Blood->SetBrushTintColor(NewColor);
	}
}
