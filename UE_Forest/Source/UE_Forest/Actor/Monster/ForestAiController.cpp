// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Monster/ForestAiController.h"

AForestAiController::AForestAiController()
{
}

void AForestAiController::OnPossess(APawn* InPawn)
{
	//RunBehaviorTree(BT);
	Super::OnPossess(InPawn);

}

void AForestAiController::OnUnPossess()
{
	Super::OnUnPossess();
}
