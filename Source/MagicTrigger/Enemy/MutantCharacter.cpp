// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Враг перса Мутант.
 */

#pragma once

#include "MutantCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Kismet/GameplayStatics.h"

#include "MagicTrigger/Data/CollisionChannelsMagicTrigger.h"
#include "MagicTrigger/Data/DebugMessage.h"
#include "MagicTrigger/AbilitySystem/MeleeAttack/MeleeAttackComponent.h"

class UAnimInstance;
class UAnimationAsset;

AMutantCharacter::AMutantCharacter()
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_ThrowableObject, ECollisionResponse::ECR_Overlap);

	FHitResult HitResultTmp = FHitResult();

	GetMesh()->SetRelativeLocation(FVector(-13, 0, -88), false, &HitResultTmp, ETeleportType::None);
	GetMesh()->SetRelativeScale3D(FVector(0.95));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshObj(TEXT("/Game/MagicTrigger/Meshes/Enemy/SK_Mutant"));
	if (MeshObj.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshObj.Object);
	}
	else
	{
		DEBUGMESSAGE("!MeshObj.Succeeded()")
	}
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimationClass(TEXT("/Game/MagicTrigger/Animations/Enemy/Mutant/ABP_Mutant"));
	if (AnimationClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimationClass.Class);
	}
	else
	{
		DEBUGMESSAGE("!AnimationClass.Succeeded()")
	}
	MeleeAttackComponent = CreateDefaultSubobject<UMeleeAttackComponent>(TEXT("MeleeAttackComponent"));

	ArrowRightHandSocketName = FName(TEXT("RightHand"));
	ArrowLeftHandSocketName = FName(TEXT("LeftHandSocket1"));

	ArrowRightHand = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowRightHand"));
	ArrowLeftHand = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowLeftHand"));

	ArrowRightHand->SetupAttachment(GetMesh(), ArrowRightHandSocketName);
	ArrowRightHand->SetRelativeRotation(FRotator(34, 137, 109), false, &HitResultTmp, ETeleportType::None);

	ArrowLeftHand->SetupAttachment(GetMesh(), ArrowLeftHandSocketName);
	ArrowLeftHand->SetRelativeRotation(FRotator(41, 104, 162), false, &HitResultTmp, ETeleportType::None);

	Name = FText::FromStringTable("/Game/MagicTrigger/Data/ST_EnemyName.ST_EnemyName", "Mutant");
	if (Name.IsEmpty())
	{
		DEBUGMESSAGE("Name.IsEmpty()");

	}

	static ConstructorHelpers::FObjectFinder<UTexture2D> IconObj(TEXT("/Game/MagicTrigger/Textures/Enemy/Mutant/T_Mutant_Icon_D"));
	if (IconObj.Succeeded())
	{
		Icon = IconObj.Object;
	}
	else
	{
		DEBUGMESSAGE("!IconObj.Succeeded()")
	}
	MaxLife = 100;
	MaxDefence = 1;
	MaxDamage = 200;
	Life = MaxLife;
	Defence = MaxDefence;
	Damage = MaxDamage;

	EnemyToBehaviorTreeStruct.WaitTimeOfAnimationRoaring = 2.52;
	EnemyToBehaviorTreeStruct.FindPlayerRadius = 2000;
	EnemyToBehaviorTreeStruct.SightRadius = 2500;
	EnemyToBehaviorTreeStruct.LoseSightRadius = 2000;
	EnemyToBehaviorTreeStruct.HearingRange = 700;
	EnemyToBehaviorTreeStruct.MoveAndAttackRadius = 600;
	EnemyToBehaviorTreeStruct.AttackRadius = 90;
	EnemyToBehaviorTreeStruct.PatrolingRadius = 700;
	EnemyToBehaviorTreeStruct.PatrolingWaitMaxTime = 10;
	static ConstructorHelpers::FObjectFinder<UAnimationAsset> AnimationRoaringObj(TEXT("/Game/MagicTrigger/Animations/Enemy/Mutant/AS_Mutant_Roaring"));
	if (AnimationRoaringObj.Succeeded())
	{
		EnemyToBehaviorTreeStruct.AnimationRoaring = AnimationRoaringObj.Object;
	}
	else
	{
		DEBUGMESSAGE("!AnimationRoaringObj.Succeeded()")
	}

	MeleeAttackComponent->AttackLengthTrace = 170;

}

void AMutantCharacter::BeginPlay()
{
	Super::BeginPlay();

	EnemyToBehaviorTreeStruct.SpawnLocation = GetActorLocation();
	Name = FText::FromStringTable("/Game/MagicTrigger/Data/ST_EnemyName.ST_EnemyName", "Mutant");
	if (Name.IsEmpty())
	{
		DEBUGMESSAGE("Name.IsEmpty()");

	}
}

void AMutantCharacter::StartTraceAttack(bool bRightHand)
{
	if (!GetWorld())
	{
		DEBUGMESSAGE("!GetWorld()");
		return;
	}

	FTimerDelegate TraceAttackDelegate = FTimerDelegate::CreateUObject(this, &AMutantCharacter::TraceAttack, bRightHand);
	GetWorld()->GetTimerManager().SetTimer(MeleeAttackComponent->AttackTimer, TraceAttackDelegate, MeleeAttackComponent->AttackTimerDeltaTime, true);
}

void AMutantCharacter::StopTraceAttack()
{
	MeleeAttackComponent->StopAttackTimer();
}

void AMutantCharacter::TraceAttack(bool bRightHand)
{
	FVector StartTrace;
	FVector EndTraceUnit;
	if (bRightHand)
	{
		StartTrace = GetMesh()->GetSocketLocation(ArrowRightHandSocketName);
		EndTraceUnit = ArrowRightHand->GetForwardVector();
	} 
	else
	{
		StartTrace = GetMesh()->GetSocketLocation(ArrowLeftHandSocketName);
		EndTraceUnit = ArrowLeftHand->GetForwardVector();
	}

	FHitResult TraceAttackHitResult;
	bool bTraceResult = MeleeAttackComponent->TraceAttack(TraceAttackHitResult, StartTrace, EndTraceUnit);
	if (!bTraceResult)
	{
		//DEBUGMESSAGE("!bTraceResult");
		return;
	}
	AEnemyCharacterMagicTrigger* HitEnemy = Cast<AEnemyCharacterMagicTrigger>(TraceAttackHitResult.GetActor());
	if (HitEnemy)
	{
		//DEBUGMESSAGE("HitEnemy");
		return;
	}

	MeleeAttackComponent->StopAttackTimer();
	UGameplayStatics::ApplyDamage(TraceAttackHitResult.GetActor(), Damage, GetController(), this, MeleeAttackComponent->DamageTypeClass);
}

void AMutantCharacter::Stunning_IF_Implementation()
{
	bStunningAfterGetDamage = true;
}
