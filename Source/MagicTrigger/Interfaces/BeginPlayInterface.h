// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Интерфейс для написания логики для BeginPlay. Задает метод, с помощью которого можно проверять ссылки на объекты, которые создаются в начале игры. 
 * Это делается с помощью таймера (BeginPlayTimer), который нужно создать в классе. Дополнительно к таймеру нужно создать переменную периода таймера (BeginPlayTimerTime, можно 0,2 с).
 * Сначала в BeginPlay запускается StartBeginPlayTimer_IF(). StartBeginPlayTimer_IF() запускает BeginPlayTimer с выполнением функции BeforeBeginPlay_IF(). В BeforeBeginPlay_IF() выполняется CheckReferences_IF(). 
 * Если CheckReferences_IF() return false, то BeforeBeginPlay_IF() return. Если CheckReferences_IF() return true, то останавливается BeginPlayTimer и вызывается DoBeginPlay_IF().
 * В CheckReferences_IF() происходит получение ссылок и проверка их на валидность. CheckReferences_IF() return true только если все ссылки валидны.
 */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BeginPlayInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable, Category = "BeginPlayInterface")
class UBeginPlayInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MAGICTRIGGER_API IBeginPlayInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	//Проверить валидность ссылок, нужных для работы DoBeginPlay.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BeginPlayInterface")
		bool CheckReferences_IF();
	//Выполнить логику для BeginPlay.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BeginPlayInterface")
		void DoBeginPlay_IF();
	//Определить диспатчеры. Вызывается в DoBeginPlay.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BeginPlayInterface")
		void AssignDispatchers_IF();
	//Запустить BeginPlayTimer.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BeginPlayInterface")
		void StartBeginPlayTimer_IF();
	//Выполняется в таймере для получения нужных ссылок.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BeginPlayInterface")
		void BeforeBeginPlay_IF();
};
