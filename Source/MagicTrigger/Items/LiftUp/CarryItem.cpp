// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Родительский класс таскаемых предметов.
 */


#include "CarryItem.h"
#include "MagicTrigger\Interfaces\AnimationManagerInterface.h"
#include "Components/BoxComponent.h"
#include "MagicTrigger\PlayerCharacter\PlayerCharacterMagicTrigger.h"

ACarryItem::ACarryItem()
{
	AttachSocket = FName(TEXT("CarryRightHand"));
}

void ACarryItem::BeginPlay()
{
	Super::BeginPlay();
	InteractionText = FText::FromStringTable("/Game/MagicTrigger/Data/ST_Interaction.ST_Interaction", "CarryTip");
	if (InteractionText.IsEmpty())
	{
		DEBUGMESSAGE("InteractionText.IsEmpty()");

	}
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
		BodyInst->UpdateMassProperties();
	}
	else
	{
		DEBUGMESSAGE("!BodyInst");
	}
}

void ACarryItem::LiftUpItself_IF_Implementation()
{
	PlayerCharacter->SetPlayingAnimationLiftUp2Hands(true);
}

void ACarryItem::PutDownItself_IF_Implementation()
{
	PlayerCharacter->SetPlayingAnimationPutDown2Hands(true);
}

