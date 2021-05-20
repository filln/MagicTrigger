// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * ��������� ���������, �� ������� �������� ��������� �����. ����� ���� ��������, �� ��������� ������ ���������� ��� �� ������� �����.
 ����� ���� �����������, ��������� ������������.
 ������ ��������� ����������� ���� � ���� ������ �� �������� �����-�����.
 */

#pragma once

#include "CoreMinimal.h"
#include "MagicTrigger\Quests\QuestSevenfoldSphere\PlatformForBoxParent.h"
#include "PlatformForBox4.generated.h"

/**
 *
 */

//���������� � UQuestSevenfoldSphereComponent
DECLARE_DELEGATE(FPlatform4OverlapBoxDelegate);

UCLASS()
class MAGICTRIGGER_API APlatformForBox4 : public APlatformForBoxParent
{
	GENERATED_BODY()

public:

	virtual void MoveDown(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	FPlatform4OverlapBoxDelegate Platform4OverlapBoxDelegate;

};
