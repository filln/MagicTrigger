// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.
/**
 * Меню загрузки игры.
 */

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
	/**
	 * Проверяется, была ли выбрана сохраненная игра в меню. Если не была, то возвращает false. При этом кнопка Load неактивна.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "LoadGameMenuUserWidget")
		bool CheckLastSavedGame();
	UFUNCTION(BlueprintCallable, Category = "LoadGameMenuUserWidget")
		void OnPressedBackMenuButton();
	UFUNCTION(BlueprintCallable, Category = "LoadGameMenuUserWidget")
		void OnPressedResumeButton();
	UFUNCTION(BlueprintCallable, Category = "LoadGameMenuUserWidget")
		void OnPressedLoadButton();

};
