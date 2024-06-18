// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArmUI.generated.h"

/**
 * 
 */
UCLASS()
class UE_FOREST_API UArmUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void BeginPlay();
public:

	UPROPERTY(EditAnywhere, meta = (BindWdiget))
	class UTextBlock* CurrentCount;

	UPROPERTY(EditAnywhere, meta = (BindWdiget))
	class UProgressBar* HpBar;

public:

	void SetCount(int8 Count);
	void SetPercent(float Percent);
};
