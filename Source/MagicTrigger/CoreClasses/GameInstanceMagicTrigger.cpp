// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstanceMagicTrigger.h"
#include "Kismet/GameplayStatics.h"

#include "MagicTrigger\Data\DebugMessage.h"
#include "MagicTrigger\Data\PlayerStateMagicTriggerStruct.h"

#include "MagicTrigger\Interfaces\PlayerStateInterface.h"
#include "MagicTrigger\Interfaces\PlayerCharacterInterface.h"
#include "MagicTrigger\Interfaces\PlayerStateInterface.h"
#include "MagicTrigger\Interfaces\HUDInterface.h"

#include "MagicTrigger\SaveGame\ListOfSavedGames.h"
#include "MagicTrigger\SaveGame\PlayerStateSaveGame.h"

#include "GameFramework\PlayerController.h"
#include "GameFramework\Character.h"
#include "GameFramework\PlayerState.h"
#include "GameFramework\HUD.h"

class UTextureRenderTarget2D;

UGameInstanceMagicTrigger::UGameInstanceMagicTrigger()
{
	GamesListName = FString(TEXT("DefaultGamesListName170520191208"));
	GameSettingsStruct.MouseSensitivity = 1.1;
	SaveGameClass = UPlayerStateSaveGame::StaticClass();
}

bool UGameInstanceMagicTrigger::SaveCurrentGame(const FString& NameOfSaveGame)
{
	//////////////////////////////////////////////////////////////////////////Check
	ACharacter* PlayerCharacterTmp = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!PlayerCharacterTmp)
	{
		DEBUGMESSAGE("!PlayerCharacterTmp");
		return false;
	}
	APlayerState* PlayerStateTmp = PlayerCharacterTmp->GetPlayerState();
	if (!PlayerStateTmp)
	{
		DEBUGMESSAGE("!PlayerStateTmp");
		return false;
	}
	if (!IsInterfaceImplementedBy<IPlayerCharacterInterface>(PlayerCharacterTmp))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IPlayerCharacterInterface>(PlayerCharacterTmp)");
		return false;
	}
	if (!IsInterfaceImplementedBy<IPlayerStateInterface>(PlayerStateTmp))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IPlayerStateInterface>(PlayerStateTmp)");
		return false;
	}
	//////////////////////////////////////////////////////////////////////////

	if (UGameplayStatics::DoesSaveGameExist(NameOfSaveGame, 0))
	{
		DEBUGMESSAGE("UGameplayStatics::DoesSaveGameExist(). Игра с таким именем уже существует.");
		return false;
	}

	UPlayerStateSaveGame* SaveGameTmp = Cast<UPlayerStateSaveGame>(UGameplayStatics::CreateSaveGameObject(SaveGameClass));
	if (!SaveGameTmp)
	{
		DEBUGMESSAGE("!SaveGameTmp");
		return false;
	}
	FPlayerStateMagicTriggerStruct StatesTmp = IPlayerStateInterface::Execute_GetStates_IF(PlayerStateTmp);
	UTextureRenderTarget2D* ScreenShotTmp = IPlayerCharacterInterface::Execute_CreateScreenShot_IF(PlayerCharacterTmp);
	SaveGameTmp->SetStates(PlayerCharacterTmp->GetActorLocation(), ScreenShotTmp, GetNameOfCurrentLevel(), StatesTmp);
	bool bGameSaved = UGameplayStatics::SaveGameToSlot(SaveGameTmp, NameOfSaveGame, 0);

	return bGameSaved;
}

bool UGameInstanceMagicTrigger::SaveNameToGamesList(const FString& NameOfSaveGame)
{
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
		bool bGameSaved = UGameplayStatics::SaveGameToSlot(ListTmp, this->GamesListName, 0);
		return bGameSaved;
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
		bool bGameSaved = UGameplayStatics::SaveGameToSlot(ListTmp, this->GamesListName, 0);
		return bGameSaved;
	}

	return false;
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

	InSavedGamesNamesList = ListTmp->ListOfSavedGames;

	return true;
}

UPlayerStateSaveGame* UGameInstanceMagicTrigger::LoadGamesData(const FString& NameOfLoadGame)
{
	if (!UGameplayStatics::DoesSaveGameExist(NameOfLoadGame, 0))
	{
		DEBUGMESSAGE("!UGameplayStatics::DoesSaveGameExist(NameOfLoadGame, 0)");
		return nullptr;
	}
	USaveGame* SaveGameTmp = UGameplayStatics::LoadGameFromSlot(NameOfLoadGame, 0);
	UPlayerStateSaveGame* StatesTmp = Cast<UPlayerStateSaveGame>(SaveGameTmp);
	if (!StatesTmp)
	{
		DEBUGMESSAGE("!StatesTmp");
		return nullptr;
	}

	return StatesTmp;
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
	bool bDeleted = UGameplayStatics::DeleteGameInSlot(NameOfDeleteGame, 0);
	if (!bDeleted)
	{
		DEBUGMESSAGE("!bDeleted");
	}
	return bDeleted;
}

