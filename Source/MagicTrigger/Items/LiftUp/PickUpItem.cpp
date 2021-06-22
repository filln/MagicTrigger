// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "PickUpItem.h"
#include "MagicTrigger\PlayerCharacter\PlayerCharacterMagicTrigger.h"

APickUpItem::APickUpItem()
{
	AttachSocket = FName(TEXT("PickUpRightHand"));
}

void APickUpItem::BeginPlay()
{
	Super::BeginPlay();
	InteractionText = FText::FromStringTable("/Game/MagicTrigger/Data/ST_Interaction.ST_Interaction", "PickUpTip");
	if (InteractionText.IsEmpty())
	{
		DEBUGMESSAGE("InteractionText.IsEmpty()");

	}
}

void APickUpItem::LiftUpItself_IF_Implementation()
{
	PlayerCharacter->SetPlayingAnimationLiftUp1Hand(true);
}
