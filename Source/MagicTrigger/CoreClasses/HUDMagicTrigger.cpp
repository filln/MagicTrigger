// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "HUDMagicTrigger.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "MagicTrigger\Interfaces\PlayerCharacterInterface.h"
#include "MagicTrigger\Interfaces\GameInstanceInterface.h"
#include "MagicTrigger\SaveGame\PlayerStateSaveGame.h"


#include "MagicTrigger\UI\PlayerGUIUserWidget.h"
#include "MagicTrigger\UI\ObserveEnemyUserWidget.h"
#include "MagicTrigger\UI\LoadingUserWidget.h"
#include "MagicTrigger\UI\MenuUserWidget.h"
#include "MagicTrigger\UI\InteractionUserWidget.h"
#include "MagicTrigger\UI\SaveGameMenuUserWidget.h"
#include "MagicTrigger\UI\LoadGameMenuUserWidget.h"
#include "MagicTrigger\UI\SavedGameUserWidget.h"
#include "MagicTrigger\UI\Settings\SettingsMenuUserWidget.h"
#include "MagicTrigger\UI\Settings\ControlUserWidget.h"
#include "MagicTrigger\UI\ListOfSavedGamesUserWidget.h"

#include "Kismet\GameplayStatics.h"
#include "Kismet\KismetMathLibrary.h"
#include "Kismet\KismetMaterialLibrary.h"
#include "GameFramework/Character.h"
#include "Components\EditableTextBox.h"


AHUDMagicTrigger::AHUDMagicTrigger()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	PlayerGUIUserWidgetClass = UPlayerGUIUserWidget::StaticClass();
	ObserveEnemyUserWidgetClass = UObserveEnemyUserWidget::StaticClass();
	LoadingUserWidgetClass = ULoadingUserWidget::StaticClass();
	MenuUserWidgetClass = UMenuUserWidget::StaticClass();
	InteractionUserWidgetClass = UInteractionUserWidget::StaticClass();
	SaveGameMenuUserWidgetClass = USaveGameMenuUserWidget::StaticClass();
	LoadGameMenuUserWidgetClass = ULoadGameMenuUserWidget::StaticClass();
	SettingsMenuUserWidgetClass = USettingsMenuUserWidget::StaticClass();
	ControlUserWidgetClass = UControlUserWidget::StaticClass();

	bShowingHints = true;
	CurrentDateTime = FText::FromString(TEXT("DefaultCurrentDateTime"));
	BeginPlayTimerTime = 0.2;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> ScreenShotMaterialObject(TEXT("/Game/MagicTrigger/Materials/UI/M_ScreenShotMat"));
	if (ScreenShotMaterialObject.Succeeded())
	{
		ScreenShotMaterial = ScreenShotMaterialObject.Object;
	}
	else
	{
		DEBUGMESSAGE("!ScreenShotMaterialObject.Succeeded()");
	}
}


void AHUDMagicTrigger::BeginPlay()
{
	Super::BeginPlay();
	StartBeginPlayTimer_IF_Implementation();

}

void AHUDMagicTrigger::DoBeginPlay_IF_Implementation()
{
	this->PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	this->PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	this->GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	CreateWidgets();
}

