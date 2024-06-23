// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BloodUI.generated.h"

/**
 * 
 */
UCLASS()
class UE_FOREST_API UBloodUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UImage* Blood;

public:

	void SetBloodUI(float PlayerPoint);

	
	
};
