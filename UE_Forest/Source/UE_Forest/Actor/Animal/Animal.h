// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interface/GameStart.h"
#include "Animal.generated.h"


UCLASS()
class UE_FOREST_API AAnimal : public APawn, public IGameStart
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAnimal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* CapsuleComponent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UFloatingPawnMovement* FloatingPawnMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MapSize;
	

public:
	AActor** Target;
public:

	UFUNCTION(BlueprintCallable)
	FVector GetNextMovePos();

	UFUNCTION(BlueprintCallable)
	FVector GetNextSpawnPos();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void MoveToStart();
	
	// IGameStart
	void ForestGameStart() override;
	void ForestGameEnd() override;

};
