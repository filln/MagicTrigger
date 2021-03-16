// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Родительский класс врагов.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MagicTrigger\Data\EnemyToBehaviorTreeStruct.h"
#include "TargetSelectionPlugin\Public\TargetSelectionInterface.h"
#include "MagicTrigger\Interfaces\EnemyCharacterInterface.h"
#include "EnemyCharacterMagicTrigger.generated.h"

class UTexture2D;
class USphereComponent;

UCLASS()
class MAGICTRIGGER_API AEnemyCharacterMagicTrigger : public ACharacter,
	public ITargetSelectionInterface,
	public IEnemyCharacterInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacterMagicTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



	/**
	 * Variables
	 */
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyCharacterMagicTrigger|AnimationStates")
		bool bGetDamage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyCharacterMagicTrigger|AnimationStates")
		bool bAttack;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyCharacterMagicTrigger|AnimationStates")
		bool bObserved;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyCharacterMagicTrigger|AnimationStates")
		bool bDying;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyCharacterMagicTrigger|AnimationStates")
		bool bStunning;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyCharacterMagicTrigger|AnimationStates")
		bool bStunningAfterGetDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyCharacterMagicTrigger|Settings")
		FEnemyToBehaviorTreeStruct EnemyToBehaviorTreeStruct;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyCharacterMagicTrigger|Settings")
		FText Name;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyCharacterMagicTrigger|Settings")
		UTexture2D* Icon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyCharacterMagicTrigger|Settings")
		float MaxLife;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyCharacterMagicTrigger|Settings")
		float MaxDefence;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyCharacterMagicTrigger|Settings")
		float MaxDamage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyCharacterMagicTrigger|Settings")
		float LifeSpan;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "EnemyCharacterMagicTrigger")
		float Life;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "EnemyCharacterMagicTrigger")
		float Defence;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "EnemyCharacterMagicTrigger")
		float Damage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "EnemyCharacterMagicTrigger")
		TEnumAsByte<EMovementMode> InitialMovementMode;

	/**
	 *
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyCharacterMagicTrigger|Components")
		USphereComponent* RunAISphere;


	/**
	 * Methods
	 */
public:
	/**
	 *
	 */
	void StartAttack();
	/**
	 *
	 */
	void StopAttack();

	/**
	 *Запуск ИИ, когда перс оверлапится с коллизией RunAISphere.
	 */
	UFUNCTION()
		void OnRunAI(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	/**
	 * Остановка ИИ, когда перс вышел из коллизии RunAISphere.
	 */
	UFUNCTION()
		void OnStopAI(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/**
	 *
	 */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser);

	UFUNCTION(BlueprintCallable, Category = "EnemyCharacterMagicTrigger")
		void DoAfterEndAnimationTakeDamage();
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "EnemyCharacterMagicTrigger")
		void Stunning(bool bInStunning);
	/**
	*
	*/
	void Die();

public:
	/////////////////////////////////////////////////////////////////////
	/**
	 * Interface metods
	 */
	 /////////////////////////////////////////////////////////////////////
	  /**
	   * TargetSelectionInterface
	   */

	   /**
		*
		*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "TargetSelectionInterface")
		void IsObserved();
	virtual void IsObserved_Implementation() override;
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "TargetSelectionInterface")
		void IsNotObserved();
	virtual void IsNotObserved_Implementation() override;

	/////////////////////////////////////////////////////////////////
	/**
	* EnemyCharacterInterface
	*/

	/**
	 * Getters
	 */

	 /**
	  *
	  */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "EnemyCharacterInterface|Getters")
		AActor* GetEnemy_IF();
	virtual AActor* GetEnemy_IF_Implementation() override;
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "EnemyCharacterInterface|Getters")
		float GetLife_IF() const;
	virtual float GetLife_IF_Implementation() const override;
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "EnemyCharacterInterface|Getters")
		float GetMaxLife_IF() const;
	virtual float GetMaxLife_IF_Implementation() const override;
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "EnemyCharacterInterface|Getters")
		UTexture2D* GetIcon_IF() const;
	virtual UTexture2D* GetIcon_IF_Implementation() const override;
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "EnemyCharacterInterface|Getters")
		FText GetName_IF() const;
	virtual FText GetName_IF_Implementation() const override;
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "EnemyCharacterInterface|Getters")
		bool GetDying_IF() const;
	virtual bool GetDying_IF_Implementation() const override;



};
