// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ForestGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UE_FOREST_API AForestGameMode : public AGameMode
{
	GENERATED_BODY()
	
protected:
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

public:
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APawn> DefaultPawn = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APawn> VRPawn = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APlayerController> DefaultPlayerControllerClass = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APlayerController> VRPlayerControllerClass = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> MainUIWidgetClass = nullptr;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AActor* ForestCharacter = nullptr;

	int8 GoalCount = 5;
	int8 OrbCount = 0;

private:
	class UMainUI* MainUI;

	bool bGamePlay = false;
public :
	float PlayerPoint = 100.0f;
	class UArmUI* ArmUI;

public:
	virtual void Tick(float DeltaSeconds) override;

public:

	void TakeDamageCharacter();

	
	void AddOrb();

	UFUNCTION(BlueprintCallable)
	void GameStart();
	void GameClear();
	void GameOver();

};
