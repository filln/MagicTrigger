// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstanceMagicTrigger.h"
#include "Kismet/GameplayStatics.h"

#include "MagicTrigger\Data\DebugMessage.h"
#include "MagicTrigger\Interfaces\HUDInterface.h"
#include "MagicTrigger\SaveGame\ListOfSavedGames.h"
#include "MagicTrigger\SaveGame\SaveGameMT.h"
#include "MagicTrigger\SaveGame\GameSettingsSaveGameMT.h"
#include "MagicTrigger\SaveGame\SaveGameManager.h"
#include "MagicTrigger\UI\LoadingUserWidget.h"

#include "GameFramework\PlayerController.h"
#include "GameFramework\HUD.h"

UGameInstanceMagicTrigger::UGameInstanceMagicTrigger()
{
	GamesListName = FString(TEXT("DefaultGamesListName170520191208"));
	GameSettingsName = FString(TEXT("DefaultGameSettingsSaveName01042021"));
	GameSettingsStruct = FGameSettingsStruct();


	LoadingUserWidgetClass = ULoadingUserWidget::StaticClass();
}

void UGameInstanceMagicTrigger::Init()
{
	Super::Init();
	SaveGameManager = NewObject<USaveGameManager>(this, USaveGameManager::StaticClass(), FName(TEXT("SaveGameManager")));
	SaveGameManager->GameInstance = this;
	this->LoadingUserWidget = CreateWidget<ULoadingUserWidget>(this, LoadingUserWidgetClass, FName(TEXT("LoadingUserWidget")));
	//DEBUGMESSAGE("Init()");
}

void UGameInstanceMagicTrigger::Shutdown()
{
	SaveGameSettings();
	//DEBUGMESSAGE("Shutdown()");
	Super::Shutdown();
}

bool UGameInstanceMagicTrigger::SaveCurrentGame(const FString& NameOfSaveGame)
{
	if (UGameplayStatics::DoesSaveGameExist(NameOfSaveGame, 0))
	{
		DEBUGMESSAGE("UGameplayStatics::DoesSaveGameExist(). Игра с таким именем уже существует.");
		return false;
	}

	USaveGameMT* SaveGameTmp = Cast<USaveGameMT>(UGameplayStatics::CreateSaveGameObject(USaveGameMT::StaticClass()));
	if (!SaveGameTmp)
	{
		DEBUGMESSAGE("!SaveGameTmp");
		return false;
	}
	this->SaveGameManager->SaveAll(SaveGameTmp);

	bool bGameSaved = UGameplayStatics::SaveGameToSlot(SaveGameTmp, NameOfSaveGame, 0);

	return bGameSaved;
}

bool UGameInstanceMagicTrigger::SaveNameToGamesList(const FString& NameOfSaveGame, TArray<FString>& InGamesList)
{
	//DEBUGSTRING(NameOfSaveGame);
	bool bGameSaved;
	if (UGameplayStatics::DoesSaveGameExist(this->GamesListName, 0))
	{
		USaveGame* SaveGameTmp = UGameplayStatics::LoadGameFromSlot(this->GamesListName, 0);
		UListOfSavedGames* ListTmp = Cast<UListOfSavedGames>(SaveGameTmp);
		if (!ListTmp)
		{
			DEBUGMESSAGE("!ListTmp");
			return false;
		}
		ListTmp->ListOfSavedGames.Add(NameOfSaveGame);
		bGameSaved = UGameplayStatics::SaveGameToSlot(ListTmp, this->GamesListName, 0);
		if (bGameSaved)
		{
			InGamesList = ListTmp->ListOfSavedGames;
		}
	}
	else
	{
		UListOfSavedGames* ListTmp = Cast<UListOfSavedGames>(UGameplayStatics::CreateSaveGameObject(UListOfSavedGames::StaticClass()));
		if (!ListTmp)
		{
			DEBUGMESSAGE("!ListTmp");
			return false;
		}
		TArray<FString> NamesListTmp;
		NamesListTmp.Add(NameOfSaveGame);
		ListTmp->ListOfSavedGames = NamesListTmp;
		bGameSaved = UGameplayStatics::SaveGameToSlot(ListTmp, this->GamesListName, 0);
		if (bGameSaved)
		{
			InGamesList = NamesListTmp;
		}
	}

	return bGameSaved;
}


