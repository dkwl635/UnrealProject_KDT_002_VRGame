// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_Attack.h"
#include "Interface/Attack.h"
#include "Actor/Monster/ForestAiController.h"

UBTDecorator_Attack::UBTDecorator_Attack()
{
	NodeName = "Check_Attack";
}

bool UBTDecorator_Attack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	IAttack* Attack = Cast<IAttack>(OwnerComp.GetAIOwner()->GetPawn());
	if (Attack)
	{
		return Attack->IsAttackable();
	}
	return false;
}

UBTDecorator_IsDie::UBTDecorator_IsDie()
{
	NodeName = "Check_IsDie";
}

bool UBTDecorator_IsDie::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	IAttack* Attack = Cast<IAttack>(OwnerComp.GetAIOwner()->GetPawn());
	if (Attack)
	{
		return Attack->IsDie();
	}
	return false;
}
