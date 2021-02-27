// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Проиграть анимацию рычания, когда найден пес и заблокировать повторное выполнение в дереве.
 */


#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Engine/EngineTypes.h"
#include "TimerManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MagicTrigger\Data\AI\BlackboardKeyNamesStruct.h"
#include "BTTask_PlayRoaring.generated.h"

 /**
  *
  */
UCLASS()
class MAGICTRIGGER_API UBTTask_PlayRoaring : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()

		/**
		* Variables
		*/
private:

	UPROPERTY()
		UBehaviorTreeComponent* MyOwnerComp;
	UPROPERTY()
		USkeletalMeshComponent* CachedSkelMesh;
	UPROPERTY()
		FBlackboardKeyNamesStruct BBKeys;
	UPROPERTY()
		UAnimationAsset* AnimationToPlay;
	EAnimationMode::Type PreviousAnimationMode;
	FTimerDelegate TimerDelegate;
	FTimerHandle TimerHandle;

	/**
	 * Methods
	 */

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;


protected:
	void OnAnimationTimerDone();
	void CleanUp(UBehaviorTreeComponent& OwnerComp);

};
