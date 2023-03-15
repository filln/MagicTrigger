// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

/**
 * Содержит логику и данные для абилок. Абилки содержаться как актор-компоненты. Сам менеджер спавнится в классе перса.
 Для удобной настройки нужно выбрать бп-наследника менеджера в бп-классе перса.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagicTrigger/Data/AbilitySystem/CurrentAbilityEnum.h"
#include "MagicTrigger/Data/AbilitySystem/AvaliabilityAbilitiesStruct.h"
#include "AbilitySystemManager.generated.h"

class UMeleeAttackComponent;
class UThrowComponent;
class USevenfoldSphereComponent;
class APlayerCharacterMagicTrigger;
class AHUDMagicTrigger;
class UParentUserWidgetMT;
class USkeletalMeshComponent;
class URoundWaveComponent;

UCLASS()
class MAGICTRIGGER_API AAbilitySystemManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAbilitySystemManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * Variables
	 */
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilitySystemManager|Abilities")
		UMeleeAttackComponent* MeleeAttackComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilitySystemManager|Abilities")
		UThrowComponent* ThrowComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilitySystemManager|Abilities")
		USevenfoldSphereComponent* SevenfoldSphereComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilitySystemManager|Abilities")
		URoundWaveComponent* RoundWaveComponent;


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AbilitySystemManager")
		ECurrentAbility CurrentAbility;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AbilitySystemManager")
		FAvaliabilityAbilitiesStruct AvaliabilityAbilities;

	APlayerCharacterMagicTrigger* PlayerCharacter;
	AHUDMagicTrigger* HUD;

private:
	UParentUserWidgetMT* CurrentAbilityWidget;


	/**
	 * Methods
	 */
public:
	void Attack();
	void SetCurrentAbility(ECurrentAbility InCurrentAbility);
	APlayerCharacterMagicTrigger* GetPlayerCharacter() const;
	APlayerController* GetPlayerController() const;

	/**
	 * Melee
	 */
	void UseMeleeAbility();
	void StartTraceAttackLeftFoot();
	void StartTraceAttackRightFoot();
	void StopTraceAttackLeftFoot();
	void StopTraceAttackRightFoot();

	/**
	 * Throw
	 */
	void UseThrowAbility();
	void IncreaseCountOfThrowableItem();
	void SetCountOfThrowableItemText();
	void SpawnThrowableItem();
	void ThrowThrowableItem();
	FTransform GetSocketTransform(FName& SocketName) const;
	USkeletalMeshComponent* GetPlayerCharacterMesh() const;
	AActor* GetObservedActor() const;
	FVector GetPlayerCharacterForwardVector() const;
	FVector GetPlayerCharacterUpVector() const;
	FVector GetPlayerCharacterVelocity() const;

	/**
	 * SSphere
	 */
	void SwitchOnSSphereAbility();
	void UseSSphereAbility();
	void SpawnSSphere();
	void SetCountOfSpheresText();

	/**
	 * RoundWave
	 */
	void UseRoundWave();


};