void AHUDMagicTrigger::CreateWidgets()
{
	this->MenuUserWidget = CreateWidget<UMenuUserWidget>(this->PlayerController, MenuUserWidgetClass, FName(TEXT("MenuUserWidget")));
	this->MenuUserWidget->HUDMagicTrigger = this;

	this->LoadingUserWidget = CreateWidget<ULoadingUserWidget>(this->PlayerController, LoadingUserWidgetClass, FName(TEXT("LoadingUserWidget")));
	this->LoadingUserWidget->HUDMagicTrigger = this;

	this->PlayerGUIUserWidget = CreateWidget<UPlayerGUIUserWidget>(this->PlayerController, PlayerGUIUserWidgetClass, FName(TEXT("PlayerGUIUserWidget")));
	this->PlayerGUIUserWidget->HUDMagicTrigger = this;
	//Отобразим по таймеру, чтобы не появлялось на экране загрузки.
	FTimerHandle ShowGUITimer;
	GetWorldTimerManager().SetTimer(ShowGUITimer, this, &AHUDMagicTrigger::ShowPlayerGUIWidget, 1);

	this->ObserveEnemyUserWidget = CreateWidget<UObserveEnemyUserWidget>(this->PlayerController, ObserveEnemyUserWidgetClass, FName(TEXT("ObserveEnemyUserWidget")));
	this->ObserveEnemyUserWidget->HUDMagicTrigger = this;

	this->InteractionUserWidget = CreateWidget<UInteractionUserWidget>(this->PlayerController, InteractionUserWidgetClass, FName(TEXT("InteractionUserWidget")));
	this->InteractionUserWidget->HUDMagicTrigger = this;

	this->LoadGameMenuUserWidget = CreateWidget<ULoadGameMenuUserWidget>(this->PlayerController, LoadGameMenuUserWidgetClass, FName(TEXT("LoadGameMenuUserWidget")));
	this->LoadGameMenuUserWidget->HUDMagicTrigger = this;

	this->SaveGameMenuUserWidget = CreateWidget<USaveGameMenuUserWidget>(this->PlayerController, SaveGameMenuUserWidgetClass, FName(TEXT("SaveGameMenuUserWidget")));
	this->SaveGameMenuUserWidget->HUDMagicTrigger = this;

	this->SettingsMenuUserWidget = CreateWidget<USettingsMenuUserWidget>(this->PlayerController, SettingsMenuUserWidgetClass, FName(TEXT("SettingsMenuUserWidget")));
	this->SettingsMenuUserWidget->HUDMagicTrigger = this;

	this->ControlUserWidget = CreateWidget<UControlUserWidget>(this->PlayerController, ControlUserWidgetClass, FName(TEXT("ControlUserWidget")));
	this->ControlUserWidget->HUDMagicTrigger = this;

}

void AHUDMagicTrigger::SetShowWidget(bool bShow, UUserWidget* InUserWidget, int ZOrder)
{
	if (bShow)
	{
		if (InUserWidget->IsVisible())
		{
			return;
		}
		else
		{
			InUserWidget->AddToViewport(ZOrder);
		}

	}
	else
	{
		InUserWidget->RemoveFromViewport();
	}
}

void AHUDMagicTrigger::SetPauseGame(bool bPause, UUserWidget* TurnOffWidget)
{
	if (bPause)
	{
		if (UGameplayStatics::IsGamePaused(GetWorld()))
		{
			return;
		}
		if (this->PlayerController->SetPause(true))
		{
			this->CurrentDateTime = GetCurrentDateTime();
			SetVisibleToButtons();
			SetShowWidget(true, this->MenuUserWidget, 1);
			SetInputMode(EInputMode::EIM_UIOnly);
		}
	}
	else
	{
		if (!UGameplayStatics::IsGamePaused(GetWorld()))
		{
			return;
		}
		this->PlayerController->SetPause(false);
		SetInputMode(EInputMode::EIM_GameOnly);
		SetShowWidget(false, TurnOffWidget, 0);
	}
}

void AHUDMagicTrigger::SetShowInteractionWidget(bool bShow, FText InInteractionText)
{
	if (bShow)
	{
		if (!bShowingHints)
		{
			return;
		}
		this->InteractionText = InInteractionText;
		SetShowWidget(true, this->InteractionUserWidget, 0);
	}
	else
	{
		SetShowWidget(false, this->InteractionUserWidget, 0);
	}
}

void AHUDMagicTrigger::SetInputMode(EInputMode InInputMode)
{
	switch (InInputMode)
	{
	case EInputMode::EIM_UIOnly:
	{
		this->PlayerController->bShowMouseCursor = true;
		FInputModeUIOnly InputModeDataUI;
		InputModeDataUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		this->PlayerController->SetInputMode(InputModeDataUI);
	}
	break;
	case EInputMode::EIM_GameOnly:
	{
		this->PlayerController->bShowMouseCursor = false;
		FInputModeGameOnly InputModeDataGame;
		this->PlayerController->SetInputMode(InputModeDataGame);
	}
	break;
	}
}

void AHUDMagicTrigger::SwitchWidgets(UUserWidget* TurnOffWidget, UUserWidget* TurnOnWidget)
{
	SetShowWidget(false, TurnOffWidget, 0);
	SetShowWidget(true, TurnOnWidget, 1);
}

void AHUDMagicTrigger::PrepareSaveGameMenuWidget()
{
	this->SaveGameMenuUserWidget->ListOfSavedGamesUserWidget->Refresh();
	if (!IsInterfaceImplementedBy<IPlayerCharacterInterface>(this->PlayerCharacter))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IPlayerCharacterInterface>(this->PlayerCharacter)");
		return;
	}

	UTextureRenderTarget2D* ScreenShot = IPlayerCharacterInterface::Execute_CreateScreenShot_IF(this->PlayerCharacter);
	UImage* Image = this->SaveGameMenuUserWidget->ScreenShotOfCurrentSaveGame;
	SetScreenShotToImageWidget(ScreenShot, Image);
	this->SaveGameMenuUserWidget->NameOfCurrentSaveGame->SetText(this->CurrentDateTime);
}

