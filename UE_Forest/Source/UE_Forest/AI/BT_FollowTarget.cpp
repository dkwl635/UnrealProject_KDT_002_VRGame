// Fill out your copyright notice in the Description page of Project Settings.
#include "AI/BT_FollowTarget.h"
#include "Actor/Monster/ForestAiController.h"
#include "GameMode/ForestGameMode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UBT_FollowTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	FName TargetKey(TEXT("Target"));
	FName TargetPosKey(TEXT("TargetPos"));

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetKey);
	if (!Target)
	{
		Target = Cast<AForestGameMode>(OwnerComp.GetWorld()->GetAuthGameMode())->ForestCharacter;
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetKey, Target);
	}

	AActor* TargetActor = (AActor*)Target;

	FVector TargetLocation = TargetActor->GetActorLocation();
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetPosKey, TargetLocation);

	return EBTNodeResult::Succeeded;
}
