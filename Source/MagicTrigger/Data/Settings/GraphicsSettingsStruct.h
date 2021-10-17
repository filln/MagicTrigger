// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
* Для сохранения имен настроек графики.
*/

#pragma once
#include "AIController.h"

#include "GraphicsSettingsStruct.generated.h"

USTRUCT(BlueprintType)
struct FGraphicsSettingsStruct
{
	GENERATED_BODY()

	FString Low;
	FString Medium;
	FString High;
	FString Epic;
	FString Cinematic;
	FString DefaultLevel;

	FString Resolution800x600;
	FString Resolution1024x768;
	FString Resolution1152x864;
	FString Resolution1176x664;
	FString Resolution1280x720;
	FString Resolution1280x768;
	FString Resolution1280x960;
	FString Resolution1280x1024;
	FString Resolution1366x768;
	FString Resolution1440x900;
	FString Resolution1600x900;
	FString Resolution1600x1024;
	FString Resolution1680x1050;
	FString Resolution1768x992;
	FString Resolution1920x1080;
	FString DefaultResolution;

	FGraphicsSettingsStruct()
	{
		Low = FString(TEXT("Low"));
		Medium = FString(TEXT("Medium"));
		High = FString(TEXT("High"));
		Epic = FString(TEXT("Epic"));
		Cinematic = FString(TEXT("Cinematic"));
		DefaultLevel = Medium;

		Resolution800x600 = FString(TEXT("800x600"));
		Resolution1024x768 = FString(TEXT("1024x768"));
		Resolution1152x864 = FString(TEXT("1152x864"));
		Resolution1176x664 = FString(TEXT("1176x664"));
		Resolution1280x720 = FString(TEXT("1280x720"));
		Resolution1280x768 = FString(TEXT("1280x768"));
		Resolution1280x960 = FString(TEXT("1280x960"));
		Resolution1280x1024 = FString(TEXT("1280x1024"));
		Resolution1366x768 = FString(TEXT("1366x768"));
		Resolution1440x900 = FString(TEXT("1440x900"));
		Resolution1600x900 = FString(TEXT("1600x900"));
		Resolution1600x1024 = FString(TEXT("1600x1024"));
		Resolution1680x1050 = FString(TEXT("1680x1050"));
		Resolution1768x992 = FString(TEXT("1768x992"));
		Resolution1920x1080 = FString(TEXT("1920x1080"));
		DefaultResolution = Resolution1920x1080;
	}
};
