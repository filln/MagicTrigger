// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Характеристики перса
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MagicTrigger/Interfaces/PlayerStateInterface.h"
#include "PlayerStateMagicTrigger.generated.h"

/**
 * 
 */
UCLASS()
class MAGICTRIGGER_API APlayerStateMagicTrigger : public APlayerState, public IPlayerStateInterface
{
	GENERATED_BODY()
	
public:
	APlayerStateMagicTrigger();
	
protected:
	virtual void BeginPlay() override;

   /**
	* Variables
	*/
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStateMagicTrigger")
	float Life;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStateMagicTrigger")
	float Defence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStateMagicTrigger")
	float Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStateMagicTrigger")
	float MaxLife;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStateMagicTrigger")
	float MaxDefence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStateMagicTrigger")
	float MaxDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStateMagicTrigger")
	float MultiplierOfDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerStateMagicTrigger")
	FPlayerStateSaveGameStruct BeginGameStates;
	
	
	/**
	 * Methods
	 */
public:
	FPlayerStateSaveGameStruct GetStates() const;
	void SetStates(FPlayerStateSaveGameStruct InStates);

	/**
	 * PlayerStateInterface Methods
	 */
public:
	/**
	 * Getters
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Getters")
		float GetLife_IF() const;
	virtual float GetLife_IF_Implementation() const override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Getters")
		float GetMaxLife_IF() const;
	virtual float GetMaxLife_IF_Implementation() const override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Getters")
		float GetDefence_IF() const;
	virtual float GetDefence_IF_Implementation() const override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Getters")
		float GetDamage_IF() const;
	virtual float GetDamage_IF_Implementation() const override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Getters")
		float GetMaxDefence_IF() const;
	virtual float GetMaxDefence_IF_Implementation() const override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Getters")
		float GetMaxDamage_IF() const;
	virtual float GetMaxDamage_IF_Implementation() const override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Getters")
		float GetMultiplierOfDamage_IF() const;
	virtual float GetMultiplierOfDamage_IF_Implementation() const override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Getters")
		FPlayerStateSaveGameStruct GetBeginGameStates_IF() const;
	virtual FPlayerStateSaveGameStruct GetBeginGameStates_IF_Implementation() const override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Getters")
		FPlayerStateSaveGameStruct GetStates_IF() const;
	virtual FPlayerStateSaveGameStruct GetStates_IF_Implementation() const override;
	/**
	 * Setters
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Setters")
		void SetLife_IF(float InLife);
	virtual void SetLife_IF_Implementation(float InLife) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Setters")
		void SetMaxLife_IF(float InMaxLife);
	virtual void SetMaxLife_IF_Implementation(float InMaxLife) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Setters")
		void SetDefence_IF(float InDefence);
	virtual void SetDefence_IF_Implementation(float InDefence) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Setters")
		void SetDamage_IF(float InDamage);
	virtual void SetDamage_IF_Implementation(float InDamage) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Setters")
		void SetMaxDefence_IF(float InMaxDefence);
	virtual void SetMaxDefence_IF_Implementation(float InMaxDefence) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Setters")
		void SetMaxDamage_IF(float InMaxDamage);
	virtual void SetMaxDamage_IF_Implementation(float InMaxDamage) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Setters")
		void SetMultiplierOfDamage_IF(float InMultiplierOfDamage);
	virtual void SetMultiplierOfDamage_IF_Implementation(float InMultiplierOfDamage) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Setters")
		void SetBeginGameStates_IF(FPlayerStateSaveGameStruct InBeginGameStates);
	virtual void SetBeginGameStates_IF_Implementation(FPlayerStateSaveGameStruct InBeginGameStates) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerStateInterface|Setters")
		void SetStates_IF(FPlayerStateSaveGameStruct InStates);
	virtual void SetStates_IF_Implementation(FPlayerStateSaveGameStruct InStates) override;


	


};
