// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "MutantAnimInstance.h"
#include "MagicTrigger\Enemy\MutantCharacter.h"
#include "MagicTrigger\Data\DebugMessage.h"

UMutantAnimInstance::UMutantAnimInstance()
{
	Speed = 0;
	bAttacking = false;
	bGettingDamage = false;
	bDying = false;
	bStunning = false;
	DurationAnimationStunning = 1.3;
}

void UMutantAnimInstance::NativeBeginPlay()
{
	if (!GetAndCheckReferences())
	{
		return;
	}
}

void UMutantAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!GetAndCheckReferences())
	{
		return;
	}

	//if (!Mutant)
	//{
	//	DEBUGMESSAGE("!Mutant");
	//	return;
	//}

	FVector Velocity = Mutant->GetVelocity();
	Speed = FMath::Sqrt(Velocity.X * Velocity.X + Velocity.Y * Velocity.Y + Velocity.Z * Velocity.Z);

	bAttacking = Mutant->bAttacking;
	bGettingDamage = Mutant->bGettingDamage;
	bDying = Mutant->bDying;
	bStunning = Mutant->bStunning;
}

bool UMutantAnimInstance::GetAndCheckReferences()
{
	APawn* PawnOwner = TryGetPawnOwner();
	if (!PawnOwner)
	{
		//DEBUGMESSAGE("!PawnOwner");
		return false;
	}
	Mutant = Cast<AMutantCharacter>(PawnOwner);
	if (!Mutant)
	{
		//DEBUGMESSAGE("!Mutant");
		return false;
	}

	return true;
}

void UMutantAnimInstance::StopTraceAttackRightHand()
{
	Mutant->StopTraceAttack();
}

void UMutantAnimInstance::StopTraceAttackLeftHand()
{
	Mutant->StopTraceAttack();
}

void UMutantAnimInstance::StartTraceAttackRightHand()
{
	Mutant->StartTraceAttack(true);
}

void UMutantAnimInstance::StartTraceAttackLeftHand()
{
	Mutant->StartTraceAttack(false);
}

void UMutantAnimInstance::EndAnimationHitReaction()
{
	Mutant->DoAfterEndAnimationTakeDamage();
}

void UMutantAnimInstance::EndAnimationStunning()
{
	FTimerHandle StunningTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(StunningTimerHandle, this, &UMutantAnimInstance::DoAfterEndAnimationStunning, DurationAnimationStunning);
}

void UMutantAnimInstance::DoAfterEndAnimationStunning()
{
	Mutant->Stunning(false);
}