bool UGameInstanceMagicTrigger::DeleteNameFromGamesList(const FString& NameOfDeleteGame)
{
	if (!UGameplayStatics::DoesSaveGameExist(NameOfDeleteGame, 0))
	{
		DEBUGMESSAGE("!UGameplayStatics::DoesSaveGameExist(NameOfDeleteGame, 0)");
		return false;
	}
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

	return bSaved;
}

void UGameInstanceMagicTrigger::MainSaveGame(const FString& NameOfSaveGame)
{
	FString ReplacedName = ReplaceSpecSymbols(NameOfSaveGame);
	bool bSavedGame = SaveCurrentGame(NameOfSaveGame);
	if (!bSavedGame)
	{
		DEBUGMESSAGE("!bSavedGame");
		return;
	}
	bool bSavedGameName = SaveNameToGamesList(NameOfSaveGame);
	if (!bSavedGameName)
	{
		DEBUGMESSAGE("!bSavedGameName");
		return;
	}
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
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!PlayerCharacter)
	{
		DEBUGMESSAGE("!PlayerCharacter");
		return;
	}
	APlayerState* PlayerState = PlayerCharacter->GetPlayerState();
	if (!PlayerState)
	{
		DEBUGMESSAGE("!PlayerState");
		return;
	}
	if (!IsInterfaceImplementedBy<IHUDInterface>(HUD))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IHUDInterface>(HUD)");
		return;
	}
	if (!IsInterfaceImplementedBy<IPlayerStateInterface>(PlayerState))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IPlayerStateInterface>(PlayerState)");
		return;
	}
	//////////////////////////////////////////////////////////////////////////

	this->CurrentStateOfPlayersSaveGame = nullptr;
	this->CurrentStateOfPlayersSaveGame = LoadGamesData(NameOfLoadGame);
	if (!this->CurrentStateOfPlayersSaveGame)
	{
		DEBUGMESSAGE("!this->CurrentStateOfPlayersSaveGame");
		return;
	}

	IHUDInterface::Execute_HideLoadGameMenuWidget_IF(HUD);
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Level1")), true, FString());
	FPlayerStateMagicTriggerStruct States = this->CurrentStateOfPlayersSaveGame->GetStates();
	FVector PlayerLocation = this->CurrentStateOfPlayersSaveGame->GetPlayerLocation();
	IPlayerStateInterface::Execute_SetStates_IF(PlayerState, States);
	FHitResult OutSweepHitResult;
	PlayerCharacter->SetActorLocation(PlayerLocation, false, &OutSweepHitResult, ETeleportType::None);
	IHUDInterface::Execute_HideLoadingWidget_IF(HUD);
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
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!PlayerCharacter)
	{
		DEBUGMESSAGE("!PlayerCharacter");
		return;
	}
	APlayerState* PlayerState = PlayerCharacter->GetPlayerState();
	if (!PlayerState)
	{
		DEBUGMESSAGE("!PlayerState");
		return;
	}
	if (!IsInterfaceImplementedBy<IHUDInterface>(HUD))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IHUDInterface>(HUD)");
		return;
	}
	if (!IsInterfaceImplementedBy<IPlayerStateInterface>(PlayerState))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IPlayerStateInterface>(PlayerState)");
		return;
	}
	//////////////////////////////////////////////////////////////////////////

	IHUDInterface::Execute_HideMenuWidget_IF(HUD);
	UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Level1")), true, FString());
	FPlayerStateMagicTriggerStruct States = IPlayerStateInterface::Execute_GetBeginGameStates_IF(PlayerState);
	IPlayerStateInterface::Execute_SetStates_IF(PlayerState, States);
}

void UGameInstanceMagicTrigger::MainDeleteGame(const FString& NameOfDeleteGame)
{
	bool bGameDeleted = DeleteSaveGame(NameOfDeleteGame);
	if (!bGameDeleted)
	{
		DEBUGMESSAGE("!bGameDeleted");
		return;
	}
	bool bNameDeleted = DeleteNameFromGamesList(NameOfDeleteGame);
	if (!bNameDeleted)
	{
		DEBUGMESSAGE("!bNameDeleted");
		return;
	}
}

UPlayerStateSaveGame* UGameInstanceMagicTrigger::LoadGamesData_IF_Implementation(FString& NameOfLoadGame)
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

void UGameInstanceMagicTrigger::LoadGamesList_IF_Implementation(TArray<FString>& InGamesList)
{
	LoadGamesNamesList(InGamesList);
}

void UGameInstanceMagicTrigger::MainLoadGame_IF_Implementation(FString& InNameOfLoadGame)
{
	MainLoadGame(InNameOfLoadGame);
}

void UGameInstanceMagicTrigger::MainSaveGame_IF_Implementation(FString& InNameOfSaveGame)
{
	MainSaveGame(InNameOfSaveGame);
}

void UGameInstanceMagicTrigger::MainDeleteGame_IF_Implementation(FString& InNameOfDeleteGame)
{
	MainDeleteGame(InNameOfDeleteGame);
}

void UGameInstanceMagicTrigger::BeginNewGame_IF_Implementation()
{
	BeginNewGame();
}
