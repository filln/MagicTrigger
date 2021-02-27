// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Контроллер врага.
 */

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MagicTrigger\Interfaces\EnemyCharacterInterface.h"
#include "MagicTrigger\Interfaces\BeginPlayInterface.h"
#include "AIModule\Classes\Perception\AIPerceptionTypes.h"
#include "MagicTrigger\Data\AI\BlackboardKeyNamesStruct.h"
#include "EnemyAIController.generated.h"

class ACharacter;
class AEnemyCharacterMagicTrigger;
class UAIPerceptionComponent;
class UBehaviorTree;
class UBlackboardData;
class UBehaviorTreeComponent;
class UBlackboardComponent;
class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;
class APawn;
class ARecastNavMesh;

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API AEnemyAIController : public AAIController, public IEnemyCharacterInterface, public IBeginPlayInterface
{
	GENERATED_BODY()

public:

	AEnemyAIController();

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	/**
	 * Variables
	 */
public:

	/**
	*
	*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "EnemyAIController")
		FBlackboardKeyNamesStruct BBKeys;
	/**
	*
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyAIController")
		UBehaviorTree* BehaviorTreeAsset;
	/**
	*
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyAIController")
		UBlackboardData* BlackboardAsset;
	/**
	* Чтобы убрать погрешность расстояния приближения к персу. Вычитаемое для EnemyToBehaviorTreeStruct.AttackRadius, результат вводится в AcceptanceRadius для MoveToActor().
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyAIController")
		float DeltaAttackRadius;
	/**
	 *
	 */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "EnemyAIController|Components")
		UAIPerceptionComponent* AIPerceptionComponent;

	/**
	 *
	 */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "EnemyAIController|Components")
		UBehaviorTreeComponent* BehaviorTreeComponent;
	/**
	 *
	 */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "EnemyAIController|Components")
		UBlackboardComponent* BlackboardComponent;

	/**
	 *
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnemyAIController")
		ARecastNavMesh* NavMesh;

private:

	UPROPERTY()
		ACharacter* PlayerCharacter;
	UPROPERTY()
		AEnemyCharacterMagicTrigger* Enemy;
	UPROPERTY()
		UAISenseConfig_Sight* AISightConfig;
	UPROPERTY()
		UAISenseConfig_Hearing* AIHearingConfig;
	UPROPERTY()
		FTimerHandle BeginPlayTimer;
	float BeginPlayTimerTime;
	UPROPERTY()
	TArray<AActor*> NavMeshArray;


	/**
	 * Methods
	 */

public:
	/**
	 *
	 */
	UFUNCTION()
		void TargetPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus);
	/**
	 *
	 */
	void FindPlayer();
	/**
	 *
	 */
	void LosePlayer();
	/**
	 *
	 */
	void StartLogic();
	/**
	 *
	 */
	void StopLogic();

private:

	/**
	 *
	 */
	void ConfigureAIPerception();

public:

	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "EnemyAIController")
		ACharacter* GetPlayerCharacter() const;
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable, Category = "EnemyAIController")
		AEnemyCharacterMagicTrigger* GetEnemy() const;

public:
	/**
	 *  InterfaceMethods
	 */

	 /**
	  * EnemyCharacterInterface
	  */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "EnemyCharacterInterface")
		void LosePlayer_IF();
	virtual void LosePlayer_IF_Implementation() override;

	/**
	 * BeginPlayInterface
	 */
	 //Проверить валидность ссылок, нужных для работы DoBeginPlay.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BeginPlayInterface")
		bool CheckReferences_IF();
	virtual bool CheckReferences_IF_Implementation() override;
	//Выполнить логику для BeginPlay.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BeginPlayInterface")
		void DoBeginPlay_IF();
	virtual void DoBeginPlay_IF_Implementation() override;
	//Запустить BeginPlayTimer.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BeginPlayInterface")
		void StartBeginPlayTimer_IF();
	virtual void StartBeginPlayTimer_IF_Implementation() override;
	//Выполняется в таймере для получения нужных ссылок.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "BeginPlayInterface")
		void BeforeBeginPlay_IF();
	virtual void BeforeBeginPlay_IF_Implementation() override;


};

/**
 * // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.generated.h"


UCLASS()
class CHAPTER_10_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

private:
	// AI Component references
	UBehaviorTreeComponent* BehaviorComp;
	UBlackboardComponent* BlackboardComp;

public:
	AEnemyAIController();

	// Called when the controller possesses a Pawn/Character
	virtual void Possess(APawn* InPawn) override;

	FBlackboard::FKey TargetKeyID;

};
 */