bool UGameInstanceMagicTrigger::LoadGamesNamesList(TArray<FString>& InSavedGamesNamesList)
{
	if (!UGameplayStatics::DoesSaveGameExist(this->GamesListName, 0))
	{
		DEBUGMESSAGE("!UGameplayStatics::DoesSaveGameExist(this->GamesListName, 0)");
		return false;
	}

	USaveGame* SaveGameTmp = UGameplayStatics::LoadGameFromSlot(this->GamesListName, 0);
	UListOfSavedGames* ListTmp = Cast<UListOfSavedGames>(SaveGameTmp);
	if (!ListTmp)
	{
		DEBUGMESSAGE("!ListTmp");
		return false;
	}
	if (!(ListTmp->ListOfSavedGames).Num())
	{
		DEBUGMESSAGE("!(ListTmp->ListOfSavedGames).Num()");
		return false;
	}
	InSavedGamesNamesList = ListTmp->ListOfSavedGames;

	return true;
}

USaveGameMT* UGameInstanceMagicTrigger::LoadGamesData(const FString& NameOfLoadGame)
{
	if (!UGameplayStatics::DoesSaveGameExist(NameOfLoadGame, 0))
	{
		DEBUGMESSAGE("!UGameplayStatics::DoesSaveGameExist(NameOfLoadGame, 0)");
		return nullptr;
	}
	USaveGame* SaveGameTmp = UGameplayStatics::LoadGameFromSlot(NameOfLoadGame, 0);
	USaveGameMT* SaveGameMTTmp = Cast<USaveGameMT>(SaveGameTmp);
	if (!SaveGameMTTmp)
	{
		DEBUGMESSAGE("!SaveGameMTTmp");
		return nullptr;
	}

	return SaveGameMTTmp;
}

FName UGameInstanceMagicTrigger::GetNameOfCurrentLevel()
{
	if (!GetWorld())
	{
		DEBUGMESSAGE("!GetWorld()");
		return FName();
	}
	FString LevelNameTmp = UGameplayStatics::GetCurrentLevelName(GetWorld(), true);
	return FName(*LevelNameTmp);
}

FString UGameInstanceMagicTrigger::ReplaceSpecSymbols(const FString& NameOfSaveGame)
{
	FString NameOfSaveGameTmp = NameOfSaveGame;
	NameOfSaveGameTmp.RemoveSpacesInline();
	FString SpecSymbols = FString(TEXT("!@#$%^&*()-=+\\|`'\"~<,.>/?№;:[]{}"));
	FString MainSymbol = FString(TEXT("_"));
	//////////////////////////////////////////////////////////////////////////
	//TArray<FString> UKismetStringLibrary::GetCharacterArrayFromString(const FString& SourceString)
	//TArray<FString> SeparatedSpecSymbols;
	//for (auto CharIt(SpecSymbols.CreateConstIterator()); CharIt; ++CharIt)
	//{
	//	TCHAR Char = *CharIt;
	//	SeparatedSpecSymbols.Add(FString(1, &Char));
	//}

	//// Remove the null terminator on the end
	//SeparatedSpecSymbols.RemoveAt(SeparatedSpecSymbols.Num() - 1, 1);
	//////////////////////////////////////////////////////////////////////////

	for (const auto& SpecSymbol : SpecSymbols)
	{
		NameOfSaveGameTmp.Replace(&SpecSymbol, *MainSymbol, ESearchCase::IgnoreCase);
	}

	return NameOfSaveGameTmp;
}

bool UGameInstanceMagicTrigger::DeleteSaveGame(const FString& NameOfDeleteGame)
{
	if (!UGameplayStatics::DoesSaveGameExist(NameOfDeleteGame, 0))
	{
		DEBUGMESSAGE("!UGameplayStatics::DoesSaveGameExist(NameOfDeleteGame, 0)");
		return false;
	}

	bool bDeleted = UGameplayStatics::DeleteGameInSlot(NameOfDeleteGame, 0);
	if (!bDeleted)
	{
		DEBUGMESSAGE("!bDeleted");
	}
	return bDeleted;
}

