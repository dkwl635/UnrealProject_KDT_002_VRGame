// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class UE_FOREST_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

public:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class USphereComponent* SphereComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* SkeletalMeshComponent;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UNiagaraComponent* NS_Beam;*/

private:
	UPROPERTY(VisibleAnywhere, Meta = (AllowPrivateAccess = true))
	class UWeaponAnimInstance* WeaponAnimInstance;

	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	int8 InitAmmo = 0;
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	int8 MaxAmmo = 0;
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	int8 Ammo = 0;
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	int8 MagazineAmmo = 0;
	UPROPERTY(EditAnywhere, Meta = (AllowPrivateAccess = true))
	int8 MaxMagazineAmmo = 0;

	

	FName SocketName = TEXT("MuzzleFlash");

public: 
	UFUNCTION(BlueprintCallable)
	void Shoot();

	UFUNCTION(BlueprintCallable)
	void Reload();

	UFUNCTION(BlueprintCallable)
	void AttachGun();
	
	UFUNCTION(BlueprintImplementableEvent)
	void AttachGun_Receive(); 
	
};
