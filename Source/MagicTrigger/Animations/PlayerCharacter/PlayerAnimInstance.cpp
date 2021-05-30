// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "PlayerAnimInstance.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "MagicTrigger\Interfaces\AnimationManagerInterface.h"
#include "GameFramework\Pawn.h"
#include "GameFramework/PawnMovementComponent.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	Speed = 0;
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

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontageObj(TEXT("/Game/MagicTrigger/Animations/PlayerCharacter/Attack/AM_Player_FightIdle"));
	if (AnimMontageObj.Succeeded())
	{
		PlayerFightIdle = AnimMontageObj.Object;
	}
	else
	{
		DEBUGMESSAGE("!AnimMontageObj.Succeeded()")
	}
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
	if (!GetAndCheckReferences())
	{
		return;
	}

	if (!PawnOwner)
	{
		DEBUGMESSAGE("!PawnOwner");
		return;
	}
	if (!AnimationManagerComponent)
	{
		DEBUGMESSAGE("!AnimationManagerComponent");
		return;
	}

	if (!IsInterfaceImplementedBy<IAnimationManagerInterface>(AnimationManagerComponent))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IAnimationManagerInterface>(AnimationManagerComponent)");
		return;
	}

	FVector Velocity = PawnOwner->GetVelocity();
	Speed = FMath::Sqrt(Velocity.X * Velocity.X + Velocity.Y * Velocity.Y + Velocity.Z * Velocity.Z);
	if (Speed > 0)
	{
		bMoving = true;
	}
	else
	{
		bMoving = false;
	}
	bInAir = PawnOwner->GetMovementComponent()->IsFalling();

	bAttacking = IAnimationManagerInterface::Execute_GetAttacking_IF(AnimationManagerComponent);
	bWatchingNow = IAnimationManagerInterface::Execute_GetWatchingNow_IF(AnimationManagerComponent);
	bShortWalk = IAnimationManagerInterface::Execute_GetShortWalk_IF(AnimationManagerComponent);
	bLiftingUp2Hands = IAnimationManagerInterface::Execute_GetLiftingUp2Hands_IF(AnimationManagerComponent);
	bLiftingUp1Hand = IAnimationManagerInterface::Execute_GetLiftingUp1Hand_IF(AnimationManagerComponent);
	bPutingDown1Hand = IAnimationManagerInterface::Execute_GetPutingDown1Hand_IF(AnimationManagerComponent);
	bThrowing = IAnimationManagerInterface::Execute_GetThrowing_IF(AnimationManagerComponent);
	bCarrying = IAnimationManagerInterface::Execute_GetCarrying_IF(AnimationManagerComponent);
	bGettingDamage = IAnimationManagerInterface::Execute_GetGettingDamage_IF(AnimationManagerComponent);
	bDying = IAnimationManagerInterface::Execute_GetDying_IF(AnimationManagerComponent);
}


bool UPlayerAnimInstance::GetAndCheckReferences()
{
	PawnOwner = TryGetPawnOwner();
	if (!PawnOwner)
	{
		DEBUGMESSAGE("!PawnOwner");
		return false;
	}
	if (!IsInterfaceImplementedBy<IAnimationManagerInterface>(PawnOwner))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IAnimationManagerInterface>(PawnOwner)");
		return false;
	}

	AnimationManagerComponent = IAnimationManagerInterface::Execute_GetAnimationManagerComponent_IF(PawnOwner);

	if (!AnimationManagerComponent)
	{
		DEBUGMESSAGE("!AnimationManagerComponent");
		return false;
	}
	if (!IsInterfaceImplementedBy<IAnimationManagerInterface>(AnimationManagerComponent))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IAnimationManagerInterface>(AnimationManagerComponent)");
		return false;
	}

	return true;
}

void UPlayerAnimInstance::PutDownThrowingObject()
{
	if (bPutingDown1Hand)
	{
		IAnimationManagerInterface::Execute_DetachLiftingActor_IF(AnimationManagerComponent);
	}
}

