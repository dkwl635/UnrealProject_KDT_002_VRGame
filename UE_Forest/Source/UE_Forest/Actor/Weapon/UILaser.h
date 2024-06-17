// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/VRGrabItem.h"
#include "UILaser.generated.h"

UCLASS()
class UE_FOREST_API AUILaser : public AActor , public IVRGrabItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUILaser();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UWidgetInteractionComponent* WidgetInteractionComponent;


	// IVRGrabItem을(를) 통해 상속됨
	void CheckGrab(bool InHand) override;

	void Grab(UVRHandSkeletalMeshComponent* Hand) override;

	void VRTriggerStart() override;

	void VRTrigger(float ActionValue) override;

	void VRTriggerCompleted() override;

	void Release() override;

	void VRAction1() override;

	void VRAction2() override;

	void VRStick() override;

};
