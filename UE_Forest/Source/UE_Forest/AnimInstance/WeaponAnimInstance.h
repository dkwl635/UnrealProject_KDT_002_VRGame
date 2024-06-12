// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "WeaponAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE_FOREST_API UWeaponAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	void Shoot();
	void Reload();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	class UAnimMontage* ShootMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	class UAnimMontage* ReloadMontage;

};
