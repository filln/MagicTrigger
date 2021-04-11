// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "SaveGameManager.h"
#include "MagicTrigger\CoreClasses\HUDMagicTrigger.h"
#include "MagicTrigger\CoreClasses\GameInstanceMagicTrigger.h"
#include "MagicTrigger\CoreClasses\PlayerStateMagicTrigger.h"
#include "MagicTrigger\CoreClasses\PlayerControllerMagicTrigger.h"
#include "MagicTrigger\SaveGame\SaveGameMT.h"
#include "MagicTrigger\SaveGame\GameSettingsSaveGameMT.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "MagicTrigger\PlayerCharacter\PlayerCharacterMagicTrigger.h"
#include "MagicTrigger\UI\LoadingUserWidget.h"
#include "Kismet/GameplayStatics.h"

USaveGameManager::USaveGameManager()
{
	CountOfLoadedElements = 0;
	AllTimersDeltaTime = 0.05;
}

void USaveGameManager::LoadAll(USaveGameMT* InLoadingGame)
{
	FTimerDelegate TmpDelegate;
	FTimerHandle* TmpTimer = &(this->LoadAllTimer);
	size_t* Count = &(this->CountOfLoadedElements);
	const size_t* MaxCount = &(this->MaxCountOfLoadedElements);
	UGameInstanceMagicTrigger* GameInstanceLoc = this->GameInstance;
	AHUDMagicTrigger* HUDLoc = this->HUD;
	TmpDelegate.BindLambda
	(
		[=]
	()
	{
		if (*Count >= *MaxCount)
		{
			*Count = 0;
			if (GameInstanceLoc->LoadingUserWidget)
			{
				GameInstanceLoc->LoadingUserWidget->RemoveFromParent();
			}
			HUDLoc->ShowPlayerGUIWidget();
			HUDLoc->SetInputMode(EInputMode::EIM_GameOnly);
			GameInstanceLoc->GetWorld()->GetTimerManager().ClearTimer(*TmpTimer);
		}
	}
	);
	this->GameInstance->GetWorld()->GetTimerManager().SetTimer(this->LoadAllTimer, TmpDelegate, AllTimersDeltaTime, true);

	CheckHUD();
	LoadPlayerCharacter(InLoadingGame);
	LoadPlayerState(InLoadingGame);

}

void USaveGameManager::SaveAll(USaveGameMT* InSavingGame)
{
	SavePlayerCharacter(InSavingGame);
	SavePlayerState(InSavingGame);
	SaveLevelName(InSavingGame);
}


void USaveGameManager::CheckHUD()
{
	FTimerDelegate TmpDelegate;
	FTimerHandle* TmpTimer = &(this->HUDTimer);
	size_t* Count = &(this->CountOfLoadedElements);
	AHUDMagicTrigger* HUDLoc = this->HUD;
	UGameInstanceMagicTrigger* GameInstanceLoc = this->GameInstance;
	TmpDelegate.BindLambda
	(
		[=]
	()
	{
		if (HUDLoc)
		{

			(*Count)++;
			GameInstanceLoc->GetWorld()->GetTimerManager().ClearTimer(*TmpTimer);
		}
		else
		{
			DEBUGMESSAGE("!this->HUD");
		}
	}
	);
	this->GameInstance->GetWorld()->GetTimerManager().SetTimer(this->HUDTimer, TmpDelegate, AllTimersDeltaTime, true);
}

void USaveGameManager::LoadPlayerCharacter(USaveGameMT* InLoadingGame)
{
	FTimerDelegate TmpDelegate;
	FTimerHandle* TmpTimer = &(this->PlayerCharacterTimer);
	size_t* Count = &(this->CountOfLoadedElements);
	APlayerCharacterMagicTrigger* PlayerLoc = this->PlayerCharacter;
	UGameInstanceMagicTrigger* GameInstanceLoc = this->GameInstance;
	TmpDelegate.BindLambda
	(
		[=]
	()
	{
		if (PlayerLoc)
		{
			FHitResult OutSweepHitResult;
			FVector Location = FVector(InLoadingGame->PlayerLocation.X, InLoadingGame->PlayerLocation.Y, InLoadingGame->PlayerLocation.Z + 40);
			PlayerLoc->SetActorLocation(Location, false, &OutSweepHitResult, ETeleportType::None);
			GameInstanceLoc->GetWorld()->GetTimerManager().ClearTimer(*TmpTimer);
			(*Count)++;
		}
		else
		{
			DEBUGMESSAGE("!this->PlayerCharacter");
		}
	}
	);
	this->GameInstance->GetWorld()->GetTimerManager().SetTimer(this->PlayerCharacterTimer, TmpDelegate, AllTimersDeltaTime, true);

}

