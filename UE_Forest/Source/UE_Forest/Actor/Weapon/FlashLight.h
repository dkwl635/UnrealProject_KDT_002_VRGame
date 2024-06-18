// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/VRGrabItem.h"
#include "FlashLight.generated.h"

UCLASS()
class UE_FOREST_API AFlashLight : public AActor , public IVRGrabItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlashLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	FAttachPos AttachPos_R;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	FAttachPos AttachPos_L;
	bool bHave = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	class UMaterialInterface* OriginalMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = true))
	TSubclassOf<class UVRHandAnimInstance> HandAnimClass = nullptr;

	void CheckGrab(bool InHand) override;
	void Grab(UVRHandSkeletalMeshComponent* Hand) override;
	void VRTriggerStart() override;
	void VRTrigger(float ActionValue) override;
	void VRTriggerCompleted() override;
	void Release() override;
	void VRAction1() override;
	void VRAction2() override;
	void VRStick() override;
	class TSubclassOf <class UVRHandAnimInstance > GetHandAnimClass() override;
	virtual bool CheckHave() override;

	UFUNCTION(BlueprintImplementableEvent)
	void Attach_Receive();

	UFUNCTION(BlueprintImplementableEvent)
	void Detach_Receive();


	 
};
