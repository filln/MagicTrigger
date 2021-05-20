// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Родительский класс таскаемых предметов.
 */


#include "CarriedItem.h"
#include "MagicTrigger\Interfaces\AnimationManagerInterface.h"
#include "Components/BoxComponent.h"
#include "GameFramework\Character.h"

ACarriedItem::ACarriedItem()
{
	AttachSocket = FName(TEXT("CarryingRightHand"));

	StaticMesh->SetSimulatePhysics(true);
	StaticMesh->SetLinearDamping(10);
	StaticMesh->SetAngularDamping(50);
	StaticMesh->SetEnableGravity(true);
	StaticMesh->bIgnoreRadialImpulse = true;
	StaticMesh->bIgnoreRadialForce = true;
	StaticMesh->bApplyImpulseOnDamage = false;
	StaticMesh->bReplicatePhysicsToAutonomousProxy = false;
	StaticMesh->SetAllMassScale(42);
	StaticMesh->SetPhysicsMaxAngularVelocityInDegrees(5);
	FBodyInstance* BodyInst = StaticMesh->GetBodyInstance();
	if (BodyInst)
	{
		BodyInst->InertiaTensorScale = FVector(0.05);
	}
	else
	{
		DEBUGMESSAGE("!BodyInst");
	}
	BodyInst->UpdateMassProperties();


}

void ACarriedItem::SetPlayingAnimationLiftUp_IF_Implementation(bool bPlaying)
{
	if (!this->PlayerCharacter)
	{
		DEBUGMESSAGE("!this->PlayerCharacter");
		return;
	}
	if (!IsInterfaceImplementedBy<IAnimationManagerInterface>(this->PlayerCharacter))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IAnimationManagerInterface>(this->PlayerCharacter)");
		return;
	}
	IAnimationManagerInterface::Execute_SetPlayingAnimationLiftUp2Hand_IF(this->PlayerCharacter, bPlaying);
}

void ACarriedItem::SetPlayingAnimationPutDown_IF_Implementation(bool bPlaying)
{
	if (!this->PlayerCharacter)
	{
		DEBUGMESSAGE("!this->PlayerCharacter");
		return;
	}
	if (!IsInterfaceImplementedBy<IAnimationManagerInterface>(this->PlayerCharacter))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IAnimationManagerInterface>(this->PlayerCharacter)");
		return;
	}
	IAnimationManagerInterface::Execute_SetPlayingAnimationPutDown2Hand_IF(this->PlayerCharacter, bPlaying);
}

void ACarriedItem::SetSimulatePhysics_IF_Implementation(bool bSimulate)
{
	this->StaticMesh->SetSimulatePhysics(bSimulate);
	FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, true);
	this->Box->AttachToComponent(GetRootComponent(), AttachmentRules, NAME_None);
	this->InteractCollision->AttachToComponent(GetRootComponent(), AttachmentRules, NAME_None);
}
