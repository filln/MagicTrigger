// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "SaveGameManager.h"

#include "ImageUtils.h"
#include "MagicTrigger/CoreClasses/HUDMagicTrigger.h"
#include "MagicTrigger/CoreClasses/GameInstanceMagicTrigger.h"
#include "MagicTrigger/CoreClasses/PlayerStateMagicTrigger.h"
#include "MagicTrigger/CoreClasses/PlayerControllerMagicTrigger.h"
#include "MagicTrigger/SaveGame/SaveGameMT.h"
#include "MagicTrigger/SaveGame/GameSettingsSaveGameMT.h"
#include "MagicTrigger/Data/DebugMessage.h"
#include "MagicTrigger/PlayerCharacter/PlayerCharacterMagicTrigger.h"
#include "MagicTrigger/UI/SaveGame/LoadingUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/BufferArchive.h"
#include "Engine/TextureRenderTarget2D.h"

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
			HUDLoc->SetInputMode(EInputMode::EIM_GameOnly, nullptr);
			GameInstanceLoc->GetWorld()->GetTimerManager().ClearTimer(*TmpTimer);			
		}
	}
	);
	GameInstance->GetWorld()->GetTimerManager().SetTimer(LoadAllTimer, TmpDelegate, AllTimersDeltaTime, true);

	CheckHUD();
	LoadPlayerCharacter(InLoadingGame);
	LoadPlayerState(InLoadingGame);

}

void USaveGameManager::SaveAll(USaveGameMT* InSavingGame, const FString& InNameOfSavingGame)
{
	SavePlayerCharacter(InSavingGame);
	SavePlayerState(InSavingGame);
	SaveLevelData(InSavingGame, InNameOfSavingGame);
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
			FVector Location = FVector(InLoadingGame->PlayerCharacterSaveGameStruct.Location.X, InLoadingGame->PlayerCharacterSaveGameStruct.Location.Y, InLoadingGame->PlayerCharacterSaveGameStruct.Location.Z + 40);
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
	InSavingGame->PlayerCharacterSaveGameStruct.Location = PlayerCharacter->GetActorLocation();

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
			(*PlayerControllerLoc)->SetMouseSensitivity(InLoadingGame->MouseSensitivity);
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
			(*PlayerControllerLoc)->SetMouseSensitivity(GameInstanceLoc->GameSettingsStruct.MouseSensitivity);
			GameInstanceLoc->GetWorld()->GetTimerManager().ClearTimer(*TmpTimer);
		}
	}
	);
	GameInstance->GetWorld()->GetTimerManager().SetTimer(LoadSettingsTimer, TmpDelegate, AllTimersDeltaTime, true);
}

void USaveGameManager::SaveLevelData(USaveGameMT* InSavingGame, const FString& InNameOfSavingGame)
{
	InSavingGame->LevelSaveGameStruct.LevelName = GameInstance->GetNameOfCurrentLevel();
	InSavingGame->LevelSaveGameStruct.NameOfSavedGame = InNameOfSavingGame;
	ScreenshotTextureTarget = CreateScreenShot();
	SaveScreenshot(ScreenshotTextureTarget, InNameOfSavingGame);
}

FString USaveGameManager::GeneratePathToScreenshot(const FString& InNameOfSavingGame)
{
	return FPaths::ProjectSavedDir() + TEXT("SaveGames/") + InNameOfSavingGame + TEXT(".exr");
	//FPaths::ProjectSavedDir() - в c:\Users\YourName\AppData\Local\YourUE4Project\Saved\SaveGames\
	//FPaths::ProjectDir() - в папке с игрой.
	//FPaths::GameContentDir()
}

UTexture2D* USaveGameManager::LoadScreenshot(const FString& InNameOfSavedGame)
{
	const FString PathToScreenshot = GeneratePathToScreenshot(InNameOfSavedGame);
	if (!FPaths::FileExists(PathToScreenshot))
	{
		DEBUGMESSAGE("!FPaths::FileExists(SaveFile)");
		return nullptr;
	}
	return FImageUtils::ImportFileAsTexture2D(PathToScreenshot);
}

void USaveGameManager::SaveScreenshot(UTextureRenderTarget2D* InTextureRenderTarget, const FString& InNameOfSavingGame)
{
	const FString PathToScreenshot = GeneratePathToScreenshot(InNameOfSavingGame);
////////////////////////////////////////////////////////////////////////////////////
	FText PathError;
	FPaths::ValidatePath(PathToScreenshot, &PathError);

	if (!InTextureRenderTarget)
	{
		//InTextureRenderTarget must be non-null
		DEBUGMESSAGE("!InTextureRenderTarget");
		return;
	}
	if (!InTextureRenderTarget->Resource)
	{
		//render target has been released
		DEBUGMESSAGE("!InTextureRenderTarget->Resource");
		return;
	}
	if (!PathError.IsEmpty())
	{
		//Invalid file path provided
		DEBUGMESSAGE("!PathError.IsEmpty()");
		return;
	}
	if (InNameOfSavingGame.IsEmpty())
	{
		//FileName must be non-empty
		DEBUGMESSAGE("InNameOfSavingGame.IsEmpty()");
		return;
	}
	//////////////////////////////////////////////////////////////////////////////
	// const FImageWriteOptions ImageWriteOptions = FImageWriteOptions();
	// UImageWriteBlueprintLibrary::ExportToDisk(InTextureRenderTarget, PathToScreenshot, ImageWriteOptions);
	
	FArchive* Ar = IFileManager::Get().CreateFileWriter(*PathToScreenshot);
	
	if(!Ar)
	{
		//FileWrite failed to create
		DEBUGMESSAGE("!Ar");
		return;
	}
	FBufferArchive Buffer;
	const bool bSuccess = FImageUtils::ExportRenderTarget2DAsEXR(InTextureRenderTarget, Buffer);
	 if (!Buffer.Num())
	 {
	 	DEBUGMESSAGE("!Buffer.Num()");
	 }
	if (bSuccess)
	{
		Ar->Serialize(const_cast<uint8*>(Buffer.GetData()), Buffer.Num());
	}
	else
	{
		DEBUGMESSAGE("!bSuccess");
	}
	
	delete Ar;
	/**
	 *
	*I think ExportRenderTarget2DAsPNG is exporting only HDR pictures whih means only EXR format.
	You can use this which makes the write operation async and gives more feedback on what texture
	format matches what export type: UImageWriteBlueprintLibrary::ExportToDisk | Unreal Engine Documentation

	To verify but I think Export PNG is only possible with this format ETextureRenderTargetFormat::RTF_RGBA16f,
	which means having the render target capturing FinalColor_LDR, other ones will need to be exported in EXR.
	Or if you need some specific format in PNG you need to convert it manually.
	 */
}

void USaveGameManager::DeleteSavedScreenshot(const FString& InSavedGameName)
{
	const FString PathToScreenshot = GeneratePathToScreenshot(InSavedGameName);
	IFileManager::Get().Delete(*PathToScreenshot, true, false, true);
}

UTextureRenderTarget2D* USaveGameManager::CreateScreenShot() const
{
	return PlayerCharacter->CreateScreenShot();
}
