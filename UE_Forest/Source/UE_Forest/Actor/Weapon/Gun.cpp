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
	// 레이캐스트 시작과 끝 지점 설정
	FVector Start = SocketLocation;
	FVector End = Start + (ForwardVector * 1000.0f); // 1000 유닛 전방

	// 레이캐스트 히트 결과 구조체
	FHitResult HitResult;

	// 레이캐스트 파라미터 설정
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this); // 현재 액터 무시

	// 레이캐스트 수행
	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_GameTraceChannel6,
		CollisionParams
	);

	// 레이캐스트 결과 처리
	if (bHit)
	{
		UE_LOG(LogTemp, Log, TEXT("Hit: %s"), *HitResult.GetActor()->GetName());
		// 히트 지점까지 디버그 라인 그리기
		DrawDebugLine(GetWorld(), Start, HitResult.Location, FColor::Red, false, 2.0f, 0, 1.0f);
		// 히트 지점에 디버그 스피어 그리기
		DrawDebugSphere(GetWorld(), HitResult.Location, 10.0f, 12, FColor::Red, false, 2.0f);

		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			// 데미지 이벤트 보내기
			FDamageEvent DamageEvent;
			float DamageAmount = 10.0f;
			HitActor->TakeDamage(DamageAmount, DamageEvent, nullptr, this);
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("No Hit"));
		// 히트가 없을 때 끝 지점까지 디버그 라인 그리기
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


