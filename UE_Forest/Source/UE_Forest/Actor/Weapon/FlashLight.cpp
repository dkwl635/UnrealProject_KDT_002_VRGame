// Fill out your copyright notice in the Description page of Project Settings.
#include "Actor/Weapon/FlashLight.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AnimInstance//VRHandAnimInstance.h"
// Sets default values
AFlashLight::AFlashLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");

	SetRootComponent(SphereComponent);
	StaticMeshComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AFlashLight::BeginPlay()
{
	Super::BeginPlay();
	
	OriginalMaterial = StaticMeshComponent->OverlayMaterial;
	StaticMeshComponent->SetOverlayMaterial(nullptr);
}

// Called every frame
void AFlashLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFlashLight::CheckGrab(bool InHand)
{
	if (InHand)
	{
		StaticMeshComponent->SetOverlayMaterial(OriginalMaterial);
	}
	else
	{
		StaticMeshComponent->SetOverlayMaterial(nullptr);
	}
}

void AFlashLight::Grab(UVRHandSkeletalMeshComponent* Hand)
{
	if (Hand->bMirror)
	{
		SetActorRelativeLocation(AttachPos_L.Pos);
		SetActorRelativeRotation(AttachPos_L.Rot);
	}
	else
	{
		SetActorRelativeLocation(AttachPos_R.Pos);
		SetActorRelativeRotation(AttachPos_R.Rot);
	}
	bHave = true;
	CheckGrab(false);
	Attach_Receive();
}

void AFlashLight::VRTriggerStart()
{
}

void AFlashLight::VRTrigger(float ActionValue)
{
}

void AFlashLight::VRTriggerCompleted()
{
}

void AFlashLight::Release()
{
	//DetachGun_Receive();
	SetActorRelativeLocation(FVector::ZeroVector);

	bHave = false;

	FDetachmentTransformRules DetachmentRules(EDetachmentRule::KeepWorld, true);
	this->DetachFromActor(DetachmentRules);


	SetActorRelativeRotation(FRotator::ZeroRotator);

	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	
	Detach_Receive();
}

void AFlashLight::VRAction1()
{
}

void AFlashLight::VRAction2()
{
	Release();
}

void AFlashLight::VRStick()
{
}

TSubclassOf<UVRHandAnimInstance> AFlashLight::GetHandAnimClass()
{
	return HandAnimClass;
}

bool AFlashLight::CheckHave()
{
	return bHave;
}

