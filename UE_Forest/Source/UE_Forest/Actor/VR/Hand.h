// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Hand.generated.h"

UCLASS()
class UE_FOREST_API AHand : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHand();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* SphereComponent;

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UMotionControllerComponent* MotionControllerComponent;



};
