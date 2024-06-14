// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Character/ForestCharacter.h"
#include "MotionControllerComponent.h"
#include "VRCharacter.generated.h"

/**
 * 
 */
static inline const FName LeftGrip = TEXT("LeftGrip");
static inline const FName RightGrip = TEXT("RightGrip");


UCLASS()
class UE_FOREST_API AVRCharacter : public AForestCharacter
{
	GENERATED_BODY()
	
public:

	AVRCharacter();

protected:
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//UFUNCTION(BlueprintCallable)
	//void SetLeftHandWidgetClass(TSubclassOf<UUserWidget> InWidgetClass);

	void OnVRMove(const FInputActionValue& InputActionValue);

	void OnGrabLeftStarted(const FInputActionValue& InputActionValue) { OnGrabStarted(MotionControllerLeft, true, InputActionValue); }
	void OnGrabRightStarted(const FInputActionValue& InputActionValue) { OnGrabStarted(MotionControllerRight, false, InputActionValue); }
	void OnGrabStarted(UMotionControllerComponent* MotionControllerComponent, const bool bLeft, const FInputActionValue& InputActionValue);

	void OnGrabLeftCompleted(const FInputActionValue& InputActionValue) { OnGrabCompleted(MotionControllerLeft, true, InputActionValue); }
	void OnGrabRightCompleted(const FInputActionValue& InputActionValue) { OnGrabCompleted(MotionControllerRight, false, InputActionValue); }
	void OnGrabCompleted(UMotionControllerComponent* MotionControllerComponent, const bool bLeft, const FInputActionValue& InputActionValue);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMotionControllerComponent* MotionControllerLeft;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UMotionControllerComponent* MotionControllerRight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UVRHandSkeletalMeshComponent* LeftHand;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UVRHandSkeletalMeshComponent* RightHand;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* LeftHandCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* RightHandCollision;
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputData* VRMoveInputData;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//class UObject* VRHandsInputDataConfig;
	//class UVRHandsInputDataConfig* VRHandsInputDataConfig;

	//
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//class UHandGraph* HandGraphLeft;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//class UHandGraph* HandGraphRight;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//class UWidgetComponent* LeftHandWidget;



};