bool UGameInstanceMagicTrigger::DeleteNameFromGamesList(const FString& NameOfDeleteGame, TArray<FString>& InGamesList)
{
	USaveGame* SaveGameTmp = UGameplayStatics::LoadGameFromSlot(this->GamesListName, 0);
	UListOfSavedGames* ListTmp = Cast<UListOfSavedGames>(SaveGameTmp);
	if (!ListTmp)
	{
		DEBUGMESSAGE("!ListTmp");
		return false;
	}
	int32 bRemoved = ListTmp->ListOfSavedGames.RemoveSingle(NameOfDeleteGame);
	if (!bRemoved)
	{
		DEBUGMESSAGE("!bRemoved");
		return false;
	}

	bool bSaved = UGameplayStatics::SaveGameToSlot(ListTmp, this->GamesListName, 0);
	if (bSaved)
	{
		InGamesList = ListTmp->ListOfSavedGames;
	}

	return bSaved;
}

bool UGameInstanceMagicTrigger::MainSaveGame(const FString& NameOfSaveGame, TArray<FString>& InGamesList)
{
	FString ReplacedName = ReplaceSpecSymbols(NameOfSaveGame);//NameOfSaveGame;
	bool bSavedGame = SaveCurrentGame(ReplacedName);
	if (!bSavedGame)
	{
		DEBUGMESSAGE("!bSavedGame");
		return false;
	}
	bool bSavedGameName = SaveNameToGamesList(ReplacedName, InGamesList);
	if (!bSavedGameName)
	{
		DEBUGMESSAGE("!bSavedGameName");
		return false;
	}

	return true;
}

void UGameInstanceMagicTrigger::MainLoadGame(const FString& NameOfLoadGame)
{
	//////////////////////////////////////////////////////////////////////////Check
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController)
	{
		DEBUGMESSAGE("!PlayerController");
		return;
	}
	AHUD* HUD = PlayerController->GetHUD();
	if (!HUD)
	{
		DEBUGMESSAGE("!HUD");
		return;
	}
	if (!IsInterfaceImplementedBy<IHUDInterface>(HUD))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IHUDInterface>(HUD)");
		return;
	}
	//////////////////////////////////////////////////////////////////////////
	this->CurrentLoadingGame = LoadGamesData(NameOfLoadGame);
	if (!CurrentLoadingGame)
	{
		DEBUGMESSAGE("!CurrentLoadingGame");
		return;
	}

	IHUDInterface::Execute_HideLoadGameMenuWidget_IF(HUD);
	UGameplayStatics::OpenLevel(GetWorld(), this->CurrentLoadingGame->LevelName);
	FTimerHandle* TmpTimer = &(this->LoadingGameTimer);
	FTimerDelegate TmpDelegate;
	USaveGameManager* SaveGameManagerLoc = this->SaveGameManager;
	bool* bLevelLoadedRef = &(this->bLevelLoaded);
	USaveGameMT* LoadingGameTmp = this->CurrentLoadingGame;
	TmpDelegate.BindLambda
	(
		[=]
	()
	{
		if (*bLevelLoadedRef)
		{
			SaveGameManagerLoc->LoadAll(LoadingGameTmp);
			*bLevelLoadedRef = false;
			GetWorld()->GetTimerManager().ClearTimer(*TmpTimer);
		}
	}
	);
	GetWorld()->GetTimerManager().SetTimer(this->LoadingGameTimer, TmpDelegate, 0.1, true, 3);
}

