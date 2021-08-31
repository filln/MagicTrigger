// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * боксы для расстановки на платформы для квеста.
 */

#pragma once

#include "CoreMinimal.h"
#include "MagicTrigger/Items/LiftUp/CarryItem.h"
#include "BoxForPlatformParent.generated.h"


 /**
  *
  */
UCLASS()
class MAGICTRIGGER_API ABoxForPlatformParent : public ACarryItem
{
	GENERATED_BODY()

public:
	ABoxForPlatformParent();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FVector InitialLocation;
	float MoveUpOverTime;
	float MoveHorizontalOverTime;
	float MoveDownOverTime;
	float MoveUpHigh;
public:
	void MoveToInitialLocation();

private:

	void MoveUp();
	UFUNCTION()
		void MoveHorizontal();
	UFUNCTION()
		void MoveDown();
	UFUNCTION()
		void SetEnableInteraction(bool bInEnable);
};
