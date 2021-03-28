﻿// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

#pragma once

#include "MagicTrigger\UI\ParentUserWidgetMT.h"
#include "LoadGameMenuUserWidget.generated.h"

class UListOfSavedGamesUserWidget;
class UButton;
class USpacer;

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API ULoadGameMenuUserWidget : public UParentUserWidgetMT
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "LoadGameMenuUserWidget")
		UListOfSavedGamesUserWidget* ListOfSavedGamesUserWidget;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "LoadGameMenuUserWidget")
		UButton* ResumeButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "LoadGameMenuUserWidget")
		UButton* BackMenuButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "LoadGameMenuUserWidget")
		UButton* LoadButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "LoadGameMenuUserWidget")
		USpacer* ResumeGameSpacer0;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LoadGameMenuUserWidget")
		bool CheckLastSavedGame();
	UFUNCTION(BlueprintCallable, Category = "LoadGameMenuUserWidget")
		void OnPressedBackMenuButton();
	UFUNCTION(BlueprintCallable, Category = "LoadGameMenuUserWidget")
		void OnPressedResumeButton();
	UFUNCTION(BlueprintCallable, Category = "LoadGameMenuUserWidget")
		void OnPressedLoadButton();

};
