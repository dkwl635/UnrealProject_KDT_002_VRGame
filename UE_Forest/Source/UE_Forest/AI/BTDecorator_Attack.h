// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_Attack.generated.h"

/**
 * 
 */
UCLASS()
class UE_FOREST_API UBTDecorator_Attack : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBTDecorator_Attack();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};


UCLASS()
class UE_FOREST_API UBTDecorator_IsDie : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBTDecorator_IsDie();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