void UGameInstanceMagicTrigger::BeginNewGame()
{
	//////////////////////////////////////////////////////////////////////////Check
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController)
	{
		DEBUGMESSAGE("!PlayerController");
		return;
	}
	AHUD* HUD = PlayerController->GetHUD();
	if (!HUD)
	{
		DEBUGMESSAGE("!HUD");
		return;
	}
	if (!IsInterfaceImplementedBy<IHUDInterface>(HUD))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IHUDInterface>(HUD)");
		return;
	}
	//////////////////////////////////////////////////////////////////////////

	IHUDInterface::Execute_HideMenuWidget_IF(HUD);
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Level1")));
	//FPlayerStateMagicTriggerStruct States = IPlayerStateInterface::Execute_GetBeginGameStates_IF(PlayerState);
	//IPlayerStateInterface::Execute_SetStates_IF(PlayerState, States);

	FTimerHandle* TmpTimer = &(this->BeginNewGameTimer);
	ULoadingUserWidget* LoadingUserWidgetTmp = this->LoadingUserWidget;
	FTimerDelegate TmpDelegate;
	bool* bLevelLoadedRef = &(this->bLevelLoaded);
	TmpDelegate.BindLambda
	(
		[=]
	()
	{
		if (*bLevelLoadedRef)
		{
			if (GetWorld())
			{
				APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
				if (PlayerController)
				{
					AHUD* HUD = PlayerController->GetHUD();
					if (HUD)
					{
						if (IsInterfaceImplementedBy<IHUDInterface>(HUD))
						{
							//DEBUGMESSAGE("IsInterfaceImplementedBy<IHUDInterface>(HUD)");
							if (LoadingUserWidgetTmp)
							{
								LoadingUserWidgetTmp->RemoveFromParent();
							}
							IHUDInterface::Execute_ShowPlayerGUIWidget_IF(HUD);
							IHUDInterface::Execute_SetInputMode_IF(HUD, EInputMode::EIM_GameOnly);

							*bLevelLoadedRef = false;
						}
						else
						{
							DEBUGMESSAGE("!IsInterfaceImplementedBy<IHUDInterface>(HUD)");
						}
					}
					else
					{
						DEBUGMESSAGE("!HUD");
					}
				}
				else
				{
					DEBUGMESSAGE("!PlayerController");
				}
			}
			else
			{
				DEBUGMESSAGE("!GetWorld()");
			}
			*bLevelLoadedRef = false;
			GetWorld()->GetTimerManager().ClearTimer(*TmpTimer);
		}
	}
	);

	GetWorld()->GetTimerManager().SetTimer(this->BeginNewGameTimer, TmpDelegate, 0.1, true, 3);
}

bool UGameInstanceMagicTrigger::MainDeleteGame(const FString& NameOfDeleteGame, TArray<FString>& InGamesList)
{
	bool bGameDeleted = DeleteSaveGame(NameOfDeleteGame);
	if (!bGameDeleted)
	{
		DEBUGMESSAGE("!bGameDeleted");
		return false;
	}
	bool bNameDeleted = DeleteNameFromGamesList(NameOfDeleteGame, InGamesList);
	if (!bNameDeleted)
	{
		DEBUGMESSAGE("!bNameDeleted");
		return false;
	}
	return true;
}

void UGameInstanceMagicTrigger::SaveGameSettings()
{
	if (UGameplayStatics::DoesSaveGameExist(this->GameSettingsName, 0))
	{
		bool bDeleted = UGameplayStatics::DeleteGameInSlot(this->GameSettingsName, 0);
		if (!bDeleted)
		{
			DEBUGMESSAGE("!bDeleted");
			return;
		}
	}

	UGameSettingsSaveGameMT* SaveGameTmp = Cast<UGameSettingsSaveGameMT>(UGameplayStatics::CreateSaveGameObject(UGameSettingsSaveGameMT::StaticClass()));
	if (!SaveGameTmp)
	{
		DEBUGMESSAGE("!SaveGameTmp");
		return;
	}
	this->SaveGameManager->SaveGameSettings(SaveGameTmp);
	bool bGameSaved = UGameplayStatics::SaveGameToSlot(SaveGameTmp, this->GameSettingsName, 0);

	if (!bGameSaved)
	{
		DEBUGMESSAGE("!bGameSaved");
	}

}

