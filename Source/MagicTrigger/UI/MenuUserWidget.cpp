// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "MenuUserWidget.h"
#include "MagicTrigger\CoreClasses\HUDMagicTrigger.h"
#include "MagicTrigger\Interfaces\GameInstanceInterface.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "MagicTrigger\UI\Settings\SettingsMenuUserWidget.h"
#include "MagicTrigger\UI\SaveGameMenuUserWidget.h"
#include "MagicTrigger\UI\LoadGameMenuUserWidget.h"
#include "MagicTrigger\UI\ListOfSavedGamesUserWidget.h"

#include "Kismet\KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Components\Button.h"
#include "Components\Spacer.h"

void UMenuUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	//DEBUGMESSAGE("NativeOnInitialized");
	//Проверить, есть ли сохраненные игры. Если нет, то скрыть кнопку загрузки игры.
	//FTimerHandle* TmpTimer = &(this->CheckHUDTimer);
	//FTimerDelegate TmpDelegate;
	//AHUDMagicTrigger** HUD = &(this->HUDMagicTrigger);
	//UButton* ButtonLoc = this->LoadGameMenuButton;
	//USpacer* SpacerLoc = this->SpacerLoad;
	//TmpDelegate.BindLambda
	//(
	//	[=]
	//()
	//{
	//	if (*HUD)
	//	{
	//		if (IsInterfaceImplementedBy<IGameInstanceInterface>((*HUD)->GameInstance))
	//		{
				//bool bVisible = UGameplayStatics::DoesSaveGameExist(IGameInstanceInterface::Execute_GetGamesListName_IF((*HUD)->GameInstance), 0);
				//if (bVisible)
				//{
				//	ButtonLoc->SetVisibility(ESlateVisibility::Visible);
				//	SpacerLoc->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
				//}
				//else
				//{
				//	ButtonLoc->SetVisibility(ESlateVisibility::Collapsed);
				//	SpacerLoc->SetVisibility(ESlateVisibility::Collapsed);
				//}
	//		}
	//		GetWorld()->GetTimerManager().ClearTimer(*TmpTimer);
	//	}
	//}
	//);
	//GetWorld()->GetTimerManager().SetTimer(this->CheckHUDTimer, TmpDelegate, 0.05, true);
}


void UMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//Проверить, есть ли сохраненные игры. Если нет, то скрыть кнопку загрузки игры.
	if (this->HUDMagicTrigger)
	{
		if (IsInterfaceImplementedBy<IGameInstanceInterface>(this->HUDMagicTrigger->GameInstance))
		{
			bool bVisible = UGameplayStatics::DoesSaveGameExist(IGameInstanceInterface::Execute_GetGamesListName_IF(this->HUDMagicTrigger->GameInstance), 0);
			if (bVisible)
			{
				this->LoadGameMenuButton->SetVisibility(ESlateVisibility::Visible);
				this->SpacerLoad->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			}
			else
			{
				this->LoadGameMenuButton->SetVisibility(ESlateVisibility::Collapsed);
				this->SpacerLoad->SetVisibility(ESlateVisibility::Collapsed);
			}
		}
	}
	//DEBUGMESSAGE("NativeConstruct");
}

void UMenuUserWidget::OnPressedResumeButton()
{
	this->HUDMagicTrigger->SetPauseGame(false, this);
}

void UMenuUserWidget::OnPressedExitButton()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void UMenuUserWidget::OnPressedNewGameButton()
{
	if (!IsInterfaceImplementedBy<IGameInstanceInterface>(this->HUDMagicTrigger->GameInstance))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy(this->HUDMagicTrigger->GameInstance)");
		return;
	}

	IGameInstanceInterface::Execute_BeginNewGame_IF(this->HUDMagicTrigger->GameInstance);
}

void UMenuUserWidget::OnPressedSaveGameMenuButton()
{
	this->HUDMagicTrigger->SaveGameMenuUserWidget->Prepare();
	this->HUDMagicTrigger->SwitchWidgets(this, this->HUDMagicTrigger->SaveGameMenuUserWidget);
}

void UMenuUserWidget::OnPressedSettingsButton()
{
	this->HUDMagicTrigger->SwitchWidgets(this, this->HUDMagicTrigger->SettingsMenuUserWidget);
}

void UMenuUserWidget::OnPressedLoadGameMenuButton()
{

	if (!this->HUDMagicTrigger->LoadGameMenuUserWidget->ListOfSavedGamesUserWidget)
	{
		DEBUGMESSAGE("!this->HUDMagicTrigger->LoadGameMenuUserWidget->ListOfSavedGamesUserWidget");
		return;
	}
	this->HUDMagicTrigger->LoadGameMenuUserWidget->ListOfSavedGamesUserWidget->Refresh();
	this->HUDMagicTrigger->SwitchWidgets(this, this->HUDMagicTrigger->LoadGameMenuUserWidget);
}
