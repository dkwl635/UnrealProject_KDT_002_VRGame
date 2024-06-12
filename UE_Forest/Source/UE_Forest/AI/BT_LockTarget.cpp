// Fill out your copyright notice in the Description page of Project Settings.
#include "AI/BT_LockTarget.h"
#include "Actor/Monster/ForestAiController.h"
#include "GameMode/ForestGameMode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UBT_LockTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return EBTNodeResult::Failed;

	FName TargetKey(TEXT("Target"));

	UObject* Target =  OwnerComp.GetBlackboardComponent()->GetValueAsObject(TargetKey);
	if (!Target)
	{
		Target = Cast<AForestGameMode>(OwnerComp.GetWorld()->GetAuthGameMode())->ForestCharacter;
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetKey, Target);
	}

	AActor* TargetActor = Cast<AActor>(Target);

	FVector TargetLocation = TargetActor->GetActorLocation();

	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(ControllingPawn->GetActorLocation(), TargetLocation);
	LookAtRotation.Pitch = 0;

	ControllingPawn->SetActorRotation(LookAtRotation);


	return EBTNodeResult::Succeeded;


}
