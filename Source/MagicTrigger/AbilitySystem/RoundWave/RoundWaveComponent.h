// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.
/**
	Абилка "волна" вокруг перса
*/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RoundWaveComponent.generated.h"

class AAbilitySystemManager;
class ARoundWave;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MAGICTRIGGER_API URoundWaveComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URoundWaveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	/**
	 * Variables
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RoundWaveComponent")
		FVector SpawnScale;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RoundWaveComponent")
		float IncreaseScaleTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RoundWaveComponent")
		float DecreaseScaleTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RoundWaveComponent")
		float MaxScaleMultiplier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "RoundWaveComponent")
		TSubclassOf<ARoundWave> RoundWaveClass;
	UPROPERTY()
		FTimerHandle ScaleTimer;
private:
	AAbilitySystemManager* AbilitySystemManager;
	ARoundWave* RoundWave;
	float ScaleTimerDeltaTime;
	float CurrentScaleMultiplier;
	float DeltaScaleMultiplier;
	/**
	 * Methods
	 */
public:
	/**
	 * Использовать абилку. Начинает цепочку действий до начала анимации.
	 */
	void Use();
	/*
		Скастовать абилку. Вызывается через цепочку функций от определенного момента анимации.
	*/
	void CastRoundWave();
	/**
	 * Закончить абилку.
	 */
	void EndRoundWave();

private:
	/**
	 * Плавно увеличивает размер актора волны.
	 */
	void IncreaseScale();
	/**
	 * Плавно уменьшает размер актора волны до нуля и удаляет его.
	 */
	void DecreaseScale();

};
