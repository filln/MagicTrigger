// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "HUDMagicTrigger.h"
#include "MagicTrigger\Data\DebugMessage.h"

#include "MagicTrigger\Interfaces\GameInstanceInterface.h"
#include "MagicTrigger\SaveGame\SaveGameMT.h"
#include "MagicTrigger\SaveGame\SaveGameManager.h"

#include "MagicTrigger\UI\PlayerGUIUserWidget.h"
#include "MagicTrigger\UI\ObserveEnemyUserWidget.h"
#include "MagicTrigger\UI\MenuUserWidget.h"
#include "MagicTrigger\UI\InteractionUserWidget.h"
#include "MagicTrigger\UI\SaveGameMenuUserWidget.h"
#include "MagicTrigger\UI\LoadGameMenuUserWidget.h"
#include "MagicTrigger\UI\SavedGameUserWidget.h"
#include "MagicTrigger\UI\Settings\SettingsMenuUserWidget.h"
#include "MagicTrigger\UI\Settings\ControlUserWidget.h"
#include "MagicTrigger\UI\ListOfSavedGamesUserWidget.h" //SwitchSavedGames()
#include "MagicTrigger\CoreClasses\GameInstanceMagicTrigger.h"

#include "Kismet\GameplayStatics.h"
#include "Kismet\KismetMathLibrary.h"
#include "Kismet\KismetMaterialLibrary.h"

#include "Components\CheckBox.h"
#include "Components\TextBlock.h"
#include "Components\Button.h"
#include "Components\Spacer.h"
#include "Components\Image.h"	//SwitchSavedGames()
#include "Engine\TextureRenderTarget2D.h"



AHUDMagicTrigger::AHUDMagicTrigger()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	PlayerGUIUserWidgetClass = UPlayerGUIUserWidget::StaticClass();
	ObserveEnemyUserWidgetClass = UObserveEnemyUserWidget::StaticClass();
	MenuUserWidgetClass = UMenuUserWidget::StaticClass();
	InteractionUserWidgetClass = UInteractionUserWidget::StaticClass();
	SaveGameMenuUserWidgetClass = USaveGameMenuUserWidget::StaticClass();
	SavedGameUserWidgetClass = USavedGameUserWidget::StaticClass();
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
	UGameInstanceMagicTrigger* GameInstanceMT = Cast<UGameInstanceMagicTrigger>(this->GameInstance);
	if (GameInstanceMT)
	{
		GameInstanceMT->SaveGameManager->HUD = this;
	}
	else
	{
		DEBUGMESSAGE("!GameInstanceMT");
	}

	CreateWidgets();
}

void AHUDMagicTrigger::CreateWidgets()
{
	this->MenuUserWidget = CreateWidget<UMenuUserWidget>(this->PlayerController, MenuUserWidgetClass, FName(TEXT("MenuUserWidget")));
	this->MenuUserWidget->HUDMagicTrigger = this;

	this->PlayerGUIUserWidget = CreateWidget<UPlayerGUIUserWidget>(this->PlayerController, PlayerGUIUserWidgetClass, FName(TEXT("PlayerGUIUserWidget")));
	this->PlayerGUIUserWidget->HUDMagicTrigger = this;
	//��������� �� �������, ����� �� ���������� �� ������ ��������.

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
		if (UGameplayStatics::IsGamePaused(GetWorld()))
		{
			this->PlayerController->SetPause(false);
		}
		SetShowWidget(false, TurnOffWidget, 0);
		SetInputMode(EInputMode::EIM_GameOnly);
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
	if (!this->PlayerController)
	{
		DEBUGMESSAGE("!this->PlayerController");
		return;
	}
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

	return FText::FromString(DateTime);
}

void AHUDMagicTrigger::SwitchSavedGames(bool bCheck, USavedGameUserWidget* InSavedGameUserWidget)
{
	if (!IsInterfaceImplementedBy<IGameInstanceInterface>(this->GameInstance))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IGameInstanceInterface>(this->GameInstance)");
		return;
	}
	//��������� ���� �����.
	if (bCheck)
	{
		//���� ���� ��� ������ �����.
		if (this->LastSavedGame)
		{
			//������� ���������� ���� ����� �����������.
			this->LastSavedGame->SavedGameCheckBox->SetCheckedState(ECheckBoxState::Unchecked);
			
		} 
		//��������� ����� ����.
		this->LastSavedGame = InSavedGameUserWidget;
		//�������� � ����� ��������� ����. ������ �� �������� �� ����������� ���� ��������� ����� ����������� ����
		FText TextOfLoadingGame = InSavedGameUserWidget->NameOfSavedGame->GetText();
		FString StringOfLoadingGame = TextOfLoadingGame.ToString();
		//DEBUGSTRING(StringOfLoadingGame);
		USaveGameMT* SaveGameMT = IGameInstanceInterface::Execute_LoadGamesData_IF(this->GameInstance, StringOfLoadingGame);
		if (!SaveGameMT)
		{
			DEBUGMESSAGE("!SaveGameMT");
			return;
		}
		if (!SaveGameMT->ScreenShot)
		{
			DEBUGMESSAGE("!SaveGameMT->ScreenShot");
			return;
		}

		UImage* SaveGameScreenShotImage = this->SaveGameMenuUserWidget->ListOfSavedGamesUserWidget->ScreenShotImage;
		SetScreenShotToImageWidget(SaveGameMT->ScreenShot, SaveGameScreenShotImage);
		SaveGameScreenShotImage->SetVisibility(ESlateVisibility::Visible);

		UImage* LoadGameScreenShotImage = this->LoadGameMenuUserWidget->ListOfSavedGamesUserWidget->ScreenShotImage;
		SetScreenShotToImageWidget(SaveGameMT->ScreenShot, LoadGameScreenShotImage);
		LoadGameScreenShotImage->SetVisibility(ESlateVisibility::Visible);
	}
	//����������� ���� �����.
	else
	{
		//���� �������� �� ���� �� ����� (�����), �� ������� ��� ���.
		if (this->LastSavedGame == InSavedGameUserWidget)
		{
			this->LastSavedGame->SavedGameCheckBox->SetCheckedState(ECheckBoxState::Checked);
			return;
		}
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
	this->Enemy = InEnemy;
}

AActor* AHUDMagicTrigger::GetEnemy_IF_Implementation() const
{
	return this->Enemy;
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

void AHUDMagicTrigger::SetInputMode_IF_Implementation(EInputMode InInputMode)
{
	SetInputMode(InInputMode);
}

void AHUDMagicTrigger::ShowGameMenu_IF_Implementation()
{
	if (!this->MenuUserWidget)
	{
		DEBUGMESSAGE("!this->MenuUserWidget");
		return;
	}

	SetShowWidget(true, this->MenuUserWidget, 1);
	SetInputMode(EInputMode::EIM_UIOnly);
}

bool AHUDMagicTrigger::CheckMenuUserWidget_IF_Implementation()
{
	return !!this->MenuUserWidget;
}

void AHUDMagicTrigger::ShowPlayerGUIWidget_IF_Implementation()
{
	ShowPlayerGUIWidget();
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
