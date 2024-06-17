// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Components/VRHandSkeletalMeshComponent.h"
#include "VRGrabItem.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UVRGrabItem : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UE_FOREST_API IVRGrabItem
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual class TSubclassOf<class UVRHandAnimInstance> GetHandAnimClass() { return nullptr; }
	virtual void CheckGrab(bool InHand) = 0;
	virtual void Grab(UVRHandSkeletalMeshComponent* Hand) = 0;
	virtual void VRTriggerStart() = 0;
	virtual void VRTrigger(float ActionValue) = 0;
	virtual void VRTriggerCompleted() = 0;
	virtual void Release() = 0;
	virtual void VRAction1() = 0;
	virtual void VRAction2() = 0;
	virtual void VRStick() = 0;
	virtual bool CheckHave() { return false; }
	
};
