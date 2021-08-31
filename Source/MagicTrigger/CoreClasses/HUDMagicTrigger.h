// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MagicTrigger/Interfaces/HUDInterface.h"
#include "MagicTrigger/Interfaces/BeginPlayInterface.h"
#include "MagicTrigger/Data/InputModeEnum.h"
#include "HUDMagicTrigger.generated.h"

class UPlayerGUIUserWidget;
class UObserveEnemyUserWidget;
class UMenuUserWidget;
class UInteractionUserWidget;
class USaveGameMenuUserWidget;
class USavedGameUserWidget;
class ULoadGameMenuUserWidget;
class USettingsMenuUserWidget;
class UControlUserWidget;
class UTextureRenderTarget2D;
class UImage;
class APlayerController;
class APlayerControllerMagicTrigger;
class APlayerState;
class ACharacter;
class UGameInstance;
class UGameInstanceMagicTrigger;
class UMaterialInterface;

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API AHUDMagicTrigger : public AHUD,
                                          public IHUDInterface,
                                          public IBeginPlayInterface
{
	GENERATED_BODY()

public:
	AHUDMagicTrigger();

	/**
	 * Variables
	 */
public:
	/**
	 * Classes of Widgets.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUDMagicTrigger|WidgetsClasses")
	TSubclassOf<UPlayerGUIUserWidget> PlayerGUIUserWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUDMagicTrigger|WidgetsClasses")
	TSubclassOf<UObserveEnemyUserWidget> ObserveEnemyUserWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUDMagicTrigger|WidgetsClasses")
	TSubclassOf<UMenuUserWidget> MenuUserWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUDMagicTrigger|WidgetsClasses")
	TSubclassOf<UInteractionUserWidget> InteractionUserWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUDMagicTrigger|WidgetsClasses")
	TSubclassOf<USaveGameMenuUserWidget> SaveGameMenuUserWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUDMagicTrigger|WidgetsClasses")
	TSubclassOf<USavedGameUserWidget> SavedGameUserWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUDMagicTrigger|WidgetsClasses")
	TSubclassOf<ULoadGameMenuUserWidget> LoadGameMenuUserWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUDMagicTrigger|WidgetsClasses")
	TSubclassOf<USettingsMenuUserWidget> SettingsMenuUserWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUDMagicTrigger|WidgetsClasses")
	TSubclassOf<UControlUserWidget> ControlUserWidgetClass;

	/**
	 * References to Widgets.
	 */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "HUDMagicTrigger|Widgets")
	UPlayerGUIUserWidget* PlayerGUIUserWidget;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "HUDMagicTrigger|Widgets")
	UObserveEnemyUserWidget* ObserveEnemyUserWidget;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "HUDMagicTrigger|Widgets")
	UMenuUserWidget* MenuUserWidget;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "HUDMagicTrigger|Widgets")
	UInteractionUserWidget* InteractionUserWidget;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "HUDMagicTrigger|Widgets")
	USaveGameMenuUserWidget* SaveGameMenuUserWidget;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "HUDMagicTrigger|Widgets")
	USavedGameUserWidget* LastSavedGame;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "HUDMagicTrigger|Widgets")
	ULoadGameMenuUserWidget* LoadGameMenuUserWidget;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "HUDMagicTrigger|Widgets")
	USettingsMenuUserWidget* SettingsMenuUserWidget;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "HUDMagicTrigger|Widgets")
	UControlUserWidget* ControlUserWidget;
	//////////////////////////////////////////////////////////////////////////

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "HUDMagicTrigger|CoreClasses")
	UGameInstance* GameInstance;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "HUDMagicTrigger")
	UMaterialInterface* ScreenShotMaterial;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "HUDMagicTrigger")
	AActor* Enemy;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "HUDMagicTrigger")
	FText CurrentDateTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUDMagicTrigger")
	bool bShowingHints;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "HUDMagicTrigger")
	FText InteractionText;
	UPROPERTY()
	ACharacter* PlayerCharacter;
	UPROPERTY()
	UGameInstanceMagicTrigger* GameInstanceMT;
	UPROPERTY()
	APlayerController* PlayerController;
	UPROPERTY()
	APlayerControllerMagicTrigger* PlayerControllerMT;
private:
	FTimerHandle BeginPlayTimer;
	float BeginPlayTimerTime;


	/**
	 * Methods
	 */
private:
	void CreateWidgets();


