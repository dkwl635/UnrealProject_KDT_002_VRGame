// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable , BlueprintType)
class UE_FOREST_API UInputData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	UInputMappingContext* InputMappingContext = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* Move = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* Look = nullptr;
};

UCLASS(Blueprintable, BlueprintType)
class UE_FOREST_API UVRInputData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputMappingContext* InputMappingContext = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* IA_Grab_Left = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* IA_Grab_Right = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* IA_Point_Left = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* IA_Point_Right = nullptr;
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* IA_IndexCurl_Left = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* IA_IndexCurl_Right = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* IA_Thumb_Left = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* IA_Thumb_Right = nullptr;*/

};

UCLASS(Blueprintable, BlueprintType)
class UE_FOREST_API UVRHandsAnimationInputDataConfig : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputMappingContext* InputMappingContext = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* IA_Grab_Left = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* IA_Grab_Right = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* IA_Point_Left = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* IA_Point_Right = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* IA_IndexCurl_Left = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* IA_IndexCurl_Right = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* IA_Thumb_Left = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInputAction* IA_Thumb_Right = nullptr;
};