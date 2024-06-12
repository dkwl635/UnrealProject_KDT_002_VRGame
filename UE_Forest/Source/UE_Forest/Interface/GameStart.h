// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameStart.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGameStart : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UE_FOREST_API IGameStart
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void ForestGameStart() = 0;
};
