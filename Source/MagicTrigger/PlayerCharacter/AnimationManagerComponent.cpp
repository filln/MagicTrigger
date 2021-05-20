// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Для взаимодействия между классом перса PlayerCharacterMagicTrigger и его классом анимаций AnimInstance (ABP_PlayerCharacter).
 */


#include "AnimationManagerComponent.h"
//#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
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
	CheckStopAttackAnimationTimerRate = 1.5;
	CheckStopThrowAnimationTimerRate = 1.1;
}


// Called when the game starts
void UAnimationManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	this->PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (this->PlayerCharacter)
	{
		USkeletalMeshComponent* Mesh = PlayerCharacter->GetMesh();
		this->AnimInstance = Mesh->GetAnimInstance();
	}
	else
	{
		DEBUGMESSAGE("!this->PlayerCharacter")
	}

	this->Owner = GetOwner();
	if (!this->Owner)
	{
		DEBUGMESSAGE("!this->Owner")
	}

}

void UAnimationManagerComponent::StartJump()
{
	if (!this->bCanJump)
	{
		return;
	}

	if (this->PlayerCharacter)
	{
		SetPlayingAnimationJump(true);
		this->PlayerCharacter->Jump();
		GetWorld()->GetTimerManager().SetTimer(CheckStopJumpAnimationTimer, this, &UAnimationManagerComponent::CheckStopJumpAnimation, CheckStopJumpAnimationTimerRate);

	}


}

void UAnimationManagerComponent::CheckStopJumpAnimation()
{
	if (this->bJumping)
	{
		SetPlayingAnimationJump(false);
	}
}

void UAnimationManagerComponent::CheckStopAttackAnimation()
{
	if (this->bAttacking)
	{
		SetPlayingAnimationAttack(false);
	}
}

void UAnimationManagerComponent::CheckStopThrowAnimation()
{
	if (this->bThrowing)
	{
		SetPlayingAnimationThrow(false);
	}
}

void UAnimationManagerComponent::StopJump()
{
	if (this->PlayerCharacter)
	{
		this->PlayerCharacter->StopJumping();
		SetPlayingAnimationJump(false);
	}
}

void UAnimationManagerComponent::AttackAnimation()
{
	if (!this->bCanAttack)
	{
		return;
	}

	SetPlayingAnimationAttack(true);

	GetWorld()->GetTimerManager().SetTimer(CheckStopAttackAnimationTimer, this, &UAnimationManagerComponent::CheckStopAttackAnimation, CheckStopAttackAnimationTimerRate);
}

void UAnimationManagerComponent::ThrowAnimation()
{
	if (!this->bCanThrow)
	{
		return;
	}

	SetPlayingAnimationThrow(true);

	GetWorld()->GetTimerManager().SetTimer(CheckStopThrowAnimationTimer, this, &UAnimationManagerComponent::CheckStopThrowAnimation, CheckStopThrowAnimationTimerRate);
}

void UAnimationManagerComponent::SetPlayingAnimationThrow(bool bPlaying)
{
	if (bPlaying)
	{
		this->bCanThrow = false;
		this->bCanAttack = false;
		this->bCanInteract = false;

		this->bThrowing = true;
	}
	else
	{
		this->bCanThrow = true;
		this->bCanAttack = true;
		this->bCanInteract = true;

		this->bThrowing = false;
	}
}

void UAnimationManagerComponent::SetPlayingAnimationAttack(bool bPlaying)
{
	if (bPlaying)
	{
		this->bCanThrow = false;
		this->bCanAttack = false;
		this->bCanInteract = false;
		this->bCanRun = false;
		this->bCanJump = false;

		this->bAttacking = true;
	}
	else
	{
		this->bCanThrow = true;
		this->bCanAttack = true;
		this->bCanInteract = true;
		this->bCanRun = true;
		this->bCanJump = true;

		this->bAttacking = false;
	}
}

void UAnimationManagerComponent::SetPlayingAnimationJump(bool bPlaying)
{
	if (bPlaying)
	{
		this->bCanInteract = false;

		this->bJumping = true;
	}
	else
	{
		this->bCanInteract = true;

		this->bJumping = false;
	}
}

void UAnimationManagerComponent::SetPlayingAnimationLiftUp1Hand(bool bPlaying)
{
	if (bPlaying)
	{
		this->bCanThrow = false;
		this->bCanAttack = false;
		this->bCanInteract = false;
		this->bCanRun = false;
		this->bCanJump = false;

		this->bLiftingUp1Hand = true;

	}
	else
	{
		this->bCanThrow = true;
		this->bCanAttack = true;
		this->bCanInteract = true;
		this->bCanRun = true;
		this->bCanJump = true;

		this->bLiftingUp1Hand = false;
	}
}

