// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Родительский класс таскаемых предметов.
 */

#pragma once

#include "CoreMinimal.h"
#include "LiftUpItem.h"
#include "CarryItem.generated.h"

/**
 * 
 */
UCLASS()
class MAGICTRIGGER_API ACarryItem : public ALiftUpItem
{
	GENERATED_BODY()
public:
	ACarryItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	virtual void LiftUpItself_IF_Implementation() override;
	virtual void PutDownItself_IF_Implementation() override;

};
