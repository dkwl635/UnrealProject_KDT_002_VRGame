#include "VRHandSkeletalMeshComponent.h"
#include "AnimInstance/VRHandAnimInstance.h"
#include "Interface/VRGrabItem.h"
#include "MotionControllerComponent.h"
#include "EnhancedInputSubsystemInterface.h"
#include "Components/WidgetInteractionComponent.h"
#include "Components/VRUWidgetInteractionComponent.h"


UVRHandSkeletalMeshComponent::UVRHandSkeletalMeshComponent()
{
	
	/*VRUWidgetInteractionComponent = CreateDefaultSubobject<UVRUWidgetInteractionComponent>("VRUWidgetInteractionComponent");
	VRUWidgetInteractionComponent->SetupAttachment(this);*/

}

void UVRHandSkeletalMeshComponent::BeginPlay()
{
	Super::BeginPlay();

	HandAnimInstance = Cast<UVRHandAnimInstance>(GetAnimInstance());
	OrginHandAnimClass = AnimClass;


	//VRUWidgetInteractionComponent->SetupAttachment(this);
}

void UVRHandSkeletalMeshComponent::SetupPlayerInputComponent(UEnhancedInputComponent* InputComponent)
{
	//EnhancedInputLocalPlayerSubsystem->AddMappingContext(InputData->InputMappingContext,1);
	HandType =  bMirror ? EHandType::Left : EHandType::Right;
	
	UInputAction* IA_Grab = HandType == EHandType::Left ? InputData->IA_Grab_Left : InputData->IA_Grab_Right;
	UInputAction* IA_Point = HandType == EHandType::Left ? InputData->IA_Point_Left : InputData->IA_Point_Right;
	UInputAction* IA_IndexCurl = HandType == EHandType::Left ? InputData->IA_IndexCurl_Left : InputData->IA_IndexCurl_Right;
	UInputAction* IA_Thumb = HandType == EHandType::Left ? InputData->IA_Thumb_Left : InputData->IA_Thumb_Right;
	UInputAction* IA_Action1 = HandType == EHandType::Left ? InputData->IA_Action1_Left : InputData->IA_Action1_Right;
	UInputAction* IA_Action2 = HandType == EHandType::Left ? InputData->IA_Action2_Left : InputData->IA_Action2_Right;

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


	InputComponent->BindAction(IA_Action1, ETriggerEvent::Started, this, &UVRHandSkeletalMeshComponent::OnAction1Trigger);
	InputComponent->BindAction(IA_Action2, ETriggerEvent::Started, this, &UVRHandSkeletalMeshComponent::OnAction2Trigger);

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

	if (IsGrab)
	{
		if (GrabItem)
		{
			GrabItem->VRTrigger(ActionValue);
		}
	}
	else
	{
		if (VRUWidgetInteractionComponent)
		{
			VRUWidgetInteractionComponent->VRTrigger(ActionValue);
		}
	}
}

void UVRHandSkeletalMeshComponent::OnIndexCurlCompleted(const FInputActionValue& InputActionValue)
{
	HandAnimInstance->PoseAlphaIndexCurl = 0.f;
	if (IsGrab)
	{
		if (GrabItem)
		{
			GrabItem->VRTriggerCompleted();
		}
	}
	else
	{
		if (VRUWidgetInteractionComponent)
		{
			VRUWidgetInteractionComponent->VRTriggerCompleted();
		}
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

void UVRHandSkeletalMeshComponent::OnAction1Trigger(const FInputActionValue& InputActionValue)
{

	if (IsGrab)
	{
		if (GrabItem)
		{
			GrabItem->VRAction1();
		}
	}

	
}

void UVRHandSkeletalMeshComponent::OnAction2Trigger(const FInputActionValue& InputActionValue)
{
	if (IsGrab)
	{
		if (GrabItem)
		{
			GrabItem->VRAction2();

			DropGrab();
		}
	}
	}

void UVRHandSkeletalMeshComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (EnterActor == nullptr)
	{
		GrabItem = Cast<IVRGrabItem>(OtherActor);
		if (GrabItem == nullptr) { return; }
		if (GrabItem->CheckHave()) { return; }
		
		EnterActor = OtherActor;
		GrabItem->CheckGrab(true);
		
	}
}

void UVRHandSkeletalMeshComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (EnterActor == OtherActor)
	{
		EnterActor = nullptr;
		if (GrabItem)
		{
			GrabItem->CheckGrab(false);
			GrabItem = nullptr;
		}
	}
}

void UVRHandSkeletalMeshComponent::TryGrab()
{
	if (IsGrab || EnterActor == nullptr)
	{
		return;
	}
	{
		if (GrabItem->CheckHave()) {
			
			EnterActor = nullptr;
			GrabItem = nullptr;
			
			return; 
		}
	

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

		if (GrabItem)
		{
			GrabItem->Grab(this);

			if (GrabItem->GetHandAnimClass())
			{
				SetAnimClass(GrabItem->GetHandAnimClass());
				HandAnimInstance = Cast<UVRHandAnimInstance>(GetAnimInstance());
			}
			if (VRUWidgetInteractionComponent)
			{
				VRUWidgetInteractionComponent->Hide();
			}
		
		}
		
	}

}

void UVRHandSkeletalMeshComponent::DropGrab()
{
	SetAnimClass(OrginHandAnimClass);
	HandAnimInstance = Cast<UVRHandAnimInstance>(GetAnimInstance());

	if (VRUWidgetInteractionComponent)
	{
		VRUWidgetInteractionComponent->Show();
	}
	
	IsGrab = false;
	EnterActor = nullptr;
	GrabItem = nullptr;
	
}
