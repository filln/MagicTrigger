// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Персонаж игры.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MagicTrigger/Interfaces/AnimationManagerInterface.h"
#include "PlayerCharacterMagicTrigger.generated.h"

class UActorComponent;

UCLASS()
class MAGICTRIGGER_API APlayerCharacterMagicTrigger : public ACharacter, public IAnimationManagerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacterMagicTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	/**
* AnimationManagerInterface methods.
*/
/**
 * Getters
 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerCharacter|AnimationManagerInterface|Getters")
		UActorComponent* GetAnimationManagerComponent_IF() const;
	virtual UActorComponent* GetAnimationManagerComponent_IF_Implementation() const override;

};
