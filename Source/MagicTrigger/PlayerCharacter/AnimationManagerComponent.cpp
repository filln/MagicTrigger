// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Для взаимодействия между классом перса PlayerCharacterMagicTrigger и его классом анимаций AnimInstance (ABP_PlayerCharacter).
 */


#include "AnimationManagerComponent.h"
#include "GameFramework/Character.h"
#include "MagicTrigger\Data\DebugMessage.h"

 // Sets default values for this component's properties
UAnimationManagerComponent::UAnimationManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	bAttacking = false;
	bLiftingUp1Hand = false;
	bLiftingUp2Hands = false;
	bPutingDown1Hand = false;
	bThrowing = false;
	bDying = false;
	bGettingDamage = false;
	bWatchingNow = false;
	bCarrying = false;
	bJumping = false;
	bShortWalk = false;

	bCanJump = true;
	bCanAttack = true;
	bCanThrow = true;
	bCanInteract = true;
	bCanRun = true;

	CheckStopJumpAnimationTimerRate = 1.9;
	CheckStopMeleeAttackAnimationTimerRate = 1.5;
	CheckStopThrowAnimationTimerRate = 1.1;
}


// Called when the game starts
void UAnimationManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<ACharacter>(GetOwner());
	if (PlayerCharacter)
	{
		USkeletalMeshComponent* Mesh = PlayerCharacter->GetMesh();
		AnimInstance = Mesh->GetAnimInstance();
	}
	else
	{
		DEBUGMESSAGE("!PlayerCharacter")
	}
}

void UAnimationManagerComponent::StartJump()
{
	if (!bCanJump)
	{
		return;
	}
	if (!PlayerCharacter)
	{
		return;
	}
	SetPlayingAnimationJump(true);
	PlayerCharacter->Jump();

	FTimerDelegate TmpDelegate;
	TmpDelegate.BindLambda
	(
		[=]()
	{
		if (bJumping)
		{
			SetPlayingAnimationJump(false);
		}
	}
	);
	GetWorld()->GetTimerManager().SetTimer(CheckStopJumpAnimationTimer, TmpDelegate, CheckStopJumpAnimationTimerRate, false);
}

void UAnimationManagerComponent::StopJump()
{
	if (PlayerCharacter)
	{
		PlayerCharacter->StopJumping();
		SetPlayingAnimationJump(false);
	}
}

void UAnimationManagerComponent::MeleeAttackAnimation()
{
	if (!bCanAttack)
	{
		return;
	}

	SetPlayingAnimationAttack(true);

	FTimerDelegate TmpDelegate;
	TmpDelegate.BindLambda
	(
		[=]()
	{
		if (bAttacking)
		{
			SetPlayingAnimationAttack(false);
		}
	}
	);
	GetWorld()->GetTimerManager().SetTimer(CheckStopMeleeAttackAnimationTimer, TmpDelegate, CheckStopMeleeAttackAnimationTimerRate, false);
}

void UAnimationManagerComponent::ThrowAnimation()
{
	if (!bCanThrow)
	{
		return;
	}

	SetPlayingAnimationThrow(true);

	FTimerDelegate TmpDelegate;
	TmpDelegate.BindLambda
	(
		[=]()
	{
		if (bThrowing)
		{
			SetPlayingAnimationThrow(false);
		}
	}
	);
	GetWorld()->GetTimerManager().SetTimer(CheckStopThrowAnimationTimer, TmpDelegate, CheckStopThrowAnimationTimerRate, false);
}

void UAnimationManagerComponent::SetPlayingAnimationThrow(bool bPlaying)
{
	if (bPlaying)
	{
		bCanThrow = false;
		bCanAttack = false;
		bCanInteract = false;

		bThrowing = true;
	}
	else
	{
		bCanThrow = true;
		bCanAttack = true;
		bCanInteract = true;

		bThrowing = false;
	}
}

void UAnimationManagerComponent::SetPlayingAnimationAttack(bool bPlaying)
{
	if (bPlaying)
	{
		bCanThrow = false;
		bCanAttack = false;
		bCanInteract = false;
		bCanRun = false;
		bCanJump = false;

		bAttacking = true;
	}
	else
	{
		bCanThrow = true;
		bCanAttack = true;
		bCanInteract = true;
		bCanRun = true;
		bCanJump = true;

		bAttacking = false;
	}
}

void UAnimationManagerComponent::SetPlayingAnimationJump(bool bPlaying)
{
	if (bPlaying)
	{
		bCanInteract = false;

		bJumping = true;
	}
	else
	{
		bCanInteract = true;

		bJumping = false;
	}
}

void UAnimationManagerComponent::SetPlayingAnimationLiftUp1Hand(bool bPlaying)
{
	if (bPlaying)
	{
		bCanThrow = false;
		bCanAttack = false;
		bCanInteract = false;
		bCanRun = false;
		bCanJump = false;

		bLiftingUp1Hand = true;

	}
	else
	{
		bCanThrow = true;
		bCanAttack = true;
		bCanInteract = true;
		bCanRun = true;
		bCanJump = true;

		bLiftingUp1Hand = false;
	}
}

void UAnimationManagerComponent::SetPlayingAnimationLiftUp2Hands(bool bPlaying)
{
	if (bPlaying)
	{
		bCanThrow = false;
		bCanAttack = false;
		bCanInteract = false;
		bCanRun = false;
		bCanJump = false;

		bLiftingUp2Hands = true;

	}
	else
	{
		bCanInteract = false;
		bCanRun = true;
	}
}

void UAnimationManagerComponent::SetPlayingAnimationPutDown1Hand(bool bPlaying)
{
	if (bPlaying)
	{
		bCanThrow = false;
		bCanAttack = false;
		bCanInteract = false;
		bCanRun = false;
		bCanJump = false;

		bPutingDown1Hand = true;

	}
	else
	{
		bCanThrow = true;
		bCanAttack = true;
		bCanInteract = true;
		bCanRun = true;
		bCanJump = true;

		bPutingDown1Hand = false;
	}
}

void UAnimationManagerComponent::SetPlayingAnimationPutDown2Hands(bool bPlaying)
{
	if (bPlaying)
	{
		bCanThrow = false;
		bCanAttack = false;
		bCanInteract = false;
		bCanRun = false;
		bCanJump = false;

		bLiftingUp2Hands = false;

	}
	else
	{
		bCanThrow = true;
		bCanAttack = true;
		bCanInteract = true;
		bCanRun = true;
		bCanJump = true;
	}
}

void UAnimationManagerComponent::StopAnimations()
{
	if (AnimInstance->Montage_IsPlaying(FightIdleMontage))
	{
		AnimInstance->Montage_Stop(0, FightIdleMontage);
	}
}


/**
* AnimationManagerInterface methods.
*/
/**
 * Setters
 */

//void UAnimationManagerComponent::SetGettingDamage_IF_Implementation(bool bInGettingDamage)
//{
//	bGettingDamage = bInGettingDamage;
//}


