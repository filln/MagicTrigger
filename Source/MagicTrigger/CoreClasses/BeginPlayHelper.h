// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Интерфейс для написания логики для BeginPlay. Задает метод, с помощью которого можно проверять ссылки на объекты, которые создаются в начале игры.
 * Это делается с помощью таймера (BeginPlayTimer). Дополнительно к таймеру нужно определить переменную периода таймера (BeginPlayTimerTime, можно 0,2 с).
 * Сначала в BeginPlay запускается StartBeginPlayTimer(). StartBeginPlayTimer() запускает BeginPlayTimer с выполнением функции BeforeBeginPlay(). В BeforeBeginPlay() выполняется CheckReferences().
 * Если CheckReferences() return false, то BeforeBeginPlay() return. Если CheckReferences() return true, то останавливается BeginPlayTimer и вызывается DoBeginPlay().
 * В CheckReferences() происходит получение ссылок и проверка их на валидность. CheckReferences() return true только если все ссылки валидны.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BeginPlayHelper.generated.h"

UCLASS()
class MAGICTRIGGER_API ABeginPlayHelper : public AActor
{
	GENERATED_BODY()
	

public:	

	FTimerHandle BeginPlayTimer;
	float BeginPlayTimerTime;

	//Проверить валидность ссылок, нужных для работы DoBeginPlay.
		bool CheckReferences();
	//Выполнить логику для BeginPlay.
		void DoBeginPlay();
	//Определить диспатчеры. Вызывается в DoBeginPlay.
		void AssignDispatchers();
	//Запустить BeginPlayTimer.
		void StartBeginPlayTimer();
	//Выполняется в таймере для получения нужных ссылок.
		void BeforeBeginPlay();

};
