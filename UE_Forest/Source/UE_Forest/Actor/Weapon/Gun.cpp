// Fill out your copyright notice in the Description page of Project Settings.
#include "Actor/Weapon/Gun.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "AnimInstance/WeaponAnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/DamageEvents.h"
#include "NiagaraComponent.h"

#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	//NS_Beam = CreateDefaultSubobject<UNiagaraComponent>("NS_Beam");

	SetRootComponent(SphereComponent);
	SkeletalMeshComponent->SetupAttachment(GetRootComponent());
	//NS_Beam->SetupAttachment(SkeletalMeshComponent);
	//NS_Beam->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetIncludingScale, "MuzzleFlash");
}

void AGun::BeginPlay()
{
	Super::BeginPlay();

	WeaponAnimInstance = Cast<UWeaponAnimInstance>(SkeletalMeshComponent->GetAnimInstance());
}



void AGun::Shoot()
{
	if (!WeaponAnimInstance) { return; }
	if (WeaponAnimInstance->IsAnyMontagePlaying()) { return; }
	if (!SkeletalMeshComponent->DoesSocketExist(SocketName)) { return; }

	if (MagazineAmmo <= 0)
	{
		return;
	}
	MagazineAmmo--;
	WeaponAnimInstance->Shoot();
	

	FVector SocketLocation = SkeletalMeshComponent->GetSocketLocation(SocketName);
	FVector ForwardVector = GetActorForwardVector();
\

	FVector Start = SocketLocation;
	FVector End = Start + (ForwardVector * 1000.0f); // 

	
	FHitResult HitResult;

	
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	// ����ĳ��Ʈ ����
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_GameTraceChannel6,
		CollisionParams
	);


	if (bHit)
	{
		UE_LOG(LogTemp, Log, TEXT("Hit: %s"), *HitResult.GetActor()->GetName());
	
		DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Red, false, 2.0f, 0, 1.0f);
	
		DrawDebugSphere(GetWorld(), HitResult.Location, 10.0f, 12, FColor::Red, false, 2.0f);

		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			// ������ �̺�Ʈ ������
			FDamageEvent DamageEvent;
			float DamageAmount = 10.0f;
			HitActor->TakeDamage(DamageAmount, DamageEvent, nullptr, this);
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("No Hit"));
	
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 2.0f, 0, 1.0f);
	}


}


void AGun::Reload()
{
	if (!WeaponAnimInstance) { return; }
	if (WeaponAnimInstance->IsAnyMontagePlaying()) { return; }
	if (Ammo <= 0)
	{
		return;
	}

	if (MagazineAmmo >= MaxMagazineAmmo)
	{
		return;
	}

	int8 Temp = MaxMagazineAmmo - MagazineAmmo;
	int8 AddMagazineAmmo = 0;
	if (Temp > Ammo)
	{
		AddMagazineAmmo = Ammo;
		Ammo = 0;
	}
	else
	{
		AddMagazineAmmo = Temp;
		Ammo -= Temp;
	}

	MagazineAmmo += Temp;
	WeaponAnimInstance->Reload();

}

void AGun::AttachGun()
{
	AttachGun_Receive();
}

void AGun::Grab(UVRHandSkeletalMeshComponent* Hand)
{
	AttachGun();
}

void AGun::VRTrigger(float ActionValue)
{
	if(bOneShoot)
	{
		return;
	}

	if (FMath::IsNearlyEqual(ActionValue, 1))
	{
		Shoot();
		bOneShoot = true;
	}


}
void AGun::VRTriggerStart()
{
}

void AGun::VRTriggerCompleted()
{
	bOneShoot = false;
}



void AGun::Release()
{
}

void AGun::VRAction1()
{
}

void AGun::VRAction2()
{
}

void AGun::VRStick()
{
}




