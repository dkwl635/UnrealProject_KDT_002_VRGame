// Fill out your copyright notice in the Description page of Project Settings.
#include "AI/BTT_Spanw.h"
#include "Actor/Monster/ForestAiController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interface/Attack.h"

EBTNodeResult::Type UBTT_Spanw::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	IAttack* TargetAttack = Cast<IAttack>(ControllingPawn);
	if (TargetAttack)
	{
		TargetAttack->Spawn();
	}


	return EBTNodeResult::Succeeded;
}
