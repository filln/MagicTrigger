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
#include "MagicTrigger\UI\SaveGame\LoadingUserWidget.h"
#include "Kismet/GameplayStatics.h"

USaveGameManager::USaveGameManager()
{
	CountOfLoadedElements = 0;
	AllTimersDeltaTime = 0.05;
}

void USaveGameManager::LoadAll(USaveGameMT* InLoadingGame)
{
	FTimerDelegate TmpDelegate;
	FTimerHandle* TmpTimer = &(LoadAllTimer);
	size_t* Count = &(CountOfLoadedElements);
	const size_t* MaxCount = &(MaxCountOfLoadedElements);
	UGameInstanceMagicTrigger* GameInstanceLoc = GameInstance;
	AHUDMagicTrigger* HUDLoc = HUD;
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
	GameInstance->GetWorld()->GetTimerManager().SetTimer(LoadAllTimer, TmpDelegate, AllTimersDeltaTime, true);

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
	FTimerHandle* TmpTimer = &(HUDTimer);
	size_t* Count = &(CountOfLoadedElements);
	AHUDMagicTrigger* HUDLoc = HUD;
	UGameInstanceMagicTrigger* GameInstanceLoc = GameInstance;
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
			DEBUGMESSAGE("!HUD");
		}
	}
	);
	GameInstance->GetWorld()->GetTimerManager().SetTimer(HUDTimer, TmpDelegate, AllTimersDeltaTime, true);
}

void USaveGameManager::LoadPlayerCharacter(USaveGameMT* InLoadingGame)
{
	FTimerDelegate TmpDelegate;
	FTimerHandle* TmpTimer = &(PlayerCharacterTimer);
	size_t* Count = &(CountOfLoadedElements);
	APlayerCharacterMagicTrigger* PlayerLoc = PlayerCharacter;
	UGameInstanceMagicTrigger* GameInstanceLoc = GameInstance;
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
			DEBUGMESSAGE("!PlayerCharacter");
		}
	}
	);
	GameInstance->GetWorld()->GetTimerManager().SetTimer(PlayerCharacterTimer, TmpDelegate, AllTimersDeltaTime, true);

}

void USaveGameManager::SavePlayerCharacter(USaveGameMT* InSavingGame)
{
	if (!PlayerCharacter)
	{
		DEBUGMESSAGE("!PlayerCharacter");
		return;
	}
	InSavingGame->PlayerLocation = PlayerCharacter->GetActorLocation();
	InSavingGame->ScreenShot = PlayerCharacter->CreateScreenShot();
}

void USaveGameManager::LoadPlayerState(USaveGameMT* InLoadingGame)
{
	FTimerDelegate TmpDelegate;
	FTimerHandle* TmpTimer = &(PlayerStateTimer);
	size_t* Count = &(CountOfLoadedElements);
	APlayerStateMagicTrigger* PlayerStateLoc = PlayerState;
	UGameInstanceMagicTrigger* GameInstanceLoc = GameInstance;
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
			DEBUGMESSAGE("!PlayerState");
		}
	}
	);
	GameInstance->GetWorld()->GetTimerManager().SetTimer(PlayerStateTimer, TmpDelegate, AllTimersDeltaTime, true);
}

void USaveGameManager::SavePlayerState(USaveGameMT* InSavingGame)
{
	if (!PlayerState)
	{
		DEBUGMESSAGE("!PlayerState");
		return;
	}
	InSavingGame->StatesStruct = PlayerState->GetStates();
}

void USaveGameManager::LoadGameSettings(UGameSettingsSaveGameMT* InLoadingGame)
{
	if (!GameInstance)
	{
		DEBUGMESSAGE("!GameInstance");
		return;
	}
	if (!InLoadingGame)
	{
		DEBUGMESSAGE("!InLoadingGame");
		return;
	}
	if (!GameInstance->GetWorld())
	{
		DEBUGMESSAGE("!GameInstance->GetWorld()");
		return;
	}
	FTimerDelegate TmpDelegate;
	FTimerHandle* TmpTimer = &(LoadSettingsTimer);
	//Нужен двойной указатель, т.к. в момент присваивания указатель еще невалиден, в лямбду передается его копия. Передать по ссылке не получится, т.к.
	//при переходе в лямбду произойдет выход из этой функции и все ее лок. переменные уничтожатся. 
	APlayerControllerMagicTrigger** PlayerControllerLoc = &(PlayerController);
	UGameInstanceMagicTrigger* GameInstanceLoc = GameInstance;
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
	GameInstance->GetWorld()->GetTimerManager().SetTimer(LoadSettingsTimer, TmpDelegate, AllTimersDeltaTime, true);
}


void USaveGameManager::SaveGameSettings(UGameSettingsSaveGameMT* InSavingGame)
{
	if (!PlayerController)
	{
		DEBUGMESSAGE("!PlayerController");
		return;
	}
	if (!InSavingGame)
	{
		DEBUGMESSAGE("!InSavingGame");
	}
	InSavingGame->MouseSensitivity = PlayerController->MouseSensitivity;

}

void USaveGameManager::ResetGameSettings()
{
	if (!GameInstance)
	{
		DEBUGMESSAGE("!GameInstance");
		return;
	}
	if (!GameInstance->GetWorld())
	{
		DEBUGMESSAGE("!GameInstance->GetWorld()");
		return;
	}
	FTimerDelegate TmpDelegate;
	FTimerHandle* TmpTimer = &(LoadSettingsTimer);
	APlayerControllerMagicTrigger** PlayerControllerLoc = &(PlayerController);
	UGameInstanceMagicTrigger* GameInstanceLoc = GameInstance;
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
	GameInstance->GetWorld()->GetTimerManager().SetTimer(LoadSettingsTimer, TmpDelegate, AllTimersDeltaTime, true);
}

void USaveGameManager::SaveLevelName(USaveGameMT* InSavingGame)
{
	InSavingGame->LevelName = GameInstance->GetNameOfCurrentLevel();
}
