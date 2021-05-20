// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Квестовая платформа, на которую ставятся квестовые боксы. Когда бокс ставится, то платформа плавно опускается как от тяжести бокса.
 Когда бокс поднимается, платформа возвращается.
 Данная платформа отслеживает бокс и дает сигнал на открытие двери-скалы.
 */


#include "PlatformForBox5.h"

void APlatformForBox5::MoveDown(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::MoveDown(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	Platform5OverlapBoxDelegate.ExecuteIfBound();
}
