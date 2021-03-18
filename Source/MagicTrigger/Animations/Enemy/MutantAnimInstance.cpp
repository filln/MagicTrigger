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

	//if (!this->Mutant)
	//{
	//	DEBUGMESSAGE("!this->Mutant");
	//	return;
	//}

	FVector Velocity = this->Mutant->GetVelocity();
	this->Speed = FMath::Sqrt(Velocity.X * Velocity.X + Velocity.Y * Velocity.Y + Velocity.Z * Velocity.Z);

	this->bAttacking = this->Mutant->bAttacking;
	this->bGettingDamage = this->Mutant->bGettingDamage;
	this->bDying = this->Mutant->bDying;
	this->bStunning = this->Mutant->bStunning;
}

bool UMutantAnimInstance::GetAndCheckReferences()
{
	APawn* PawnOwner = TryGetPawnOwner();
	if (!PawnOwner)
	{
		//DEBUGMESSAGE("!PawnOwner");
		return false;
	}
	this->Mutant = Cast<AMutantCharacter>(PawnOwner);
	if (!this->Mutant)
	{
		//DEBUGMESSAGE("!this->Mutant");
		return false;
	}

	return true;
}

void UMutantAnimInstance::StopTraceAttackRightHand()
{
	this->Mutant->StopTraceAttack();
}

void UMutantAnimInstance::StopTraceAttackLeftHand()
{
	this->Mutant->StopTraceAttack();
}

void UMutantAnimInstance::StartTraceAttackRightHand()
{
	this->Mutant->StartTraceAttack(true);
}

void UMutantAnimInstance::StartTraceAttackLeftHand()
{
	this->Mutant->StartTraceAttack(false);
}

void UMutantAnimInstance::EndAnimationHitReaction()
{
	this->Mutant->DoAfterEndAnimationTakeDamage();
}

void UMutantAnimInstance::EndAnimationStunning()
{
	FTimerHandle StunningTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(StunningTimerHandle, this, &UMutantAnimInstance::DoAfterEndAnimationStunning, this->DurationAnimationStunning);
}

void UMutantAnimInstance::DoAfterEndAnimationStunning()
{
	this->Mutant->Stunning(false);
}
