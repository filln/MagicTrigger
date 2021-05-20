// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Родительский класс таскаемых предметов.
 */

#pragma once

#include "CoreMinimal.h"
#include "LiftingItem.h"
#include "CarriedItem.generated.h"

/**
 * 
 */
UCLASS()
class MAGICTRIGGER_API ACarriedItem : public ALiftingItem
{
	GENERATED_BODY()
public:
	ACarriedItem();

public:

	virtual void SetPlayingAnimationLiftUp_IF_Implementation(bool bPlaying) override;
	virtual void SetPlayingAnimationPutDown_IF_Implementation(bool bPlaying) override;
	virtual void SetSimulatePhysics_IF_Implementation(bool bSimulate) override;
};