void UGameInstanceMagicTrigger::LoadGameSettings()
{
	if (!UGameplayStatics::DoesSaveGameExist(this->GameSettingsName, 0))
	{
		//DEBUGMESSAGE("!UGameplayStatics::DoesSaveGameExist(this->GameSettingsName, 0)");
		ResetGameSettings();
		return;
	}
	USaveGame* SaveGameTmp = UGameplayStatics::LoadGameFromSlot(this->GameSettingsName, 0);
	UGameSettingsSaveGameMT* SaveGameMTTmp = Cast<UGameSettingsSaveGameMT>(SaveGameTmp);
	if (!SaveGameMTTmp)
	{
		DEBUGMESSAGE("!SaveGameMTTmp");
		return;
	}
	if (!this->SaveGameManager)
	{
		DEBUGMESSAGE("!this->SaveGameManager");
		return;
	}
	this->SaveGameManager->LoadGameSettings(SaveGameMTTmp);

}

void UGameInstanceMagicTrigger::ResetGameSettings()
{
	this->SaveGameManager->ResetGameSettings();
}

USaveGameMT* UGameInstanceMagicTrigger::LoadGamesData_IF_Implementation(FString& NameOfLoadGame)
{
	return LoadGamesData(NameOfLoadGame);
}

FGameSettingsStruct UGameInstanceMagicTrigger::GetGameSettingsStruct_IF_Implementation() const
{
	return this->GameSettingsStruct;
}

void UGameInstanceMagicTrigger::SetGameSettingsStruct_IF_Implementation(FGameSettingsStruct InGameSettingsStruct)
{
	this->GameSettingsStruct = InGameSettingsStruct;
}

void UGameInstanceMagicTrigger::SetMouseSensitivity_IF_Implementation(float MouseSensitivity)
{
	this->GameSettingsStruct.MouseSensitivity = MouseSensitivity;
}

bool UGameInstanceMagicTrigger::LoadGamesList_IF_Implementation(TArray<FString>& InGamesList)
{
	return LoadGamesNamesList(InGamesList);
}

void UGameInstanceMagicTrigger::MainLoadGame_IF_Implementation(FString& InNameOfLoadGame)
{
	MainLoadGame(InNameOfLoadGame);
}

bool UGameInstanceMagicTrigger::MainSaveGame_IF_Implementation(FString& InNameOfSaveGame, TArray<FString>& InGamesList)
{
	return MainSaveGame(InNameOfSaveGame, InGamesList);
}

bool UGameInstanceMagicTrigger::MainDeleteGame_IF_Implementation(FString& InNameOfDeleteGame, TArray<FString>& InGamesList)
{
	return MainDeleteGame(InNameOfDeleteGame, InGamesList);
}

void UGameInstanceMagicTrigger::BeginNewGame_IF_Implementation()
{
	BeginNewGame();
}

void UGameInstanceMagicTrigger::SetLevelLoadedTrue_IF_Implementation()
{
	this->bLevelLoaded = true;
}

void UGameInstanceMagicTrigger::SaveGameSettings_IF_Implementation()
{
	SaveGameSettings();
}

void UGameInstanceMagicTrigger::ResetGameSettings_IF_Implementation()
{
	ResetGameSettings();
}

void UGameInstanceMagicTrigger::ShowGameMenu_IF_Implementation()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		DEBUGMESSAGE("!World");
	}

	FTimerDelegate TmpDelegate;
	FTimerHandle* TmpTimer = &(this->BeginNewGameTimer);
	TmpDelegate.BindLambda
	(
		[=]
	()
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
		if (PlayerController)
		{
			AHUD* HUD = PlayerController->GetHUD();
			if (IsInterfaceImplementedBy<IHUDInterface>(HUD))
			{
				if (IHUDInterface::Execute_CheckMenuUserWidget_IF(HUD))
				{
					IHUDInterface::Execute_ShowGameMenu_IF(HUD);
					GetWorld()->GetTimerManager().ClearTimer(*TmpTimer);
				}
			}
		}
	}
	);
	GetWorld()->GetTimerManager().SetTimer(this->BeginNewGameTimer, TmpDelegate, 0.1, true);
}

FString UGameInstanceMagicTrigger::GetGamesListName_IF_Implementation()
{
	return this->GamesListName;
}

void UGameInstanceMagicTrigger::ShowLoadingUserWidget_IF_Implementation()
{
	if (this->LoadingUserWidget)
	{
		this->LoadingUserWidget->AddToViewport(0);
	}
	else
	{
		DEBUGMESSAGE("!this->LoadingUserWidget");
	}
}
