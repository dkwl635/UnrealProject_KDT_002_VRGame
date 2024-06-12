// Fill out your copyright notice in the Description page of Project Settings.
#include "AI/BTN_Attack.h"
#include "Actor/Monster/ForestAiController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/Attack.h"


EBTNodeResult::Type UBTN_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return EBTNodeResult::Failed;

	FName TargetKey(TEXT("SelfActor"));

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetKey);


	IAttack* TargetAttack = Cast<IAttack>(Target);
	if (TargetAttack)
	{
		TargetAttack->StartAttack();
	}


	return EBTNodeResult::Succeeded;

}
