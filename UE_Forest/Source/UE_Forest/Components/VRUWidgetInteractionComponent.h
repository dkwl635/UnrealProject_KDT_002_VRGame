// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetInteractionComponent.h"
#include "Interface/VRGrabItem.h"
#include "VRUWidgetInteractionComponent.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class UE_FOREST_API UVRUWidgetInteractionComponent : public UWidgetInteractionComponent , public IVRGrabItem
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

public:
	bool bTrigger = false;;

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


public:
	UPROPERTY(VisibleAnywhere , BlueprintReadWrite)
	bool bShow = false;
	void Trigger();
	void Show();
	void Hide();


	class UNiagaraComponent* NS_Beam;
};
