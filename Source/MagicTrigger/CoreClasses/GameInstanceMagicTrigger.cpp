// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstanceMagicTrigger.h"
#include "Kismet/GameplayStatics.h"

#include "MagicTrigger/Data/DebugMessage.h"
#include "MagicTrigger/CoreClasses/HUDMagicTrigger.h"
#include "MagicTrigger/SaveGame/ListOfSavedGames.h"
#include "MagicTrigger/SaveGame/SaveGameMT.h"
#include "MagicTrigger/SaveGame/GameSettingsSaveGameMT.h"
#include "MagicTrigger/SaveGame/SaveGameManager.h"
#include "MagicTrigger/UI/SaveGame/LoadingUserWidget.h"

#include "GameFramework/PlayerController.h"
#include "GameFramework/HUD.h"

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
	LoadingUserWidget = CreateWidget<ULoadingUserWidget>(this, LoadingUserWidgetClass, FName(TEXT("LoadingUserWidget")));
	//LoadGameSettings();
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
	SaveGameManager->SaveAll(SaveGameTmp);

	bool bGameSaved = UGameplayStatics::SaveGameToSlot(SaveGameTmp, NameOfSaveGame, 0);

	return bGameSaved;
}

AHUDMagicTrigger* UGameInstanceMagicTrigger::SetAndGetHUDMT()
{
	if (!GetWorld())
	{
		DEBUGMESSAGE("!GetWorld()");
		return nullptr;
	}
	if (!PlayerController)
	{
		PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (!PlayerController)
		{
			DEBUGMESSAGE("!PlayerController");
			return nullptr;
		}
	}
	if (!HUD)
	{
		HUD = PlayerController->GetHUD();
		if (!HUD)
		{
			DEBUGMESSAGE("!HUD");
			return nullptr;
		}
	}
	if (!HUDMT)
	{
		HUDMT = Cast<AHUDMagicTrigger>(HUD);
		if (!HUDMT)
		{
			DEBUGMESSAGE("!HUDMT");
			return nullptr;
		}
	}
	return HUDMT;
}

bool UGameInstanceMagicTrigger::SaveNameToGamesList(const FString& NameOfSaveGame, TArray<FString>& InGamesList)
{
	//DEBUGSTRING(NameOfSaveGame);
	bool bGameSaved;
	if (UGameplayStatics::DoesSaveGameExist(GamesListName, 0))
	{
		USaveGame* SaveGameTmp = UGameplayStatics::LoadGameFromSlot(GamesListName, 0);
		UListOfSavedGames* ListTmp = Cast<UListOfSavedGames>(SaveGameTmp);
		if (!ListTmp)
		{
			DEBUGMESSAGE("!ListTmp");
			return false;
		}
		ListTmp->ListOfSavedGames.Add(NameOfSaveGame);
		bGameSaved = UGameplayStatics::SaveGameToSlot(ListTmp, GamesListName, 0);
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
		bGameSaved = UGameplayStatics::SaveGameToSlot(ListTmp, GamesListName, 0);
		if (bGameSaved)
		{
			InGamesList = NamesListTmp;
		}
	}

	return bGameSaved;
}


bool UGameInstanceMagicTrigger::LoadGamesNamesList(TArray<FString>& InSavedGamesNamesList)
{
	if (!UGameplayStatics::DoesSaveGameExist(GamesListName, 0))
	{
		DEBUGMESSAGE("!UGameplayStatics::DoesSaveGameExist(GamesListName, 0)");
		return false;
	}

	USaveGame* SaveGameTmp = UGameplayStatics::LoadGameFromSlot(GamesListName, 0);
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
	USaveGame* SaveGameTmp = UGameplayStatics::LoadGameFromSlot(GamesListName, 0);
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

	bool bSaved = UGameplayStatics::SaveGameToSlot(ListTmp, GamesListName, 0);
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
	if (!SetAndGetHUDMT())
	{
		return;
	}
	CurrentLoadingGame = LoadGamesData(NameOfLoadGame);
	if (!CurrentLoadingGame)
	{
		DEBUGMESSAGE("!CurrentLoadingGame");
		return;
	}

	HUDMT->HideLoadGameMenuWidget();
	UGameplayStatics::OpenLevel(GetWorld(), CurrentLoadingGame->LevelSaveGameStruct.LevelName);
	FTimerHandle* TmpTimer = &(LoadingGameTimer);
	FTimerDelegate TmpDelegate;
	USaveGameManager* SaveGameManagerLoc = SaveGameManager;
	bool* bLevelLoadedRef = &(bLevelLoaded);
	USaveGameMT* LoadingGameTmp = CurrentLoadingGame;
	TmpDelegate.BindLambda
	(
		[=]
	()
	{
		//Вначале проверяется, загрузился ли уровень, и если уровень загрузился, то загружаются данные из объекта сохраненной ранее игры.
		if (*bLevelLoadedRef)
		{
			SaveGameManagerLoc->LoadAll(LoadingGameTmp);
			*bLevelLoadedRef = false;
			GetWorld()->GetTimerManager().ClearTimer(*TmpTimer);
		}
	}
	);
	GetWorld()->GetTimerManager().SetTimer(LoadingGameTimer, TmpDelegate, 0.1, true, 3);
}

