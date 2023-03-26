// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "PlayerAnimInstance.h"
#include "MagicTrigger/Data/DebugMessage.h"
#include "MagicTrigger/PlayerCharacter/PlayerCharacterMagicTrigger.h"
#include "MagicTrigger/PlayerCharacter/AnimationManagerComponent.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	Speed = 0;
	bMoving = false;
	bInAir = false;
	bAttacking = false;
	bSpawningSSphere = false;
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

	FVector Velocity = PlayerCharacter->GetVelocity();
	Speed = FMath::Sqrt(Velocity.X * Velocity.X + Velocity.Y * Velocity.Y + Velocity.Z * Velocity.Z);
	if (Speed > 0)
	{
		bMoving = true;
	}
	else
	{
		bMoving = false;
	}
	bInAir = PlayerCharacter->IsFalling();

	bAttacking = AnimationManagerComponent->bAttacking;
	bSpawningSSphere = AnimationManagerComponent->bSpawningSSphere;
	bRoundWaving = AnimationManagerComponent->bRoundWaving;
	bWatchingNow = AnimationManagerComponent->bWatchingNow;
	bShortWalk = AnimationManagerComponent->bShortWalk;
	bLiftingUp2Hands = AnimationManagerComponent->bLiftingUp2Hands;
	bLiftingUp1Hand = AnimationManagerComponent->bLiftingUp1Hand;
	bPutingDown1Hand = AnimationManagerComponent->bPutingDown1Hand;
	bThrowing = AnimationManagerComponent->bThrowing;
	bCarrying = AnimationManagerComponent->bCarrying;
	bGettingDamage = AnimationManagerComponent->bGettingDamage;
	bDying = AnimationManagerComponent->bDying;
}


bool UPlayerAnimInstance::GetAndCheckReferences()
{
	APawn* PawnOwner = TryGetPawnOwner();
	if (!PawnOwner)
	{
		DEBUGMESSAGE("!PawnOwner");
		return false;
	}
	PlayerCharacter = Cast<APlayerCharacterMagicTrigger>(PawnOwner);
	if (!PlayerCharacter)
	{
		DEBUGMESSAGE("!PlayerCharacter");
		return false;
	}
	AnimationManagerComponent = PlayerCharacter->AnimationManagerComponent;

	if (!AnimationManagerComponent)
	{
		DEBUGMESSAGE("!AnimationManagerComponent");
		return false;
	}

	return true;
}

void UPlayerAnimInstance::PutDownPickUpItem()
{
	if (bPutingDown1Hand)
	{
		PlayerCharacter->DetachLiftUpItem();
	}
}

void UPlayerAnimInstance::LiftUpPickUpItem()
{
	if (bLiftingUp1Hand)
	{
		PlayerCharacter->AttachLiftUpItem();
	}
}

void UPlayerAnimInstance::EndAnimationLiftingCarryItem()
{
	if (bLiftingUp2Hands)
	{
		AnimationManagerComponent->SetPlayingAnimationLiftUp2Hands(false);
	}
}

void UPlayerAnimInstance::EndAnimationLiftingPickUpItem()
{
	if (bLiftingUp1Hand)
	{
		PlayerCharacter->PickUpPickUpItem();
		AnimationManagerComponent->SetPlayingAnimationLiftUp1Hand(false);
	}
}

void UPlayerAnimInstance::StartAnimationLiftingCarryItem()
{
	if (bLiftingUp2Hands)
	{
		AnimationManagerComponent->bCarrying = true;
	}
}

void UPlayerAnimInstance::EndAnimationPutDownCarryItem()
{
	if (!bLiftingUp2Hands)
	{
		AnimationManagerComponent->SetPlayingAnimationPutDown2Hands(false);
		AnimationManagerComponent->bCarrying = false;
	}
}

void UPlayerAnimInstance::EndAnimationPutDownPickUpItem()
{
	if (bPutingDown1Hand)
	{
		AnimationManagerComponent->SetPlayingAnimationPutDown1Hand(false);
	}
}

void UPlayerAnimInstance::LiftUpCarryItem()
{
	PlayerCharacter->AttachLiftUpItem();
}

void UPlayerAnimInstance::PutDownCarryItem()
{
	PlayerCharacter->DetachLiftUpItem();
}

void UPlayerAnimInstance::StartTraceAttackLeftFoot()
{
	PlayerCharacter->StartTraceAttackLeftFoot();
}

void UPlayerAnimInstance::StartTraceAttackRightFoot()
{
	PlayerCharacter->StartTraceAttackRightFoot();
}

void UPlayerAnimInstance::StopTraceAttackLeftFoot()
{
	PlayerCharacter->StopTraceAttackLeftFoot();
}

void UPlayerAnimInstance::StopTraceAttackRightFoot()
{
	PlayerCharacter->StopTraceAttackRightFoot();
}

void UPlayerAnimInstance::EndAttack()
{
	AnimationManagerComponent->SetPlayingAnimationAttack(false);
	Montage_Play(PlayerFightIdle);	
}

void UPlayerAnimInstance::CastRoundWave()
{
	//DEBUGMESSAGE("Cast Round Wave");
	PlayerCharacter->CastRoundWave();
}

void UPlayerAnimInstance::EndAnimationRoundWave()
{
	//DEBUGMESSAGE("End of RoundWaveAnimation");
	AnimationManagerComponent->SetPlayingAnimationRoundWave(false);
}

void UPlayerAnimInstance::StartAnimationThrow()
{
	PlayerCharacter->SpawnThrowableItem();
}

void UPlayerAnimInstance::ThrowThrowableItem()
{
	PlayerCharacter->ThrowThrowableItem();
}

void UPlayerAnimInstance::EndAnimationThrow()
{
	AnimationManagerComponent->SetPlayingAnimationThrow(false);
}

void UPlayerAnimInstance::EndAnimationHitReaction()
{
	AnimationManagerComponent->bGettingDamage = false;
}

void UPlayerAnimInstance::EndAnimationJump()
{
	AnimationManagerComponent->SetPlayingAnimationJump(false);
}

void UPlayerAnimInstance::ReportNoise()
{
	PlayerCharacter->ReportNoise();
}

void UPlayerAnimInstance::SpawnSSphere()
{
	PlayerCharacter->SpawnSSphere();
}

void UPlayerAnimInstance::EndAnimationSpawnSSphere()
{
	AnimationManagerComponent->SetPlayingAnimationSpawnSSphere(false);
}
