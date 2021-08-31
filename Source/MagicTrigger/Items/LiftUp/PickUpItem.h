// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

/**
 * Предметы, которые поднимаются для инвентаря или абилок.
 */

#pragma once

#include "CoreMinimal.h"
#include "MagicTrigger/Items/LiftUp/LiftUpItem.h"
#include "PickUpItem.generated.h"

/**
 * 
 */
UCLASS()
class MAGICTRIGGER_API APickUpItem : public ALiftUpItem
{
	GENERATED_BODY()
	
public:

	APickUpItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void LiftUpItself_IF_Implementation() override;
};