void UAnimationManagerComponent::SetPlayingAnimationLiftUp2Hands(bool bPlaying)
{
	if (bPlaying)
	{
		this->bCanThrow = false;
		this->bCanAttack = false;
		this->bCanInteract = false;
		this->bCanRun = false;
		this->bCanJump = false;

		this->bLiftingUp2Hands = true;

	}
	else
	{
		this->bCanInteract = false;
		this->bCanRun = true;
	}
}

void UAnimationManagerComponent::SetPlayingAnimationPutDown1Hand(bool bPlaying)
{
	if (bPlaying)
	{
		this->bCanThrow = false;
		this->bCanAttack = false;
		this->bCanInteract = false;
		this->bCanRun = false;
		this->bCanJump = false;

		this->bPutingDown1Hand = true;

	}
	else
	{
		this->bCanThrow = true;
		this->bCanAttack = true;
		this->bCanInteract = true;
		this->bCanRun = true;
		this->bCanJump = true;

		this->bPutingDown1Hand = false;
	}
}

void UAnimationManagerComponent::SetPlayingAnimationPutDown2Hands(bool bPlaying)
{
	if (bPlaying)
	{
		this->bCanThrow = false;
		this->bCanAttack = false;
		this->bCanInteract = false;
		this->bCanRun = false;
		this->bCanJump = false;

		this->bLiftingUp2Hands = false;

	}
	else
	{
		this->bCanThrow = true;
		this->bCanAttack = true;
		this->bCanInteract = true;
		this->bCanRun = true;
		this->bCanJump = true;
	}
}

void UAnimationManagerComponent::StopAnimations()
{
	if (this->AnimInstance->Montage_IsPlaying(FightIdleMontage))
	{
		this->AnimInstance->Montage_Stop(0, FightIdleMontage);
	}
}


/**
* AnimationManagerInterface methods.
*/
/**
 * Setters
 */
void UAnimationManagerComponent::SetPlayingAnimationAttack_IF_Implementation(bool bPlaying)
{
	SetPlayingAnimationAttack(bPlaying);
}

void UAnimationManagerComponent::SetPlayingAnimationThrow_IF_Implementation(bool bPlaying)
{
	SetPlayingAnimationThrow(bPlaying);
}

void UAnimationManagerComponent::SetPlayingAnimationJump_IF_Implementation(bool bPlaying)
{
	SetPlayingAnimationJump(bPlaying);
}

void UAnimationManagerComponent::SetPlayingAnimationLiftUp1Hand_IF_Implementation(bool bPlaying)
{
	SetPlayingAnimationLiftUp1Hand(bPlaying);
}

void UAnimationManagerComponent::SetPlayingAnimationPutDown1Hand_IF_Implementation(bool bPlaying)
{
	SetPlayingAnimationPutDown1Hand(bPlaying);
}

void UAnimationManagerComponent::SetPlayingAnimationLiftUp2Hand_IF_Implementation(bool bPlaying)
{
	SetPlayingAnimationLiftUp2Hands(bPlaying);
}

void UAnimationManagerComponent::SetPlayingAnimationPutDown2Hand_IF_Implementation(bool bPlaying)
{
	SetPlayingAnimationPutDown2Hands(bPlaying);
}

void UAnimationManagerComponent::SetGettingDamage_IF_Implementation(bool bInGettingDamage)
{
	this->bGettingDamage = bInGettingDamage;
}

void UAnimationManagerComponent::SetCarrying_IF_Implementation(bool bInCarrying)
{
	this->bCarrying = bInCarrying;
}

void UAnimationManagerComponent::SetCanInteract_IF_Implementation(bool bInCanInteract)
{
	this->bCanInteract = bInCanInteract;
}

/**
* AnimationManagerInterface methods.
*/
/**
 * Getters
 */

bool UAnimationManagerComponent::GetAttacking_IF_Implementation() const
{
	return this->bAttacking;
}

bool UAnimationManagerComponent::GetWatchingNow_IF_Implementation() const
{
	return this->bWatchingNow;
}

bool UAnimationManagerComponent::GetLiftingUp2Hands_IF_Implementation() const
{
	return this->bLiftingUp2Hands;
}

bool UAnimationManagerComponent::GetLiftingUp1Hand_IF_Implementation() const
{
	return this->bLiftingUp1Hand;
}

bool UAnimationManagerComponent::GetPutingDown1Hand_IF_Implementation() const
{
	return this->bPutingDown1Hand;
}

bool UAnimationManagerComponent::GetThrowing_IF_Implementation() const
{
	return this->bThrowing;
}

bool UAnimationManagerComponent::GetGettingDamage_IF_Implementation() const
{
	return this->bGettingDamage;
}

