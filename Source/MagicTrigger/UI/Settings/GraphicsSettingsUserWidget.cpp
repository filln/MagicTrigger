// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "GraphicsSettingsUserWidget.h"
#include "MagicTrigger/CoreClasses/HUDMagicTrigger.h"
#include "MagicTrigger/UI/Settings/SettingsMenuUserWidget.h"
#include "Components/ComboBoxString.h"
#include "MagicTrigger/Data/DebugMessage.h"
#include "GameFramework/GameUserSettings.h"

UGraphicsSettingsUserWidget::UGraphicsSettingsUserWidget()
{
	GraphicsSettingsStruct = FGraphicsSettingsStruct();
	FillArraysFromGraphicSettingsStruct();
	bDisallowFillComboBoxes = false;
}

void UGraphicsSettingsUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	GameUserSettings = UGameUserSettings::GetGameUserSettings();
	if (!GameUserSettings)
	{
		DEBUGMESSAGE("!GameUserSettings");
	}
}

void UGraphicsSettingsUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UGraphicsSettingsUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	FillAllComboBox();
	LoadSettingsFromSavedToWidget();
	LevelComboBoxes =
	{
		ResolutionScaleComboBox,
		ViewDistanceComboBox,
		AntiAliasingComboBox,
		PostProcessingComboBox,
		ShadowsComboBox,
		TexturesComboBox,
		EffectsComboBox,
		FoliageComboBox,
		ShadingComboBox
	};
}

void UGraphicsSettingsUserWidget::OnPressedBackMenuButton()
{
	HUDMagicTrigger->SwitchWidgets(this, HUDMagicTrigger->SettingsMenuUserWidget);
}

void UGraphicsSettingsUserWidget::OnPressedResumeButton()
{
	HUDMagicTrigger->SetPauseGame(false, this);
}

void UGraphicsSettingsUserWidget::ApplyGraphicsSettings()
{
	SaveSettingsFromWidget();
	GameUserSettings->ApplySettings(true);
}

void UGraphicsSettingsUserWidget::ResetToDefaultGraphicsSettings()
{
	GameUserSettings->RunHardwareBenchmark();
	GameUserSettings->ApplyHardwareBenchmarkResults();
	LoadSettingsFromSavedToWidget();
}

void UGraphicsSettingsUserWidget::LoadLowGraphicsSettings()
{
	for (auto ComboBox : LevelComboBoxes)
	{
		ComboBox->SetSelectedOption(GraphicsSettingsStruct.Low);
	}
}

void UGraphicsSettingsUserWidget::LoadMediumGraphicsSettings()
{
	for (auto ComboBox : LevelComboBoxes)
	{
		ComboBox->SetSelectedOption(GraphicsSettingsStruct.Medium);
	}
}

void UGraphicsSettingsUserWidget::LoadHighGraphicsSettings()
{
	for (auto ComboBox : LevelComboBoxes)
	{
		ComboBox->SetSelectedOption(GraphicsSettingsStruct.High);
	}
}

void UGraphicsSettingsUserWidget::LoadEpicGraphicsSettings()
{
	for (auto ComboBox : LevelComboBoxes)
	{
		ComboBox->SetSelectedOption(GraphicsSettingsStruct.Epic);
	}
}

void UGraphicsSettingsUserWidget::LoadCinematicGraphicsSettings()
{
	for (auto ComboBox : LevelComboBoxes)
	{
		ComboBox->SetSelectedOption(GraphicsSettingsStruct.Cinematic);
	}
}

void UGraphicsSettingsUserWidget::FillAllComboBox()
{
	if (bDisallowFillComboBoxes)
	{
		return;
	}
	if (!ScreenResolutionComboBox)
	{
		DEBUGMESSAGE("!ScreenResolutionComboBox");
		return;
	}
	for (auto Resolution : ResolutionsArray)
	{
		ScreenResolutionComboBox->AddOption(*Resolution);
	}
	FillGraphicsLevelComboBox(ResolutionScaleComboBox);
	FillGraphicsLevelComboBox(ViewDistanceComboBox);
	FillGraphicsLevelComboBox(AntiAliasingComboBox);
	FillGraphicsLevelComboBox(PostProcessingComboBox);
	FillGraphicsLevelComboBox(ShadowsComboBox);
	FillGraphicsLevelComboBox(TexturesComboBox);
	FillGraphicsLevelComboBox(EffectsComboBox);
	FillGraphicsLevelComboBox(FoliageComboBox);
	FillGraphicsLevelComboBox(ShadingComboBox);

	bDisallowFillComboBoxes = true;
}

void UGraphicsSettingsUserWidget::FillGraphicsLevelComboBox(UComboBoxString* InComboBox)
{
	for (auto GraphicsLevel : GraphicsLevelsMap)
	{
		InComboBox->AddOption(GraphicsLevel.Key);
	}
}

