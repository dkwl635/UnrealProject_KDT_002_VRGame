// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Attack.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAttack : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UE_FOREST_API IAttack
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void StartAttack() = 0;
	virtual void OnAttack() = 0;
	virtual void AttackDamage() = 0;
	virtual bool IsAttackable() = 0;
	virtual bool IsDie() = 0;
	virtual void Spawn() = 0;

};
