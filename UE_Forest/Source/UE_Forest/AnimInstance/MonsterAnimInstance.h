// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Interface/Attack.h"
#include "MonsterAnimInstance.generated.h"

/**
 * 
 */
DECLARE_DELEGATE(FOnDieDelegate);

UCLASS()
class UE_FOREST_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;

	void StartAttackMontage();

public:
	UFUNCTION()
	void AnimNotify_AttackHitCheck();
	UFUNCTION()
	void AnimNotify_PlayParticleEffect();

	UFUNCTION()
	void AnimNotify_DieEvenet();
public:
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	class UAnimMontage* AttackMontage;

public:

	IAttack* AttackEvent = nullptr;
	FOnDieDelegate DieEvenet;
};
