// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

/**
 * Анимации Демона.
 */

#include "DemonAnimInstance.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "MagicTrigger\Enemy\DemonCharacter.h"

UDemonAnimInstance::UDemonAnimInstance()
{
	Speed = 0;
	bAttacking = false;
	bDying = false;
}

void UDemonAnimInstance::NativeBeginPlay()
{
	if (!GetAndCheckReferences())
	{
		return;
	}
}

void UDemonAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!GetAndCheckReferences())
	{
		return;
	}

	FVector Velocity = this->Demon->GetVelocity();
	this->Speed = FMath::Sqrt(Velocity.X * Velocity.X + Velocity.Y * Velocity.Y + Velocity.Z * Velocity.Z);

	this->bAttacking = this->Demon->bAttacking;
	this->bDying = this->Demon->bDying;

}

bool UDemonAnimInstance::GetAndCheckReferences()
{
	APawn* PawnOwner = TryGetPawnOwner();
	if (!PawnOwner)
	{
		//DEBUGMESSAGE("!PawnOwner");
		return false;
	}
	this->Demon = Cast<ADemonCharacter>(PawnOwner);
	if (!this->Demon)
	{
		//DEBUGMESSAGE("!this->Demon");
		return false;
	}

	return true;
}

void UDemonAnimInstance::CreateFireBall()
{
	this->Demon->CreateFireBall();
}

void UDemonAnimInstance::MoveFireBallToTarget()
{
	this->Demon->MoveFireBallToTarget();
}
