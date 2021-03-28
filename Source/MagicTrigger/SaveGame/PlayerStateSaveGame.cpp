// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateSaveGame.h"

void UPlayerStateSaveGame::SetStates(FVector InPlayerLocation, UTextureRenderTarget2D* InScreenShot, FName InLevelName, FPlayerStateMagicTriggerStruct InStatesStruct)
{
	this->PlayerLocation = InPlayerLocation;
	this->ScreenShot = InScreenShot;
	this->LevelName = InLevelName;
	this->StatesStruct = InStatesStruct;
}

FPlayerStateMagicTriggerStruct UPlayerStateSaveGame::GetStates() const
{
	return this->StatesStruct;
}

FVector UPlayerStateSaveGame::GetPlayerLocation() const
{
	return this->PlayerLocation;
}