void UGraphicsSettingsUserWidget::FillArraysFromGraphicSettingsStruct()
{
	GraphicsLevelsMap =
	{
		{GraphicsSettingsStruct.Low, 0},
		{GraphicsSettingsStruct.Medium, 1},
		{GraphicsSettingsStruct.High, 2},
		{GraphicsSettingsStruct.Epic, 3},
		{GraphicsSettingsStruct.Cinematic, 4}
	};
	ResolutionsArray =
	{
		&GraphicsSettingsStruct.Resolution800x600,
		&GraphicsSettingsStruct.Resolution1024x768,
		&GraphicsSettingsStruct.Resolution1152x864,
		&GraphicsSettingsStruct.Resolution1176x664,
		&GraphicsSettingsStruct.Resolution1280x720,
		&GraphicsSettingsStruct.Resolution1280x768,
		&GraphicsSettingsStruct.Resolution1280x960,
		&GraphicsSettingsStruct.Resolution1280x1024,
		&GraphicsSettingsStruct.Resolution1366x768,
		&GraphicsSettingsStruct.Resolution1440x900,
		&GraphicsSettingsStruct.Resolution1600x900,
		&GraphicsSettingsStruct.Resolution1600x1024,
		&GraphicsSettingsStruct.Resolution1680x1050,
		&GraphicsSettingsStruct.Resolution1768x992,
		&GraphicsSettingsStruct.Resolution1920x1080
	};
}

void UGraphicsSettingsUserWidget::LoadSettingsFromSavedToWidget()
{
	const FIntPoint ResolutionInt = GameUserSettings->GetScreenResolution();
	const FString ResolutionStr = ConvertFIntPointToResolutionString(ResolutionInt);
	ScreenResolutionComboBox->SetSelectedOption(ResolutionStr);
	const float ResScale = GameUserSettings->GetResolutionScaleNormalized();
	//DEBUGFLOAT(ResScale);
	if (ResScale > 0 && ResScale <= 0.21)
	{
		ResolutionScaleComboBox->SetSelectedOption(GraphicsSettingsStruct.Low);
	}
	else if (ResScale > 0.21 && ResScale <= 0.41)
	{
		ResolutionScaleComboBox->SetSelectedOption(GraphicsSettingsStruct.Medium);
	}
	else if (ResScale > 0.41 && ResScale <= 0.61)
	{
		ResolutionScaleComboBox->SetSelectedOption(GraphicsSettingsStruct.High);
	}
	else if (ResScale > 0.61 && ResScale <= 0.81)
	{
		ResolutionScaleComboBox->SetSelectedOption(GraphicsSettingsStruct.Epic);
	}
	else if (ResScale > 0.81 && ResScale <= 1.1)
	{
		ResolutionScaleComboBox->SetSelectedOption(GraphicsSettingsStruct.Cinematic);
	}
	else
	{
		DEBUGMESSAGE("No exists levels.");
		ResolutionScaleComboBox->SetSelectedOption(GraphicsSettingsStruct.Low);
	}

	LoadSettingsFromSavedToComboBoxesBasedOnSwitch(GameUserSettings->GetViewDistanceQuality(), ViewDistanceComboBox);
	LoadSettingsFromSavedToComboBoxesBasedOnSwitch(GameUserSettings->GetAntiAliasingQuality(), AntiAliasingComboBox);
	LoadSettingsFromSavedToComboBoxesBasedOnSwitch(GameUserSettings->GetPostProcessingQuality(), PostProcessingComboBox);
	LoadSettingsFromSavedToComboBoxesBasedOnSwitch(GameUserSettings->GetShadowQuality(), ShadowsComboBox);
	LoadSettingsFromSavedToComboBoxesBasedOnSwitch(GameUserSettings->GetTextureQuality(), TexturesComboBox);
	LoadSettingsFromSavedToComboBoxesBasedOnSwitch(GameUserSettings->GetVisualEffectQuality(), EffectsComboBox);
	LoadSettingsFromSavedToComboBoxesBasedOnSwitch(GameUserSettings->GetFoliageQuality(), FoliageComboBox);
	LoadSettingsFromSavedToComboBoxesBasedOnSwitch(GameUserSettings->GetShadingQuality(), ShadingComboBox);
}