void UPlayerAnimInstance::LiftUpThrowingObject()
{
	if (bLiftingUp1Hand)
	{
		IAnimationManagerInterface::Execute_AttachThrowableActor_IF(AnimationManagerComponent);
	}
}

void UPlayerAnimInstance::EndAnimationLiftingCarriedObject()
{
	if (bLiftingUp2Hands)
	{
		IAnimationManagerInterface::Execute_SetPlayingAnimationLiftUp2Hand_IF(AnimationManagerComponent, false);
	}
}

void UPlayerAnimInstance::EndAnimationLiftingThrowingObject()
{
	if (bLiftingUp1Hand)
	{
		IAnimationManagerInterface::Execute_SetPlayingAnimationLiftUp1Hand_IF(AnimationManagerComponent, false);
	}
}

void UPlayerAnimInstance::StartAnimationLiftingCarriedObject()
{
	if (bLiftingUp2Hands)
	{
		IAnimationManagerInterface::Execute_SetCarrying_IF(AnimationManagerComponent, true);
	}
}

void UPlayerAnimInstance::EndAnimationPutDownCarriedObject()
{
	if (!bLiftingUp2Hands)
	{
		IAnimationManagerInterface::Execute_SetPlayingAnimationPutDown2Hand_IF(AnimationManagerComponent, false);
		IAnimationManagerInterface::Execute_SetCarrying_IF(AnimationManagerComponent, false);
	}
}

void UPlayerAnimInstance::EndAnimationPutDownThrowingObject()
{
	if (bPutingDown1Hand)
	{
		IAnimationManagerInterface::Execute_SetPlayingAnimationPutDown1Hand_IF(AnimationManagerComponent, false);
	}
}

void UPlayerAnimInstance::LiftUpCarriedObject()
{
	IAnimationManagerInterface::Execute_AttachLiftingActor_IF(AnimationManagerComponent);
}

void UPlayerAnimInstance::PutDownCarriedObject()
{
	IAnimationManagerInterface::Execute_DetachLiftingActor_IF(AnimationManagerComponent);
}

void UPlayerAnimInstance::StartTraceAttackLeftFoot()
{
	IAnimationManagerInterface::Execute_StartTraceAttackLeftFoot_IF(AnimationManagerComponent);
}

void UPlayerAnimInstance::StartTraceAttackRightFoot()
{
	IAnimationManagerInterface::Execute_StartTraceAttackRightFoot_IF(AnimationManagerComponent);
}

void UPlayerAnimInstance::StopTraceAttackLeftFoot()
{
	IAnimationManagerInterface::Execute_StopTraceAttackLeftFoot_IF(AnimationManagerComponent);
}

void UPlayerAnimInstance::StopTraceAttackRightFoot()
{
	IAnimationManagerInterface::Execute_StopTraceAttackRightFoot_IF(AnimationManagerComponent);
}

void UPlayerAnimInstance::EndAttack()
{
	IAnimationManagerInterface::Execute_SetPlayingAnimationAttack_IF(AnimationManagerComponent, false);
	Montage_Play(PlayerFightIdle);	
}

void UPlayerAnimInstance::EndAnimationThrow()
{
	IAnimationManagerInterface::Execute_SetPlayingAnimationThrow_IF(AnimationManagerComponent, false);
}

void UPlayerAnimInstance::ThrowObject()
{
	IAnimationManagerInterface::Execute_SpawnThrowableActor_IF(AnimationManagerComponent);
}

void UPlayerAnimInstance::EndAnimationHitReaction()
{
	IAnimationManagerInterface::Execute_SetGettingDamage_IF(AnimationManagerComponent, false);
}

void UPlayerAnimInstance::EndAnimationJump()
{
	IAnimationManagerInterface::Execute_SetPlayingAnimationJump_IF(AnimationManagerComponent, false);
}

void UPlayerAnimInstance::ReportNoise()
{
	IAnimationManagerInterface::Execute_ReportNoise_IF(AnimationManagerComponent);
}
