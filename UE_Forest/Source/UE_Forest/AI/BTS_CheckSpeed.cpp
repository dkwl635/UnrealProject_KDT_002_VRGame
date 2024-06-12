// Fill out your copyright notice in the Description page of Project Settings.

#include "BTS_CheckSpeed.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"



void UBTS_CheckSpeed::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// Get the AI Controller
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		// Get the controlled Pawn
		APawn* ControlledPawn = AIController->GetPawn();
		if (ControlledPawn)
		{
			// Check the speed of the Pawn
			FVector Velocity = ControlledPawn->GetVelocity();
			float Speed = Velocity.Size();

			if (Speed == 0.0f)
			{
				// Set the Blackboard key to indicate failure (you should have a key for this purpose)
				UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
				if (BlackboardComp)
				{
					// Assuming you have a key named "ShouldFail" in your blackboard
					BlackboardComp->SetValueAsBool(TEXT("ShouldFail"), true);
				}
			}
		}
	}
}