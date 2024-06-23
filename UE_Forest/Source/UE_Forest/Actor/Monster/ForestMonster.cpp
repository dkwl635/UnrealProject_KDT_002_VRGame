// Fill out your copyright notice in the Description page of Project Settings.
#include "Actor/Monster/ForestMonster.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "ForestAiController.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AnimInstance/MonsterAnimInstance.h"
#include "GameMode/ForestGameMode.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/AudioComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
AForestMonster::AForestMonster()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	BodyBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BodyBoxComponent"));
	AttackBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackBox"));
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
	StepAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("StepAudioComponent"));

	SetRootComponent(BodyBoxComponent);
	SkeletalMeshComponent->SetupAttachment(GetRootComponent());
	AttackBox->SetupAttachment(GetRootComponent());
	FloatingPawnMovement->UpdatedComponent = GetRootComponent();
	StepAudioComponent->SetupAttachment(GetRootComponent());

	AIControllerClass = AForestAiController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	FloatingPawnMovement->MaxSpeed = InitSpeed;

	AttackBox->OnComponentBeginOverlap.AddDynamic(this, &AForestMonster::OnBeginHitBox);
	AttackBox->OnComponentEndOverlap.AddDynamic(this, &AForestMonster::OnEndHitBox);

	

}

// Called when the game starts or when spawned
void AForestMonster::BeginPlay()
{
	
	Super::BeginPlay();
	Speed = InitSpeed;

	GameMode = Cast<AForestGameMode>(GetWorld()->GetAuthGameMode());
	
	IsInHitBoxCharacter = false;

	MonsterAnimInstance = Cast<UMonsterAnimInstance>(SkeletalMeshComponent->GetAnimInstance());
	if (MonsterAnimInstance)
	{
		MonsterAnimInstance->DieEvenet.BindUObject(this, &AForestMonster::MonsterDisable);
	}

	BodyOrginECollision = BodyBoxComponent->GetCollisionEnabled();
	AttackBoxOrginECollision = BodyBoxComponent->GetCollisionEnabled();


}

void AForestMonster::PossessedBy(AController* NewController)
{
	//OnPossess()->PossessedBy();

	Super::PossessedBy(NewController);

	OnwerController = Cast<AForestAiController>(NewController);	
}
// Called every frame
void AForestMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Speed += (DeltaTime * 3);
	if (Speed > MaxSpeed)
	{
		Speed = MaxSpeed;
	}

	FloatingPawnMovement->MaxSpeed = Speed;

}

void AForestMonster::OnBeginLight()
{
	BlackboardComponent->SetValueAsBool(IsMoveKey, false);

	Speed = InitSpeed;
}

void AForestMonster::OnEndLight()
{
	BlackboardComponent->SetValueAsBool(IsMoveKey, true);

	Speed = InitSpeed;
}

void AForestMonster::OnBeginHitBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IsInHitBoxCharacter = true;
	BlackboardComponent->SetValueAsBool(IsAttackKey, IsInHitBoxCharacter);
}

void AForestMonster::OnEndHitBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	IsInHitBoxCharacter = false;
	BlackboardComponent->SetValueAsBool(IsAttackKey, IsInHitBoxCharacter);
}



float AForestMonster::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	TakeDamageEvent();
	Die();
	return 0.0f;
}


void AForestMonster::StartAttack()
{

	if (MonsterAnimInstance)
	{
		MonsterAnimInstance->StartAttackMontage();
	}
	
}

void AForestMonster::OnAttack()
{
	
	if (IsInHitBoxCharacter)
	{
		UE_LOG(LogTemp, Display, TEXT("OnAttack"));
		AttackDamage();	
		TakeSuccessDamage();
	}
}

void AForestMonster::AttackDamage()
{
	GameMode->TakeDamageCharacter();
}

bool AForestMonster::IsAttackable()
{
	return IsInHitBoxCharacter;
}

void AForestMonster::Die()
{
	isDie = true;
	OnwerController->StopMovement();
	BodyBoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void AForestMonster::MonsterDisable()
{
	SkeletalMeshComponent->SetVisibility(false, true);
	BodyBoxComponent->SetVisibility(false);
	AttackBox->SetVisibility(false);
}

void AForestMonster::MonsterSpawn()
{
	SkeletalMeshComponent->SetVisibility(true, true);

	BodyBoxComponent->SetVisibility(true);
	AttackBox->SetVisibility(true);

	BodyBoxComponent->SetCollisionEnabled(BodyOrginECollision);
	AttackBox->SetCollisionEnabled(AttackBoxOrginECollision);

	MonsterSpawnEvent();

	int32 RandomValueX = FMath::RandRange(-12500, 12500);
	int32 RandomValueY = FMath::RandRange(-12500, 12500);

	FVector NewPos = FVector(RandomValueX, RandomValueY, GetActorLocation().Z);
	SetActorLocation(NewPos, false, nullptr, ETeleportType::TeleportPhysics);

}

void AForestMonster::ForestGameStart()
{
	//AI Start
	OnwerController->RunBehaviorTree(OnwerController->BT);
	//BrainComponent
	BlackboardComponent = OnwerController->FindComponentByClass<UBlackboardComponent>();
	BlackboardComponent->SetValueAsBool(IsMoveKey, true);
	BlackboardComponent->SetValueAsBool(IsAttackKey, false);

	GameMode = Cast<AForestGameMode>(GetWorld()->GetAuthGameMode());
	AActor* Target = GameMode->ForestCharacter;
	BlackboardComponent->SetValueAsObject(TargetKey, Target);

}

void AForestMonster::ForestGameEnd()
{


}

bool AForestMonster::IsDie()
{
	return isDie;
}

void AForestMonster::Spawn()
{
	isDie = false;

	MonsterSpawn();
	
}


