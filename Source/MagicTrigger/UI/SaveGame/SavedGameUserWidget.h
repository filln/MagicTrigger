// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

#pragma once

#include "MagicTrigger\UI\ParentUserWidgetMT.h"
#include "SavedGameUserWidget.generated.h"

class UCheckBox;
class UTextBlock;
/**
 *
 */
UCLASS()
class MAGICTRIGGER_API USavedGameUserWidget : public UParentUserWidgetMT
{
	GENERATED_BODY()

protected:

	virtual void NativeOnInitialized() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SavedGameUserWidget")
		UCheckBox* SavedGameCheckBox;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SavedGameUserWidget")
		UTextBlock* NameOfSavedGame;

public:

	UFUNCTION(BlueprintCallable, Category = "SavedGameUserWidget")
		void OnCheckStateChangedSavedGameCheckBox(bool bChecked);
};
