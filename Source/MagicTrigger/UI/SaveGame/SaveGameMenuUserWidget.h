// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.
/**
 * Меню сохранения игры.
 */

#pragma once

#include "MagicTrigger/UI/ParentUserWidgetMT.h"
#include "SaveGameMenuUserWidget.generated.h"

class UListOfSavedGamesUserWidget;
class UImage;
class UEditableTextBox;
class UButton;

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API USaveGameMenuUserWidget : public UParentUserWidgetMT
{
	GENERATED_BODY()


public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "SaveGameMenuUserWidget")
		UListOfSavedGamesUserWidget* ListOfSavedGamesUserWidget;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "SaveGameMenuUserWidget")
		UImage* ScreenShotOfCurrentSaveGame;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "SaveGameMenuUserWidget")
		UEditableTextBox* NameOfCurrentSaveGame;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "SaveGameMenuUserWidget")
		UButton* ResumeButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "SaveGameMenuUserWidget")
		UButton* BackMenuButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "SaveGameMenuUserWidget")
		UButton* DeleteSaveButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "SaveGameMenuUserWidget")
		UButton* SaveButton;


public:
	/**
	 * Обновить список сохраненных игр и заполнить изображение скриншота. Напрямую RenderTarget2D не выводится в виджет, нужно делать материал с параметром MaterialDomain "User Interface"
	 Вызывается в MenuUserWidget при нажатии кнопки Save game
	 */
	UFUNCTION(BlueprintCallable, Category = "SaveGameMenuUserWidget")
		void Prepare();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "SaveGameMenuUserWidget")
		bool CheckLastSavedGame();
	UFUNCTION(BlueprintCallable, Category = "LoadGameMenuUserWidget")
		void OnPressedBackMenuButton();
	UFUNCTION(BlueprintCallable, Category = "LoadGameMenuUserWidget")
		void OnPressedResumeButton();
	UFUNCTION(BlueprintCallable, Category = "LoadGameMenuUserWidget")
		void OnClickedSaveButton();
	UFUNCTION(BlueprintCallable, Category = "LoadGameMenuUserWidget")
		void OnClickedDeleteSaveButton();

};
