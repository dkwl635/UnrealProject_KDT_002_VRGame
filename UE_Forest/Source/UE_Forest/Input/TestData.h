// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnhancedInputComponent.h"
#include "TestData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class UE_FOREST_API UTestData : public UDataAsset
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TestInt = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* InputMappingContext = nullptr;
	
};
