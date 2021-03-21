// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MagicTrigger\Interfaces\PlayerControllerInterface.h"
#include "PlayerControllerMagicTrigger.generated.h"

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API APlayerControllerMagicTrigger : public APlayerController, public IPlayerControllerInterface
{
	GENERATED_BODY()

public:

	APlayerControllerMagicTrigger();

	/**
	 * Variables
	 */
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerControllerMagicTrigger")
		float InitialInputYawScale;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerControllerMagicTrigger")
		float InitialInputPitchScale;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerControllerMagicTrigger")
		float InitialInputRollScale;

	/**
	 * Methods
	 */
public:

	virtual void BeginPlay() override;

	/**
	 * Установка чувствительности мыши. Множитель на входе нужен для согласования чувствительности с положением слайдера в ControlWidget.
	 Также для установки максимума чувствительности. Слагаемое на входе - для установки минимальной чувствительности при нулевом положении слайдера.
	 */
	void SetInputRotationScale(float MouseSensBaseValue, float MouseSensMultiplier, float MouseSensAddend);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerControllerInterface")
		void SetInputRotationScale_IF(float mouseSensBaseValue, float mouseSensMultiplier, float mouseSensAddend);
	virtual void SetInputRotationScale_IF_Implementation(float mouseSensBaseValue, float mouseSensMultiplier, float mouseSensAddend) override;
};