FText AHUDMagicTrigger::GetCurrentDateTime()
{
	FDateTime DateTimeStruct = UKismetMathLibrary::Now();
	FString Year = FString::FromInt(DateTimeStruct.GetYear());
	FString Month = FString::FromInt(DateTimeStruct.GetMonth());
	FString Day = FString::FromInt(DateTimeStruct.GetDay());

	FString Hour = FString::FromInt(DateTimeStruct.GetDay());
	FString Minute = FString::FromInt(DateTimeStruct.GetMinute());
	FString Second = FString::FromInt(DateTimeStruct.GetSecond());

	FString Date = Day.Append("_").Append(Month).Append("_").Append(Year);
	FString Time = Hour.Append("_").Append(Minute).Append("_").Append(Second);
	FString DateTime = Date.Append("__").Append(Time);

	return FText.AsCultureInvariant(DateTime);
}

void AHUDMagicTrigger::SwitchSavedGames(bool bCheck, USavedGameUserWidget* InSavedGameUserWidget)
{
	if (!IsInterfaceImplementedBy<IGameInstanceInterface>(this->GameInstance))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IGameInstanceInterface>(this->GameInstance)");
		return;
	}
	//активация поля сейва.
	if (bCheck)
	{
		//Если сейв был выбран ранее.
		if (this->LastSavedGame)
		{
			//Сделать поле сейва невыбранным.
			this->LastSavedGame->SavedGameCheckBox->SetCheckedState(ECheckBoxState::Unchecked);
		} 
		//Запомнить новое поле.
		this->LastSavedGame = InSavedGameUserWidget;
		//Загрузка и показ скриншота игры. Ссылка на скриншот из сохраненной игры невалидна после перезапуска игры
		FText TextOfLoadingGame = InSavedGameUserWidget->NameOfSavedGame->GetText();
		FString StringOfLoadingGame = TextOfLoadingGame.ToString();
		UPlayerStateSaveGame* PlayerStateSaveGame = IGameInstanceInterface::LoadGamesData_IF(this->GameInstance, StringOfLoadingGame);
		if (!PlayerStateSaveGame)
		{
			DEBUGMESSAGE("!PlayerStateSaveGame");
			return;
		}
		if (!PlayerStateSaveGame->ScreenShot)
		{
			DEBUGMESSAGE("!PlayerStateSaveGame->ScreenShot");
			return;
		}

		UImage* SaveGameScreenShotImage = this->SaveGameMenuUserWidget->ListOfSavedGamesUserWidget->ScreenShotImage;
		SetScreenShotToImageWidget(PlayerStateSaveGame->ScreenShot, SaveGameScreenShotImage);
		SaveGameScreenShotImage->SetVisibility(ESlateVisibility::Visible);

		UImage* LoadGameScreenShotImage = this->LoadGameMenuUserWidget->ListOfSavedGamesUserWidget->ScreenShotImage;
		SetScreenShotToImageWidget(PlayerStateSaveGame->ScreenShot, LoadGameScreenShotImage);
		LoadGameScreenShotImage->SetVisibility(ESlateVisibility::Visible);
	}
	//деактивация поля сейва.
	else
	{
		UImage* SaveGameScreenShotImage = this->SaveGameMenuUserWidget->ListOfSavedGamesUserWidget->ScreenShotImage;
		SaveGameScreenShotImage->SetVisibility(ESlateVisibility::Hidden);

		UImage* LoadGameScreenShotImage = this->LoadGameMenuUserWidget->ListOfSavedGamesUserWidget->ScreenShotImage;
		LoadGameScreenShotImage->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AHUDMagicTrigger::SetScreenShotToImageWidget(UTextureRenderTarget2D* InScreenShot, UImage* InImage)
{
	UMaterialInstanceDynamic* ScreenShotMaterialDynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), this->ScreenShotMaterial); 
	ScreenShotMaterialDynamic->SetTextureParameterValue(FName(TEXT("Texture")), InScreenShot);
	InImage->Brush.SetResourceObject(ScreenShotMaterialDynamic);
}

void AHUDMagicTrigger::PrepareLoadGameMenuWidget()
{
	this->LoadGameMenuUserWidget->ListOfSavedGamesUserWidget->Refresh();
}