bool UAnimationManagerComponent::GetDying_IF_Implementation() const
{
	return this->bDying;
}

bool UAnimationManagerComponent::GetCarrying_IF_Implementation() const
{
	return this->bCarrying;
}

bool UAnimationManagerComponent::GetShortWalk_IF_Implementation() const
{
	return this->bShortWalk;
}

/**
* AnimationManagerInterface methods.
*/
/**
 * Other methods.
 */

void UAnimationManagerComponent::StartTraceAttackRightFoot_IF_Implementation()
{
	if (Owner)
	{
		if (IsInterfaceImplementedBy<IAnimationManagerInterface>(Owner))
		{
			IAnimationManagerInterface::Execute_StartTraceAttackRightFoot_IF(Owner);
		}
		else
		{
			DEBUGMESSAGE("!IsInterfaceImplementedBy<IAnimationManagerInterface>(Owner)")
		}
	}
}

void UAnimationManagerComponent::StopTraceAttackRightFoot_IF_Implementation()
{
	if (Owner)
	{
		if (IsInterfaceImplementedBy<IAnimationManagerInterface>(Owner))
		{
			IAnimationManagerInterface::Execute_StopTraceAttackRightFoot_IF(Owner);
		}
		else
		{
			DEBUGMESSAGE("!IsInterfaceImplementedBy<IAnimationManagerInterface>(Owner)")
		}
	}
}

void UAnimationManagerComponent::StartTraceAttackLeftFoot_IF_Implementation()
{
	if (Owner)
	{
		if (IsInterfaceImplementedBy<IAnimationManagerInterface>(Owner))
		{
			IAnimationManagerInterface::Execute_StartTraceAttackLeftFoot_IF(Owner);
		}
		else
		{
			DEBUGMESSAGE("!IsInterfaceImplementedBy<IAnimationManagerInterface>(Owner)")
		}
	}
}

void UAnimationManagerComponent::StopTraceAttackLeftFoot_IF_Implementation()
{
	if (Owner)
	{
		if (IsInterfaceImplementedBy<IAnimationManagerInterface>(Owner))
		{
			IAnimationManagerInterface::Execute_StopTraceAttackLeftFoot_IF(Owner);
		}
		else
		{
			DEBUGMESSAGE("!IsInterfaceImplementedBy<IAnimationManagerInterface>(Owner)")
		}
	}
}

void UAnimationManagerComponent::SpawnThrowableActor_IF_Implementation()
{
	if (Owner)
	{
		if (IsInterfaceImplementedBy<IAnimationManagerInterface>(Owner))
		{
			IAnimationManagerInterface::Execute_SpawnThrowableActor_IF(Owner);
		}
		else
		{
			DEBUGMESSAGE("!IsInterfaceImplementedBy<IAnimationManagerInterface>(Owner)")
		}
	}
}

void UAnimationManagerComponent::AttachThrowableActor_IF_Implementation()
{
	if (Owner)
	{
		if (IsInterfaceImplementedBy<IAnimationManagerInterface>(Owner))
		{
			IAnimationManagerInterface::Execute_AttachThrowableActor_IF(Owner);
		}
		else
		{
			DEBUGMESSAGE("!IsInterfaceImplementedBy<IAnimationManagerInterface>(Owner)")
		}
	}
}

void UAnimationManagerComponent::AttachLiftingActor_IF_Implementation()
{
	if (Owner)
	{
		if (IsInterfaceImplementedBy<IAnimationManagerInterface>(Owner))
		{
			IAnimationManagerInterface::Execute_AttachLiftingActor_IF(Owner);
		}
		else
		{
			DEBUGMESSAGE("!IsInterfaceImplementedBy<IAnimationManagerInterface>(Owner)")
		}
	}
}

void UAnimationManagerComponent::DetachLiftingActor_IF_Implementation()
{
	if (Owner)
	{
		if (IsInterfaceImplementedBy<IAnimationManagerInterface>(Owner))
		{
			IAnimationManagerInterface::Execute_DetachLiftingActor_IF(Owner);
		}
		else
		{
			DEBUGMESSAGE("!IsInterfaceImplementedBy<IAnimationManagerInterface>(Owner)")
		}
	}
}

void UAnimationManagerComponent::ReportNoise_IF_Implementation()
{
	if (Owner)
	{
		if (IsInterfaceImplementedBy<IAnimationManagerInterface>(Owner))
		{
			IAnimationManagerInterface::Execute_ReportNoise_IF(Owner);
		}
		else
		{
			DEBUGMESSAGE("!IsInterfaceImplementedBy<IAnimationManagerInterface>(Owner)")
		}
	}
}