public:
	virtual void BeginPlay() override;
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "HUDMagicTrigger")
	void SetShowWidget(bool bShow, UUserWidget* InUserWidget, int ZOrder);
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "HUDMagicTrigger")
	void SetPauseGame(bool bPause, UUserWidget* TurnOffWidget);
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "HUDMagicTrigger")
	void SetShowInteractionWidget(bool bShow, FText InInteractionText);
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "HUDMagicTrigger")
	void SetInputMode(EInputMode InInputMode);
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "HUDMagicTrigger")
	void SwitchWidgets(UUserWidget* TurnOffWidget, UUserWidget* TurnOnWidget);
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "HUDMagicTrigger")
	FText GetCurrentDateTime();
	/**
	 *Просмотр, выбор сохраненных игр. Используется в виджете, когда ЛКМ по полю сохраненной игры. Если поле выбирается, то входит bCheck == true, если
	 поле автоматически перестает быть выбранным, то входит bCheck == false.
	 Поле с игрой делается выделенным автоматически при ЛКМ, а метод снимает выделение с предыдущего поля и сохраняет ссылку на выделенный виджет.
	 */
	UFUNCTION(BlueprintCallable, Category = "HUDMagicTrigger")
	void SwitchSavedGames(bool bCheck, USavedGameUserWidget* InSavedGameUserWidget);
	/**
	 *Применить скриншот к виджету изображения. Не получится без материала-посредника
	 */
	UFUNCTION(BlueprintCallable, Category = "HUDMagicTrigger")
	void SetScreenShotToImageWidget(UTextureRenderTarget2D* InScreenShot, UImage* InImage);
	/**
	 *При выходе в меню после первого начала игры показать кнопки для сохранения и продолжения игры
	 */
	UFUNCTION(BlueprintCallable, Category = "HUDMagicTrigger")
	void SetVisibleToButtons();
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "HUDMagicTrigger")
	void HideLoadGameMenuWidget();
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "HUDMagicTrigger")
	void HideMenuWidget();
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "HUDMagicTrigger")
	void HideObserveEnemyWidget();
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "HUDMagicTrigger")
	void ShowObserveEnemyWidget();

	/**
	 *
	 */
	void CreatePlayerGUIUserWidget(APlayerController* InPlayerController);
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "HUDMagicTrigger")
	void ShowPlayerGUIWidget();

	bool CheckMenuUserWidget();
	void ShowGameMenu();

	/**
	 * GameInstance
	 */
	bool MainSaveGame(const FString& NameOfSaveGame, TArray<FString>& InGamesList);
	void MainLoadGame(const FString& NameOfLoadGame);
	void BeginNewGame();
	void SaveGameSettings();

	/**
	 *PlayerController
	 */
	float GetMouseSensitivity() const;
	void SetInputRotationScale(float InMouseSensitivity) const;

	/**
	 * Interface methods
	 */
public:
	/**
	 * HUDInterface
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HUDInterface")
	void SetEnemy_IF(AActor* InEnemy);
	virtual void SetEnemy_IF_Implementation(AActor* InEnemy) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HUDInterface")
	AActor* GetEnemy_IF() const;
	virtual AActor* GetEnemy_IF_Implementation() const override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HUDInterface")
	void HideLoadGameMenuWidget_IF();
	virtual void HideLoadGameMenuWidget_IF_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HUDInterface")
	void HideMenuWidget_IF();
	virtual void HideMenuWidget_IF_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HUDInterface")
	void ShowObserveEnemyWidget_IF();
	virtual void ShowObserveEnemyWidget_IF_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HUDInterface")
	void HideObserveEnemyWidget_IF();
	virtual void HideObserveEnemyWidget_IF_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HUDInterface")
	void SetPauseGame_IF(bool bPause, UUserWidget* HiddenWidget);
	virtual void SetPauseGame_IF_Implementation(bool bPause, UUserWidget* HiddenWidget) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HUDInterface")
	void ShowInteractionWidget_IF(FText& InInteractionText);
	virtual void ShowInteractionWidget_IF_Implementation(FText& InInteractionText) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HUDInterface")
	void HideInteractionWidget_IF();
	virtual void HideInteractionWidget_IF_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HUDInterface")
	void SetInputMode_IF(EInputMode InInputMode);
	virtual void SetInputMode_IF_Implementation(EInputMode InInputMode) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HUDInterface")
	void ShowGameMenu_IF();
	virtual void ShowGameMenu_IF_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HUDInterface")
	bool CheckMenuUserWidget_IF();
	virtual bool CheckMenuUserWidget_IF_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HUDInterface")
	void ShowPlayerGUIWidget_IF();
	virtual void ShowPlayerGUIWidget_IF_Implementation() override;

	/**
	 * BeginplayInterface
	 */

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BeginPlayInterface")
	bool CheckReferences_IF();
	virtual bool CheckReferences_IF_Implementation() override;
	//Выполнить логику для BeginPlay.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BeginPlayInterface")
	void DoBeginPlay_IF();
	virtual void DoBeginPlay_IF_Implementation() override;
	//Запустить BeginPlayTimer.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BeginPlayInterface")
	void StartBeginPlayTimer_IF();
	virtual void StartBeginPlayTimer_IF_Implementation() override;
	//Выполняется в таймере для получения нужных ссылок.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BeginPlayInterface")
	void BeforeBeginPlay_IF();
	virtual void BeforeBeginPlay_IF_Implementation() override;
};
