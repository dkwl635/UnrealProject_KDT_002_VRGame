// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/WeaponAnimInstance.h"

void UWeaponAnimInstance::Shoot()
{
	if (ShootMontage)
	{
		Montage_Play(ShootMontage);
	}
	
}

void UWeaponAnimInstance::Reload()
{
	if (ReloadMontage)
	{
		Montage_Play(ReloadMontage);
	}
}
