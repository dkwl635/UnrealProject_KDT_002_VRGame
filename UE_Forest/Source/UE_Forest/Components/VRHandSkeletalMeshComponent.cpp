#include "VRHandSkeletalMeshComponent.h"
#include "AnimInstance/VRHandAnimInstance.h"
#include "Interface/VRGrabItem.h"
#include "MotionControllerComponent.h"
#include "EnhancedInputSubsystemInterface.h"


void UVRHandSkeletalMeshComponent::BeginPlay()
{
	Super::BeginPlay();

	HandAnimInstance = Cast<UVRHandAnimInstance>(GetAnimInstance());

}

void UVRHandSkeletalMeshComponent::SetupPlayerInputComponent(UEnhancedInputComponent* InputComponent)
{
	//EnhancedInputLocalPlayerSubsystem->AddMappingContext(InputData->InputMappingContext,1);
	HandType =  bMirror ? EHandType::Left : EHandType::Right;
	
	UInputAction* IA_Grab = HandType == EHandType::Left ? InputData->IA_Grab_Left : InputData->IA_Grab_Right;
	UInputAction* IA_Point = HandType == EHandType::Left ? InputData->IA_Point_Left : InputData->IA_Point_Right;
	UInputAction* IA_IndexCurl = HandType == EHandType::Left ? InputData->IA_IndexCurl_Left : InputData->IA_IndexCurl_Right;
	UInputAction* IA_Thumb = HandType == EHandType::Left ? InputData->IA_Thumb_Left : InputData->IA_Thumb_Right;

	InputComponent->BindAction(IA_Grab, ETriggerEvent::Triggered, this, &UVRHandSkeletalMeshComponent::OnGrabTriggered);
	InputComponent->BindAction(IA_Grab, ETriggerEvent::Canceled, this, &UVRHandSkeletalMeshComponent::OnGrabCompleted);
	InputComponent->BindAction(IA_Grab, ETriggerEvent::Completed, this, &UVRHandSkeletalMeshComponent::OnGrabCompleted);

	InputComponent->BindAction(IA_Point, ETriggerEvent::Started, this, &UVRHandSkeletalMeshComponent::OnPointStarted);
	InputComponent->BindAction(IA_Point, ETriggerEvent::Canceled, this, &UVRHandSkeletalMeshComponent::OnPointStarted);
	InputComponent->BindAction(IA_Point, ETriggerEvent::Completed, this, &UVRHandSkeletalMeshComponent::OnPointCompleted);

	InputComponent->BindAction(IA_IndexCurl, ETriggerEvent::Triggered, this, &UVRHandSkeletalMeshComponent::OnIndexCurlTriggered);
	InputComponent->BindAction(IA_IndexCurl, ETriggerEvent::Canceled, this, &UVRHandSkeletalMeshComponent::OnIndexCurlCompleted);
	InputComponent->BindAction(IA_IndexCurl, ETriggerEvent::Completed, this, &UVRHandSkeletalMeshComponent::OnIndexCurlCompleted);

	InputComponent->BindAction(IA_Thumb, ETriggerEvent::Started, this, &UVRHandSkeletalMeshComponent::OnThumbStarted);
	InputComponent->BindAction(IA_Thumb, ETriggerEvent::Canceled, this, &UVRHandSkeletalMeshComponent::OnThumbStarted);
	InputComponent->BindAction(IA_Thumb, ETriggerEvent::Completed, this, &UVRHandSkeletalMeshComponent::OnThumbCompleted);

}


void UVRHandSkeletalMeshComponent::OnGrabTriggered(const FInputActionValue& InputActionValue)
{
	const float ActionValue = InputActionValue.Get<float>();
	HandAnimInstance->PoseAlphaGrap = ActionValue;

	
	if (!ControllerGrab && FMath::IsNearlyEqual(ActionValue,1))
	{
		TryGrab();
		ControllerGrab = true;
	}

}
void UVRHandSkeletalMeshComponent::OnGrabStarted(const FInputActionValue& InputActionValue)
{
	HandAnimInstance->PoseAlphaGrap = 0.f;
}

void UVRHandSkeletalMeshComponent::OnGrabCompleted(const FInputActionValue& InputActionValue)
{
	HandAnimInstance->PoseAlphaGrap = 0.f;
	
	ControllerGrab = false;
}

void UVRHandSkeletalMeshComponent::OnPointStarted(const FInputActionValue& InputActionValue)
{
	HandAnimInstance->PoseAlphaPoint = 0.f;
}

void UVRHandSkeletalMeshComponent::OnPointTriggered(const FInputActionValue& InputActionValue)
{
}

void UVRHandSkeletalMeshComponent::OnPointCompleted(const FInputActionValue& InputActionValue)
{
	HandAnimInstance->PoseAlphaPoint = 0.f;
}

void UVRHandSkeletalMeshComponent::OnIndexCurlTriggered(const FInputActionValue& InputActionValue)
{
	const float ActionValue = InputActionValue.Get<float>();
	HandAnimInstance->PoseAlphaIndexCurl = ActionValue;

	if (GrabItem)
	{
		GrabItem->VRTrigger(ActionValue);
	}
}

void UVRHandSkeletalMeshComponent::OnIndexCurlCompleted(const FInputActionValue& InputActionValue)
{
	HandAnimInstance->PoseAlphaIndexCurl = 0.f;

	if (GrabItem)
	{
		GrabItem->VRTriggerCompleted();
	}
}

void UVRHandSkeletalMeshComponent::OnThumbStarted(const FInputActionValue& InputActionValue)
{
	HandAnimInstance->PoseAlphaThumb = 0.f;
}

void UVRHandSkeletalMeshComponent::OnThumbCompleted(const FInputActionValue& InputActionValue)
{
	HandAnimInstance->PoseAlphaThumb = 1.f;
}

void UVRHandSkeletalMeshComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (EnterActor == nullptr)
	{
		EnterActor = OtherActor;
	}
}

void UVRHandSkeletalMeshComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (EnterActor == OtherActor)
	{
		EnterActor = nullptr;
	}

}

void UVRHandSkeletalMeshComponent::TryGrab()
{
	if (IsGrab || EnterActor == nullptr)
	{
		return;
	}
	{
		//	FAttachmentTransformRules(EAttachmentRule InLocationRule, EAttachmentRule InRotationRule, EAttachmentRule InScaleRule, bool bInWeldSimulatedBodies)
		FAttachmentTransformRules Rules
		(
			EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true
		);

		FName SocketName = TEXT("ItemSocket_r");
		if (HandType == EHandType::Left)
		{
			SocketName = TEXT("ItemSocket_l");
		}
		


		EnterActor->AttachToComponent(this, Rules, SocketName);

		IsGrab = true;

		GrabItem = Cast<IVRGrabItem>(EnterActor);
		if (GrabItem)
		{
			GrabItem->Grab(this);
		}
		
	}

}
