// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ForestAiController.generated.h"

/**
 * 
 */
UCLASS()
class UE_FOREST_API AForestAiController : public AAIController
{
	GENERATED_BODY()

public:
	AForestAiController();
	virtual void OnPossess(APawn* InPawn) override;  
	virtual void OnUnPossess() override;			

public:
	//static const FName TargetKey;
	//static const FName TargetActorKey;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBehaviorTree* BT;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBlackboardData* BBD;
private:

	//FTimerHandle RepeatTimerHandle;  
	//float RepeatInterval;


	
};
