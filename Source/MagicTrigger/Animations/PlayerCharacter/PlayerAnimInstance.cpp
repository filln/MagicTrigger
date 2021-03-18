// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "PlayerAnimInstance.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "MagicTrigger\Interfaces\AnimationManagerInterface.h"
#include "GameFramework\Pawn.h"
#include "GameFramework/PawnMovementComponent.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	Speed = 0;
	PlayRateLiftingThrowingObject = 1;
	StartPositionLiftingThrowingObject = 0;
	bMoving = false;
	bInAir = false;
	bAttacking = false;
	bShortWalk = false;
	bWatchingNow = false;
	bLiftingUp2Hands = false;
	bLiftingUp1Hand = false;
	bPutingDown1Hand = false;
	bThrowing = false;
	bGettingDamage = false;
	bDying = false;
	bFightingIdle = false;
	bCarrying = false;
}

void UPlayerAnimInstance::NativeBeginPlay()
{
	if (!GetAndCheckReferences())
	{
		return;
	}

}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	//if (!GetAndCheckReferences())
	//{
	//	return;
	//}

	if (!this->PawnOwner)
	{
		DEBUGMESSAGE("!this->PawnOwner");
		return;
	}
	if (!this->AnimationManagerComponent)
	{
		DEBUGMESSAGE("!this->AnimationManagerComponent");
		return;
	}

	if (!IsInterfaceImplementedBy<IAnimationManagerInterface>(this->AnimationManagerComponent))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IAnimationManagerInterface>(this->AnimationManagerComponent)");
		return;
	}

	FVector Velocity = this->PawnOwner->GetVelocity();
	this->Speed = FMath::Sqrt(Velocity.X * Velocity.X + Velocity.Y * Velocity.Y + Velocity.Z * Velocity.Z);
	if (this->Speed > 0)
	{
		this->bMoving = true;
	}
	else
	{
		this->bMoving = false;
	}
	this->bInAir = PawnOwner->GetMovementComponent()->IsFalling();

	this->bAttacking = IAnimationManagerInterface::Execute_GetAttacking_IF(this->AnimationManagerComponent);
	this->bWatchingNow = IAnimationManagerInterface::Execute_GetWatchingNow_IF(this->AnimationManagerComponent);
	this->bShortWalk = IAnimationManagerInterface::Execute_GetShortWalk_IF(this->AnimationManagerComponent);
	this->bLiftingUp2Hands = IAnimationManagerInterface::Execute_GetLiftingUp2Hands_IF(this->AnimationManagerComponent);
	this->bLiftingUp1Hand = IAnimationManagerInterface::Execute_GetLiftingUp1Hand_IF(this->AnimationManagerComponent);
	this->bPutingDown1Hand = IAnimationManagerInterface::Execute_GetPutingDown1Hand_IF(this->AnimationManagerComponent);
	this->bThrowing = IAnimationManagerInterface::Execute_GetThrowing_IF(this->AnimationManagerComponent);
	this->bCarrying = IAnimationManagerInterface::Execute_GetCarrying_IF(this->AnimationManagerComponent);
	this->PlayRateLiftingThrowingObject = IAnimationManagerInterface::Execute_GetPlayRateLiftingThrowingObject_IF(this->AnimationManagerComponent);
	this->StartPositionLiftingThrowingObject = IAnimationManagerInterface::Execute_GetStartPositionLiftingThrowingObject_IF(this->AnimationManagerComponent);
	this->bGettingDamage = IAnimationManagerInterface::Execute_GetGettingDamage_IF(this->AnimationManagerComponent);
	this->bDying = IAnimationManagerInterface::Execute_GetDying_IF(this->AnimationManagerComponent);
}


bool UPlayerAnimInstance::GetAndCheckReferences()
{
	this->PawnOwner = TryGetPawnOwner();
	if (!this->PawnOwner)
	{
		DEBUGMESSAGE("!this->PawnOwner");
		return false;
	}
	if (!IsInterfaceImplementedBy<IAnimationManagerInterface>(this->PawnOwner))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IAnimationManagerInterface>(this->PawnOwner)");
		return false;
	}

	this->AnimationManagerComponent = IAnimationManagerInterface::Execute_GetAnimationManagerComponent_IF(this->PawnOwner);

	if (!this->AnimationManagerComponent)
	{
		DEBUGMESSAGE("!this->AnimationManagerComponent");
		return false;
	}
	if (!IsInterfaceImplementedBy<IAnimationManagerInterface>(this->AnimationManagerComponent))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IAnimationManagerInterface>(this->AnimationManagerComponent)");
		return false;
	}

	return true;
}

