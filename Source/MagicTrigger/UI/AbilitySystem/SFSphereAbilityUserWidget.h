// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.
/*
Виджет абилки семикратной сферы.
*/

#pragma once

#include "CoreMinimal.h"
#include "MagicTrigger/UI/ParentUserWidgetMT.h"
#include "SFSphereAbilityUserWidget.generated.h"

class UImage;
class UTextBlock;


/**
 *
 */
UCLASS()
class MAGICTRIGGER_API USFSphereAbilityUserWidget : public UParentUserWidgetMT
{
	GENERATED_BODY()

public:

	USFSphereAbilityUserWidget();

	/**
	 * Variables
	 */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "SFSphereAbilityUserWidget")
		UImage* IconImage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "SFSphereAbilityUserWidget")
		UTextBlock* CountText;
	int Count;
	/**
	 * Methods
	 */
protected:

	virtual void NativeConstruct() override;


};
