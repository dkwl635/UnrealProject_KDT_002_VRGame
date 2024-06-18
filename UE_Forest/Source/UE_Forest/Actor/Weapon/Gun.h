// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/VRGrabItem.h"
#include "Gun.generated.h"




UCLASS()
class UE_FOREST_API AGun : public AActor , public IVRGrabItem
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
	
	bool bHave = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TSubclassOf<class UVRHandAnimInstance> HandAnimClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Meta = (AllowPrivateAccess = true))
	FAttachPos AttachPos_R;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Meta = (AllowPrivateAccess = true))
	FAttachPos AttachPos_L;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	class UMaterialInterface* OriginalMaterial;



public: 
	bool bOneShoot = false;;
	UFUNCTION(BlueprintCallable)
	void Shoot();

	UFUNCTION(BlueprintCallable)
	void Reload();

	UFUNCTION(BlueprintCallable)
	void AttachGun();
	
	UFUNCTION(BlueprintImplementableEvent)
	void AttachGun_Receive(); 
	
		UFUNCTION(BlueprintImplementableEvent)
	void DetachGun_Receive();



	// IVRGrabItem을(를) 통해 상속됨
	class TSubclassOf <class UVRHandAnimInstance > GetHandAnimClass() override;
	void CheckGrab(bool InHand) override;
	void Grab(UVRHandSkeletalMeshComponent* Hand) override;
	void VRTrigger(float ActionValue) override;
	void VRTriggerStart() override;
	void VRTriggerCompleted() override;
	void Release() override;
	void VRAction1() override;
	void VRAction2() override;
	void VRStick() override;
	bool CheckHave() override;



	// IVRGrabItem을(를) 통해 상속됨

};
