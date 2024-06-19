// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interface/Attack.h"
#include "Interface/GameStart.h"
#include "ForestMonster.generated.h"

UCLASS()
class UE_FOREST_API AForestMonster : public APawn , public IAttack , public IGameStart
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AForestMonster();


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* AttackBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UFloatingPawnMovement* FloatingPawnMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMonsterAnimInstance* MonsterAnimInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAudioComponent* StepAudioComponent;

public:
	class AForestGameMode* GameMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InitSpeed = 300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxSpeed = 700.0;
private:
	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	float Speed = 0;

	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	bool IsInHitBoxCharacter = false;

	class AForestAiController* OnwerController = nullptr;
	class UBlackboardComponent* BlackboardComponent = nullptr;


	FName IsMoveKey = "IsMove";
	FName IsAttackKey = "IsAttack";
	FName TargetKey = "Target";

	class UMaterialInstanceDynamic* DynMaterial = nullptr;





	bool isDie = false;

	ECollisionEnabled::Type BodyOrginECollision;
	ECollisionEnabled::Type AttackBoxOrginECollision;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PossessedBy(class AController* NewController) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UFUNCTION(BlueprintCallable)
	void OnBeginLight();
	
	UFUNCTION(BlueprintCallable)
	void OnEndLight();

	UFUNCTION(BlueprintCallable)
	void OnBeginHitBox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void OnEndHitBox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void TakeDamageEvent();

	UFUNCTION(BlueprintImplementableEvent)
	void TakeSuccessDamage();

	void StartAttack()override;
	void OnAttack() override;
	void AttackDamage() override;
	bool IsAttackable() override;
	bool IsDie() override;
	void Spawn() override;

	///
	void Die();
	void MonsterDisable();
	void MonsterSpawn();
	UFUNCTION(BlueprintImplementableEvent)
	void MonsterSpawnEvent();

	void ForestGameStart() override;

};