void UGraphicsSettingsUserWidget::LoadSettingsFromSavedToComboBoxesBasedOnSwitch(int32 InLevel, UComboBoxString* InComboBox)
{
	switch (InLevel)
	{
	case 0:
		{
			InComboBox->SetSelectedOption(GraphicsSettingsStruct.Low);
			break;
		}
	case 1:
		{
			InComboBox->SetSelectedOption(GraphicsSettingsStruct.Medium);
			break;
		}
	case 2:
		{
			InComboBox->SetSelectedOption(GraphicsSettingsStruct.High);
			break;
		}
	case 3:
		{
			InComboBox->SetSelectedOption(GraphicsSettingsStruct.Epic);
			break;
		}
	case 4:
		{
			InComboBox->SetSelectedOption(GraphicsSettingsStruct.Cinematic);
			break;
		}
	default:
		{
			DEBUGMESSAGE("No exists graphics levels.")
			InComboBox->SetSelectedOption(GraphicsSettingsStruct.Low);
		}
	}
}

void UGraphicsSettingsUserWidget::SaveSettingsFromWidget()
{
	GameUserSettings->SetScreenResolution(ConvertResolutionStringToFIntPoint(ScreenResolutionComboBox->GetSelectedOption()));
	
	const int32 ResScaleInt = *(GraphicsLevelsMap.Find(ResolutionScaleComboBox->GetSelectedOption()));
	//DEBUGSTRING(FString::FromInt(ScaleLevelInt));
	float ResScaleFloat;
	switch (ResScaleInt)
	{
		case 0:
			{
				ResScaleFloat = 0.2;
				break;
			}
		case 1:
			{
				ResScaleFloat = 0.4;
				break;
			}
		case 2:
			{
				ResScaleFloat = 0.6;
				break;
			}
		case 3:
			{
				ResScaleFloat = 0.8;
				break;
			}
		case 4:
			{
				ResScaleFloat = 1;
				break;
			}
		default:
			{
				DEBUGMESSAGE("No exists levels.");
				ResScaleFloat = 0.2;
			}			
	}
	//DEBUGFLOAT(ResScaleFloat);
	GameUserSettings->SetResolutionScaleNormalized(ResScaleFloat);
	
	GameUserSettings->SetViewDistanceQuality(*(GraphicsLevelsMap.Find(ViewDistanceComboBox->GetSelectedOption())));
	GameUserSettings->SetAntiAliasingQuality(*(GraphicsLevelsMap.Find(AntiAliasingComboBox->GetSelectedOption())));
	GameUserSettings->SetPostProcessingQuality(*(GraphicsLevelsMap.Find(PostProcessingComboBox->GetSelectedOption())));
	GameUserSettings->SetShadowQuality(*(GraphicsLevelsMap.Find(ShadowsComboBox->GetSelectedOption())));
	GameUserSettings->SetTextureQuality(*(GraphicsLevelsMap.Find(TexturesComboBox->GetSelectedOption())));
	GameUserSettings->SetVisualEffectQuality(*(GraphicsLevelsMap.Find(EffectsComboBox->GetSelectedOption())));
	GameUserSettings->SetFoliageQuality(*(GraphicsLevelsMap.Find(FoliageComboBox->GetSelectedOption())));
	GameUserSettings->SetShadingQuality(*(GraphicsLevelsMap.Find(ShadingComboBox->GetSelectedOption())));
}

FIntPoint UGraphicsSettingsUserWidget::ConvertResolutionStringToFIntPoint(const FString InResolution)
{
	FIntPoint OutResolution;
	if (InResolution.Len() == 0)
	{
		DEBUGMESSAGE("InResolution.Len() == 0");
		OutResolution.X = 800;
		OutResolution.Y = 600;
		return OutResolution;
	}
	const int32 DelimiterPos = InResolution.Find(TEXT("x"));
	if (DelimiterPos == INDEX_NONE)
	{
		DEBUGMESSAGE("DelimiterPos == INDEX_NONE");
		OutResolution.X = 800;
		OutResolution.Y = 600;
		return OutResolution;
	}
	const FString XString = InResolution.Left(DelimiterPos);
	const FString YString = InResolution.Right(InResolution.Len() - DelimiterPos - 1);
	OutResolution.X = FCString::Atoi(*XString);
	OutResolution.Y = FCString::Atoi(*YString);
	// DEBUGSTRING(InResolution);
	// DEBUGSTRING(XString);
	// DEBUGSTRING(YString);
	return OutResolution;
}

FString UGraphicsSettingsUserWidget::ConvertFIntPointToResolutionString(const FIntPoint InResolution)
{
	FString OutResolution;
	if (InResolution.X < 800 || InResolution.Y < 600)
	{
		DEBUGMESSAGE("InResolution.X <= 800 || InResolution.Y <= 600");
		return FString(TEXT("800x600"));
	}
	const FString XString = FString::FromInt(InResolution.X);
	const FString YString = FString::FromInt(InResolution.Y);
	OutResolution.Append(XString).Append(TEXT("x")).Append(YString);
	return OutResolution;
}