void USaveGameManager::SavePlayerCharacter(USaveGameMT* InSavingGame)
{
	if (!this->PlayerCharacter)
	{
		DEBUGMESSAGE("!this->PlayerCharacter");
		return;
	}
	InSavingGame->PlayerLocation = this->PlayerCharacter->GetActorLocation();
	InSavingGame->ScreenShot = this->PlayerCharacter->CreateScreenShot();
}

void USaveGameManager::LoadPlayerState(USaveGameMT* InLoadingGame)
{
	FTimerDelegate TmpDelegate;
	FTimerHandle* TmpTimer = &(this->PlayerStateTimer);
	size_t* Count = &(this->CountOfLoadedElements);
	APlayerStateMagicTrigger* PlayerStateLoc = this->PlayerState;
	UGameInstanceMagicTrigger* GameInstanceLoc = this->GameInstance;
	TmpDelegate.BindLambda
	(
		[=]
	()
	{
		if (PlayerStateLoc)
		{
			PlayerStateLoc->SetStates(InLoadingGame->StatesStruct);
			(*Count)++;
			GameInstanceLoc->GetWorld()->GetTimerManager().ClearTimer(*TmpTimer);
		}
		else
		{
			DEBUGMESSAGE("!this->PlayerState");
		}
	}
	);
	this->GameInstance->GetWorld()->GetTimerManager().SetTimer(this->PlayerStateTimer, TmpDelegate, AllTimersDeltaTime, true);
}

void USaveGameManager::SavePlayerState(USaveGameMT* InSavingGame)
{
	if (!this->PlayerState)
	{
		DEBUGMESSAGE("!this->PlayerState");
		return;
	}
	InSavingGame->StatesStruct = this->PlayerState->GetStates();
}

void USaveGameManager::LoadGameSettings(UGameSettingsSaveGameMT* InLoadingGame)
{
	if (!this->GameInstance)
	{
		DEBUGMESSAGE("!this->GameInstance");
		return;
	}
	if (!InLoadingGame)
	{
		DEBUGMESSAGE("!InLoadingGame");
		return;
	}
	if (!this->GameInstance->GetWorld())
	{
		DEBUGMESSAGE("!this->GameInstance->GetWorld()");
		return;
	}
	FTimerDelegate TmpDelegate;
	FTimerHandle* TmpTimer = &(this->LoadSettingsTimer);
	//Нужен двойной указатель, т.к. в момент присваивания указатель еще невалиден, в лямбду передается его копия. Передать по ссылке не получится, т.к.
	//при переходе в лямбду произойдет выход из этой функции и все ее лок. переменные уничтожатся. 
	APlayerControllerMagicTrigger** PlayerControllerLoc = &(this->PlayerController);
	UGameInstanceMagicTrigger* GameInstanceLoc = this->GameInstance;
	TmpDelegate.BindLambda
	(
		[=]
	()
	{
		if (*PlayerControllerLoc)
		{
			(*PlayerControllerLoc)->SetInputRotationScale(InLoadingGame->MouseSensitivity);
			GameInstanceLoc->GetWorld()->GetTimerManager().ClearTimer(*TmpTimer);
		}
	}
	);
	this->GameInstance->GetWorld()->GetTimerManager().SetTimer(this->LoadSettingsTimer, TmpDelegate, AllTimersDeltaTime, true);
}


void USaveGameManager::SaveGameSettings(UGameSettingsSaveGameMT* InSavingGame)
{
	if (!this->PlayerController)
	{
		DEBUGMESSAGE("!this->PlayerController");
		return;
	}
	if (!InSavingGame)
	{
		DEBUGMESSAGE("!InSavingGame");
	}
	InSavingGame->MouseSensitivity = this->PlayerController->MouseSensitivity;

}

void USaveGameManager::ResetGameSettings()
{
	if (!this->GameInstance)
	{
		DEBUGMESSAGE("!this->GameInstance");
		return;
	}
	if (!this->GameInstance->GetWorld())
	{
		DEBUGMESSAGE("!this->GameInstance->GetWorld()");
		return;
	}
	FTimerDelegate TmpDelegate;
	FTimerHandle* TmpTimer = &(this->LoadSettingsTimer);
	APlayerControllerMagicTrigger** PlayerControllerLoc = &(this->PlayerController);
	UGameInstanceMagicTrigger* GameInstanceLoc = this->GameInstance;
	TmpDelegate.BindLambda
	(
		[=]
	()
	{
		if (*PlayerControllerLoc)
		{
			(*PlayerControllerLoc)->SetInputRotationScale(GameInstanceLoc->GameSettingsStruct.MouseSensitivity);
			GameInstanceLoc->GetWorld()->GetTimerManager().ClearTimer(*TmpTimer);
		}
	}
	);
	this->GameInstance->GetWorld()->GetTimerManager().SetTimer(this->LoadSettingsTimer, TmpDelegate, AllTimersDeltaTime, true);
}

void USaveGameManager::SaveLevelName(USaveGameMT* InSavingGame)
{
	InSavingGame->LevelName = GameInstance->GetNameOfCurrentLevel();
}