void UPlayerAnimInstance::PutDownThrowingObject()
{
	if (this->bPutingDown1Hand)
	{
		IAnimationManagerInterface::Execute_DetachLiftingActor_IF(this->AnimationManagerComponent);
	}
}

void UPlayerAnimInstance::LiftUpThrowingObject()
{
	if (this->bLiftingUp1Hand)
	{
		IAnimationManagerInterface::Execute_AttachThrowableActor_IF(this->AnimationManagerComponent);
	}
}

void UPlayerAnimInstance::EndAnimationLiftingCarriedObject()
{
	if (this->bLiftingUp2Hands)
	{
		IAnimationManagerInterface::Execute_SetPlayingAnimationLiftUp2Hand_IF(this->AnimationManagerComponent, false);
	}
}

void UPlayerAnimInstance::EndAnimationLiftingThrowingObject()
{
	if (this->bLiftingUp1Hand)
	{
		IAnimationManagerInterface::Execute_SetPlayingAnimationLiftUp1Hand_IF(this->AnimationManagerComponent, false);
	}
}

void UPlayerAnimInstance::StartAnimationLiftingCarriedObject()
{
	if (this->bLiftingUp2Hands)
	{
		IAnimationManagerInterface::Execute_SetCarrying_IF(this->AnimationManagerComponent, true);
	}
}

void UPlayerAnimInstance::EndAnimationPutDownCarriedObject()
{
	if (!this->bLiftingUp2Hands)
	{
		IAnimationManagerInterface::Execute_SetPlayingAnimationPutDown2Hand_IF(this->AnimationManagerComponent, false);
		IAnimationManagerInterface::Execute_SetCarrying_IF(this->AnimationManagerComponent, false);
	}
}

void UPlayerAnimInstance::EndAnimationPutDownThrowingObject()
{
	if (this->bPutingDown1Hand)
	{
		IAnimationManagerInterface::Execute_DetachLiftingActor_IF(this->AnimationManagerComponent);
	}
}

void UPlayerAnimInstance::LiftUpCarriedObject()
{
	IAnimationManagerInterface::Execute_AttachLiftingActor_IF(this->AnimationManagerComponent);
}

void UPlayerAnimInstance::PutDownCarriedObject()
{
	IAnimationManagerInterface::Execute_DetachLiftingActor_IF(this->AnimationManagerComponent);
}

void UPlayerAnimInstance::StartTraceAttackLeftFoot()
{
	IAnimationManagerInterface::Execute_StartTraceAttackLeftFoot_IF(this->AnimationManagerComponent);
}

void UPlayerAnimInstance::StartTraceAttackRightFoot()
{
	IAnimationManagerInterface::Execute_StartTraceAttackRightFoot_IF(this->AnimationManagerComponent);
}

void UPlayerAnimInstance::StopTraceAttackLeftFoot()
{
	IAnimationManagerInterface::Execute_StopTraceAttackLeftFoot_IF(this->AnimationManagerComponent);
}

void UPlayerAnimInstance::StopTraceAttackRightFoot()
{
	IAnimationManagerInterface::Execute_StopTraceAttackRightFoot_IF(this->AnimationManagerComponent);
}

void UPlayerAnimInstance::EndAttack()
{
	IAnimationManagerInterface::Execute_SetPlayingAnimationAttack_IF(this->AnimationManagerComponent, false);
}

void UPlayerAnimInstance::EndAnimationThrow()
{
	IAnimationManagerInterface::Execute_SetPlayingAnimationThrow_IF(this->AnimationManagerComponent, false);
}

void UPlayerAnimInstance::ThrowObject()
{
	IAnimationManagerInterface::Execute_SpawnThrowableActor_IF(this->AnimationManagerComponent);
}

void UPlayerAnimInstance::EndAnimationHitReaction()
{
	IAnimationManagerInterface::Execute_SetGettingDamage_IF(this->AnimationManagerComponent, false);
}

void UPlayerAnimInstance::EndAnimationJump()
{
	IAnimationManagerInterface::Execute_SetPlayingAnimationJump_IF(this->AnimationManagerComponent, false);
}

void UPlayerAnimInstance::ReportNoise()
{
	IAnimationManagerInterface::Execute_ReportNoise_IF(this->AnimationManagerComponent);
}
