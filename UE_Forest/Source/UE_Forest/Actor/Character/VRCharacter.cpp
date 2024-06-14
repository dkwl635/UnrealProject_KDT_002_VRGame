// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Character/VRCharacter.h"
#include "Components/VRHandSkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputSubsystems.h"
#include  "Input/InputData.h"


AVRCharacter::AVRCharacter()
{
	FollowCamera->SetupAttachment(GetRootComponent());

	MotionControllerLeft = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerLeft"));
	MotionControllerRight = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionControllerRight"));

	MotionControllerLeft->SetTrackingMotionSource(LeftGrip);
	MotionControllerRight->SetTrackingMotionSource(RightGrip);
	MotionControllerLeft->SetupAttachment(GetRootComponent());
	MotionControllerRight->SetupAttachment(GetRootComponent());

	LeftHand = CreateDefaultSubobject<UVRHandSkeletalMeshComponent>(TEXT("LeftHand"));
	LeftHand->SetupAttachment(MotionControllerLeft);

	RightHand = CreateDefaultSubobject<UVRHandSkeletalMeshComponent>(TEXT("RightHand"));
	RightHand->SetupAttachment(MotionControllerRight);

	LeftHandCollision = CreateDefaultSubobject<USphereComponent>(TEXT("LeftHandCollision"));
	LeftHandCollision->SetupAttachment(LeftHand);
	LeftHandCollision->SetCollisionProfileName(TEXT("Hand"));
	LeftHandCollision->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	

	RightHandCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RightHandCollision"));
	RightHandCollision->SetupAttachment(RightHand);
	RightHandCollision->SetCollisionProfileName(TEXT("Hand"));
	RightHandCollision->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

	const FTransform RTransform = FTransform(FRotator(25.0, 0.0, 90.0), FVector(-2.98, 3.5, 4.56));
	RightHand->SetRelativeTransform(RTransform);

	const FTransform LTransform = FTransform(FRotator(-25.0, 180.0, 90.0), FVector(-2.98, -3.5, 4.56));
	LeftHand->SetRelativeTransform(LTransform);

	LeftHand->bMirror = true;

	{
		/*LeftHandWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("LeftHandWidget"));
		LeftHandWidget->SetupAttachment(MotionControllerLeft);

		FTransform Transform = FTransform(
			FRotator(58.7, 180.0, 0.0),
			FVector(20.0, -12.0, -1.8),
			FVector(0.05, 0.05, 0.05));
		LeftHandWidget->SetRelativeTransform(Transform);
		LeftHandWidget->SetDrawSize(FVector2D(800.0, 800.0));*/
	}

}

void AVRCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	
		Subsystem->AddMappingContext(LeftHand->InputData->InputMappingContext, 1);
	}
	else {  }
}

void AVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (!MoveInputData) { return; }

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(MoveInputData->Move, ETriggerEvent::Triggered, this, &AVRCharacter::OnVRMove);

		// Looking
		//EnhancedInputComponent->BindAction(MoveInputData->Look, ETriggerEvent::Triggered, this, &AForestCharacter::Look);

		LeftHand->SetupPlayerInputComponent(EnhancedInputComponent);
		RightHand->SetupPlayerInputComponent(EnhancedInputComponent);
	//OnComponentBeginOverlap
		RightHandCollision->OnComponentBeginOverlap.AddDynamic(RightHand ,&UVRHandSkeletalMeshComponent::OnOverlapBegin);
		LeftHandCollision->OnComponentBeginOverlap.AddDynamic(LeftHand ,&UVRHandSkeletalMeshComponent::OnOverlapBegin);
	//OnComponentEndOverlap
		RightHandCollision->OnComponentEndOverlap.AddDynamic(RightHand, &UVRHandSkeletalMeshComponent::OnOverlapEnd);
		LeftHandCollision->OnComponentEndOverlap.AddDynamic(LeftHand, &UVRHandSkeletalMeshComponent::OnOverlapEnd);

	}
	else
	{

	}
	/*UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	if(BasicInputDataConfig)
	{
		UBasicInputDataConfig* Input = (UBasicInputDataConfig*)(BasicInputDataConfig);
		EnhancedInputComponent->BindAction(Input->Move, ETriggerEvent::Triggered, this, &ThisClass::OnVRMove);
	}*/

	

	//if(VRHandsInputDataConfig)
	//{
	//	UVRHandsInputDataConfig* VRInput = (UVRHandsInputDataConfig*)(VRHandsInputDataConfig);
	//
	//	EnhancedInputComponent->BindAction(VRInput->IA_Grab_Right, ETriggerEvent::Started, this, &ThisClass::OnGrabRightStarted);
	//	EnhancedInputComponent->BindAction(VRInput->IA_Grab_Right, ETriggerEvent::Completed, this, &ThisClass::OnGrabRightCompleted);
	//	
	//	EnhancedInputComponent->BindAction(VRInput->IA_Grab_Left, ETriggerEvent::Started, this, &ThisClass::OnGrabLeftStarted);
	//	EnhancedInputComponent->BindAction(VRInput->IA_Grab_Left, ETriggerEvent::Completed, this, &ThisClass::OnGrabLeftCompleted);


	//}
	{
		//HandGraphLeft->SetupPlayerInputComponent(MotionControllerLeft, EnhancedInputComponent);
		//HandGraphRight->SetupPlayerInputComponent(MotionControllerRight, EnhancedInputComponent);
	}
}

void AVRCharacter::OnVRMove(const FInputActionValue& InputActionValue)
{

	const FVector2D ActionValue = InputActionValue.Get<FVector2D>();

	const FRotator CameraRotator = FollowCamera->GetRelativeRotation();
	const FRotator CameraYawRotator = FRotator(0., CameraRotator.Yaw, 0.);

	if (!FMath::IsNearlyZero(ActionValue.Y))
	{
		const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(CameraYawRotator);
		AddMovementInput(ForwardVector, ActionValue.Y);
	}

	if (!FMath::IsNearlyZero(ActionValue.X))
	{
		const FVector RightVector = UKismetMathLibrary::GetRightVector(CameraYawRotator);
		AddMovementInput(RightVector, ActionValue.X);
	}
}

void AVRCharacter::OnGrabStarted(UMotionControllerComponent* MotionControllerComponent, const bool bLeft, const FInputActionValue& InputActionValue)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.f, FColor::Red, TEXT("OnGrabStarted"));
}

void AVRCharacter::OnGrabCompleted(UMotionControllerComponent* MotionControllerComponent, const bool bLeft, const FInputActionValue& InputActionValue)
{
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 5.f, FColor::Red, TEXT("OnGrabCompleted"));
}