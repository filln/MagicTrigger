// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MagicTrigger/Interfaces/PlayerControllerInterface.h"
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "PlayerControllerMagicTrigger")
		float MouseSensitivity;

	
	/**
	 * Methods
	 */
public:

	virtual void BeginPlay() override;

	/**
	 * Установка чувствительности мыши. 
	 */
	void SetMouseSensitivity(float InMouseSensitivity);
	float GetMouseSensitivity() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerControllerInterface")
		void SetMouseSensitivity_IF(float InMouseSensitivity);
	virtual void SetMouseSensitivity_IF_Implementation(float InMouseSensitivity) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerControllerInterface")
		float GetMouseSensitivity_IF();
	virtual float GetMouseSensitivity_IF_Implementation() override;
	void SetInputRotationScale(float InInputPitchScale, float InInputYawScale, float InInputRollScale);
};
