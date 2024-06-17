// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/VRUWidgetInteractionComponent.h"
#include "NiagaraComponent.h"

void UVRUWidgetInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	NS_Beam = Cast<UNiagaraComponent>(GetChildComponent(0));
}

void UVRUWidgetInteractionComponent::CheckGrab(bool InHand)
{
}

void UVRUWidgetInteractionComponent::Grab(UVRHandSkeletalMeshComponent* Hand)
{
}

void UVRUWidgetInteractionComponent::VRTriggerStart()
{
}

void UVRUWidgetInteractionComponent::VRTrigger(float ActionValue)
{
	if (!bShow) { return; }
	if (bTrigger) { return; }

	if (FMath::IsNearlyEqual(ActionValue, 1))
	{
		bTrigger = true;
		Trigger();
	}

}

void UVRUWidgetInteractionComponent::VRTriggerCompleted()
{
	bTrigger = false;
	ReleasePointerKey(EKeys::LeftMouseButton);
}

void UVRUWidgetInteractionComponent::Release()
{
}

void UVRUWidgetInteractionComponent::VRAction1()
{
}

void UVRUWidgetInteractionComponent::VRAction2()
{
}

void UVRUWidgetInteractionComponent::VRStick()
{
}

void UVRUWidgetInteractionComponent::Trigger()
{
	PressPointerKey(EKeys::LeftMouseButton);
}

void UVRUWidgetInteractionComponent::Show()
{
	bShow = true;
	
	this->SetVisibility(bShow);
	NS_Beam->SetVisibility(bShow);
}

void UVRUWidgetInteractionComponent::Hide()
{
	bShow = false;

	this->SetVisibility(bShow);
	NS_Beam->SetVisibility(bShow);
}
