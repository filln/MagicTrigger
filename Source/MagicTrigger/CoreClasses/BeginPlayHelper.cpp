// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Интерфейс для написания логики для BeginPlay. Задает метод, с помощью которого можно проверять ссылки на объекты, которые создаются в начале игры.
 * Это делается с помощью таймера (BeginPlayTimer). Дополнительно к таймеру нужно определить переменную периода таймера (BeginPlayTimerTime, можно 0,2 с).
 * Сначала в BeginPlay запускается StartBeginPlayTimer(). StartBeginPlayTimer() запускает BeginPlayTimer с выполнением функции BeforeBeginPlay(). В BeforeBeginPlay() выполняется CheckReferences().
 * Если CheckReferences() return false, то BeforeBeginPlay() return. Если CheckReferences() return true, то останавливается BeginPlayTimer и вызывается DoBeginPlay().
 * В CheckReferences() происходит получение ссылок и проверка их на валидность. CheckReferences() return true только если все ссылки валидны.
 */


#include "BeginPlayHelper.h"

bool ABeginPlayHelper::CheckReferences()
{
	return true;
}

void ABeginPlayHelper::DoBeginPlay()
{
}

void ABeginPlayHelper::AssignDispatchers()
{
}

void ABeginPlayHelper::StartBeginPlayTimer()
{
	if (!GetWorld())
	{
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(BeginPlayTimer, this, &ABeginPlayHelper::BeforeBeginPlay, BeginPlayTimerTime, true);
}

void ABeginPlayHelper::BeforeBeginPlay()
{
	if (CheckReferences())
	{
		GetWorld()->GetTimerManager().ClearTimer(BeginPlayTimer);
		DoBeginPlay();
	}
}
