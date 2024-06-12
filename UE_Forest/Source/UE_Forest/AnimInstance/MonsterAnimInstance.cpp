// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/MonsterAnimInstance.h"

void UMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	APawn* Owner =  TryGetPawnOwner();
	if (Owner)
	{
		AttackEvent = Cast<IAttack>(Owner);
	}
}

void UMonsterAnimInstance::StartAttackMontage()
{
	Montage_Play(AttackMontage);

}

void UMonsterAnimInstance::AnimNotify_AttackHitCheck()
{
	if (AttackEvent)
	{
		AttackEvent->OnAttack();
	}

}

void UMonsterAnimInstance::AnimNotify_PlayParticleEffect()
{
}

void UMonsterAnimInstance::AnimNotify_DieEvenet()
{

	if (DieEvenet.IsBound())
	{
		DieEvenet.Execute();
	}
}
