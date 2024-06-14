// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "Input/InputData.h"

#include "VRHandSkeletalMeshComponent.generated.h"

/**
 * 
 */
UCLASS()
class UE_FOREST_API UVRHandSkeletalMeshComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
public:

	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UVRHandAnimInstance* HandAnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UVRHandsAnimationInputDataConfig* InputData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bMirror = false;


public:
	enum EHandType
	{
		Left,
		Right
	};

	void SetupPlayerInputComponent( UEnhancedInputComponent* InputComponent);

	bool ControllerGrab = false;
	void OnGrabStarted(const FInputActionValue& InputActionValue);
	void OnGrabTriggered(const FInputActionValue& InputActionValue);
	void OnGrabCompleted(const FInputActionValue& InputActionValue);

	bool ControllerPoint = false;
	void OnPointStarted(const FInputActionValue& InputActionValue);
	void OnPointTriggered(const FInputActionValue& InputActionValue);
	void OnPointCompleted(const FInputActionValue& InputActionValue);


	void OnIndexCurlTriggered(const FInputActionValue& InputActionValue);
	void OnIndexCurlCompleted(const FInputActionValue& InputActionValue);
	bool ControllerThumb = false;
	void OnThumbStarted(const FInputActionValue& InputActionValue);
	void OnThumbCompleted(const FInputActionValue& InputActionValue);

	EHandType HandType = (EHandType)-1;

public:
	UPROPERTY(VisibleAnywhere , BlueprintReadOnly)
	bool IsGrab = false;

	class IVRGrabItem* GrabItem = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AActor* EnterActor = nullptr;


	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void TryGrab();


};
