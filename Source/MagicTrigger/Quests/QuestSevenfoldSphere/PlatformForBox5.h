// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Квестовая платформа, на которую ставятся квестовые боксы. Когда бокс ставится, то платформа плавно опускается как от тяжести бокса.
 Когда бокс поднимается, платформа возвращается.
 Данная платформа отслеживает бокс и дает сигнал на открытие двери-скалы.
 */

#pragma once

#include "CoreMinimal.h"
#include "MagicTrigger/Quests/QuestSevenfoldSphere/PlatformForBoxParent.h"
#include "PlatformForBox5.generated.h"

 /**
  *
  */

  //Вызывается в UQuestSevenfoldSphereComponent
DECLARE_DELEGATE(FPlatform5OverlapBoxDelegate);

UCLASS()
class MAGICTRIGGER_API APlatformForBox5 : public APlatformForBoxParent
{
	GENERATED_BODY()

public:

	virtual void MoveDown(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	FPlatform5OverlapBoxDelegate Platform5OverlapBoxDelegate;
};