void UGameInstanceMagicTrigger::BeginNewGame()
{
	if (!SetAndGetHUDMT())
	{
		return;
	}
	HUDMT->HideMenuWidget();
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Level1")));
	FTimerHandle* TmpTimer = &(BeginNewGameTimer);
	ULoadingUserWidget* LoadingUserWidgetTmp = LoadingUserWidget;
	FTimerDelegate TmpDelegate;
	bool* bLevelLoadedRef = &(bLevelLoaded);
	TmpDelegate.BindLambda
	(
		[=]
	()
	{
		//Вначале проверяется, загрузился ли уровень, и если уровень загрузился, то продолжать.
		if (*bLevelLoadedRef)
		{
			if (!SetAndGetHUDMT())
			{
				return;
			}
			if (LoadingUserWidgetTmp)
			{
				LoadingUserWidgetTmp->RemoveFromParent();
			}
			HUDMT->CreatePlayerGUIUserWidget(PlayerController);
			HUDMT->ShowPlayerGUIWidget();			
			PlayerController->bShowMouseCursor = false;
			FInputModeGameOnly InputModeDataGame;
			PlayerController->SetInputMode(InputModeDataGame);
			*bLevelLoadedRef = false;
			GetWorld()->GetTimerManager().ClearTimer(*TmpTimer);
		}
	}
	);

	GetWorld()->GetTimerManager().SetTimer(BeginNewGameTimer, TmpDelegate, 0.1, true, 3);
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
	if (UGameplayStatics::DoesSaveGameExist(GameSettingsName, 0))
	{
		bool bDeleted = UGameplayStatics::DeleteGameInSlot(GameSettingsName, 0);
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
	SaveGameManager->SaveGameSettings(SaveGameTmp);
	bool bGameSaved = UGameplayStatics::SaveGameToSlot(SaveGameTmp, GameSettingsName, 0);

	if (!bGameSaved)
	{
		DEBUGMESSAGE("!bGameSaved");
	}

}

void UGameInstanceMagicTrigger::LoadGameSettings()
{
	if (!UGameplayStatics::DoesSaveGameExist(GameSettingsName, 0))
	{
		//DEBUGMESSAGE("!UGameplayStatics::DoesSaveGameExist(GameSettingsName, 0)");
		ResetGameSettings();
		return;
	}
	USaveGame* SaveGameTmp = UGameplayStatics::LoadGameFromSlot(GameSettingsName, 0);
	UGameSettingsSaveGameMT* SaveGameMTTmp = Cast<UGameSettingsSaveGameMT>(SaveGameTmp);
	if (!SaveGameMTTmp)
	{
		DEBUGMESSAGE("!SaveGameMTTmp");
		return;
	}
	if (!SaveGameManager)
	{
		DEBUGMESSAGE("!SaveGameManager");
		return;
	}
	SaveGameManager->LoadGameSettings(SaveGameMTTmp);

}

void UGameInstanceMagicTrigger::ResetGameSettings()
{
	SaveGameManager->ResetGameSettings();
}

USaveGameMT* UGameInstanceMagicTrigger::LoadGamesData_IF_Implementation(FString& NameOfLoadGame)
{
	return LoadGamesData(NameOfLoadGame);
}

FGameSettingsStruct UGameInstanceMagicTrigger::GetGameSettingsStruct_IF_Implementation() const
{
	return GameSettingsStruct;
}

void UGameInstanceMagicTrigger::SetGameSettingsStruct_IF_Implementation(FGameSettingsStruct InGameSettingsStruct)
{
	GameSettingsStruct = InGameSettingsStruct;
}

void UGameInstanceMagicTrigger::SetMouseSensitivity_IF_Implementation(float MouseSensitivity)
{
	GameSettingsStruct.MouseSensitivity = MouseSensitivity;
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
	bLevelLoaded = true;
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
	FTimerDelegate TmpDelegate;
	FTimerHandle* TmpTimer = &(BeginNewGameTimer);
	TmpDelegate.BindLambda
	(
		[=]
	()
	{
		if (SetAndGetHUDMT())
		{
			if (HUDMT->CheckMenuUserWidget())
			{
				HUDMT->ShowGameMenu();
				GetWorld()->GetTimerManager().ClearTimer(*TmpTimer);
			}
		}
	}
	);
	GetWorld()->GetTimerManager().SetTimer(BeginNewGameTimer, TmpDelegate, 0.1, true);
}

FString UGameInstanceMagicTrigger::GetGamesListName_IF_Implementation()
{
	return GamesListName;
}

void UGameInstanceMagicTrigger::ShowLoadingUserWidget_IF_Implementation()
{
	if (LoadingUserWidget)
	{
		LoadingUserWidget->AddToViewport(0);
	}
	else
	{
		DEBUGMESSAGE("!LoadingUserWidget");
	}
}
