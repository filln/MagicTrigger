// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

#pragma once

#include "MagicTrigger\UI\ParentUserWidgetMT.h"
#include "MenuUserWidget.generated.h"

class UButton;
class USpacer;

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API UMenuUserWidget : public UParentUserWidgetMT
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
		/**
		 * Variables
		 */
public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "MenuUserWidget")
		UButton* ResumeButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "MenuUserWidget")
		UButton* SaveGameMenuButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "MenuUserWidget")
		UButton* ExitButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "MenuUserWidget")
		UButton* LoadGameMenuButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "MenuUserWidget")
		UButton* NewGameButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "MenuUserWidget")
		UButton* SettingsButton;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "MenuUserWidget")
		USpacer* SpacerSave;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "MenuUserWidget")
		USpacer* SpacerLoad;

private:
	FTimerHandle CheckHUDTimer;
	/**
	 * Methods
	 */
public:

	UFUNCTION(BlueprintCallable, Category = "MenuUserWidget")
		void OnPressedResumeButton();
	UFUNCTION(BlueprintCallable, Category = "MenuUserWidget")
		void OnPressedExitButton();
	UFUNCTION(BlueprintCallable, Category = "MenuUserWidget")
		void OnPressedNewGameButton();
	UFUNCTION(BlueprintCallable, Category = "MenuUserWidget")
		void OnPressedSaveGameMenuButton();
	UFUNCTION(BlueprintCallable, Category = "MenuUserWidget")
		void OnPressedSettingsButton();
	UFUNCTION(BlueprintCallable, Category = "MenuUserWidget")
		void OnPressedLoadGameMenuButton();


};