void AHUDMagicTrigger::SetVisibleToButtons()
{
	this->MenuUserWidget->ResumeButton->SetVisibility(ESlateVisibility::Visible);
	this->MenuUserWidget->SaveGameMenuButton->SetVisibility(ESlateVisibility::Visible);
	this->MenuUserWidget->SpacerSave->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	this->LoadGameMenuUserWidget->ResumeButton->SetVisibility(ESlateVisibility::Visible);
	this->LoadGameMenuUserWidget->ResumeGameSpacer0->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	this->SettingsMenuUserWidget->ResumeButton->SetVisibility(ESlateVisibility::Visible);
	this->SettingsMenuUserWidget->ResumeGameSpacer0->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	this->ControlUserWidget->ResumeButton->SetVisibility(ESlateVisibility::Visible);
	this->ControlUserWidget->ResumeGameSpacer0->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

}

void AHUDMagicTrigger::HideLoadingWidget()
{
	SetPauseGame(false, this->LoadingUserWidget);
}

void AHUDMagicTrigger::HideLoadGameMenuWidget()
{
	SetShowWidget(false, this->LoadGameMenuUserWidget, 0);
}

void AHUDMagicTrigger::HideMenuWidget()
{
	SetShowWidget(false, this->MenuUserWidget, 0);
}

void AHUDMagicTrigger::HideObserveEnemyWidget()
{
	SetShowWidget(false, this->ObserveEnemyUserWidget, 0);
}

void AHUDMagicTrigger::ShowObserveEnemyWidget()
{
	SetShowWidget(true, this->ObserveEnemyUserWidget, 0);
}

void AHUDMagicTrigger::ShowPlayerGUIWidget()
{
	SetShowWidget(true, this->PlayerGUIUserWidget, 0);
}

void AHUDMagicTrigger::SetEnemy_IF_Implementation(AActor* InEnemy)
{
}

AActor* AHUDMagicTrigger::GetEnemy_IF_Implementation() const
{
	return this->Enemy;
}

void AHUDMagicTrigger::HideLoadingWidget_IF_Implementation()
{
	HideLoadingWidget();
}

void AHUDMagicTrigger::HideLoadGameMenuWidget_IF_Implementation()
{
	HideLoadGameMenuWidget();
}

void AHUDMagicTrigger::HideMenuWidget_IF_Implementation()
{
	HideMenuWidget();
}

void AHUDMagicTrigger::ShowObserveEnemyWidget_IF_Implementation()
{
	ShowObserveEnemyWidget();
}

void AHUDMagicTrigger::HideObserveEnemyWidget_IF_Implementation()
{
	HideObserveEnemyWidget();
}

void AHUDMagicTrigger::SetPauseGame_IF_Implementation(bool bPause, UUserWidget* HiddenWidget)
{
	SetPauseGame(bPause, HiddenWidget);
}

void AHUDMagicTrigger::ShowInteractionWidget_IF_Implementation(FText& InInteractionText)
{
	SetShowInteractionWidget(true, InInteractionText);
}

void AHUDMagicTrigger::HideInteractionWidget_IF_Implementation()
{
	SetShowInteractionWidget(false, FText());
}

bool AHUDMagicTrigger::CheckReferences_IF_Implementation()
{
	APlayerController* PlayerControllerTmp = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerControllerTmp)
	{
		//DEBUGMESSAGE("!PlayerControllerTmp");
		return false;
	}
	ACharacter* PlayerCharacterTmp = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!PlayerCharacterTmp)
	{
		//DEBUGMESSAGE("!PlayerCharacterTmp");
		return false;
	}
	UGameInstance* GameInstanceTmp = UGameplayStatics::GetGameInstance(GetWorld());
	if (!GameInstanceTmp)
	{
		DEBUGMESSAGE("!GameInstanceTmp");
		return false;
	}

	return true;
}

void AHUDMagicTrigger::StartBeginPlayTimer_IF_Implementation()
{
	if (!GetWorld())
	{
		DEBUGMESSAGE("!GetWorld()");
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(this->BeginPlayTimer, this, &AHUDMagicTrigger::BeforeBeginPlay_IF_Implementation, this->BeginPlayTimerTime, true);
}

void AHUDMagicTrigger::BeforeBeginPlay_IF_Implementation()
{
	if (CheckReferences_IF_Implementation())
	{
		GetWorld()->GetTimerManager().ClearTimer(this->BeginPlayTimer);
		DoBeginPlay_IF_Implementation();
	}
}
