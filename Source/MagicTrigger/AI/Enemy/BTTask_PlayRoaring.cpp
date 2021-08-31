// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Проиграть анимацию рычания, когда найден пес и заблокировать повторное выполнение в дереве.
 */


#pragma once


#include "BTTask_PlayRoaring.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MagicTrigger/AI/Enemy/EnemyAIController.h"
#include "MagicTrigger/Enemy/EnemyCharacterMagicTrigger.h"
#include "MagicTrigger/Data/DebugMessage.h"
#include "GameFramework/Character.h"

UBTTask_PlayRoaring::UBTTask_PlayRoaring(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Play Roaring Animation";
	bCreateNodeInstance = true;
	TimerDelegate = FTimerDelegate::CreateUObject(this, &UBTTask_PlayRoaring::OnAnimationTimerDone);
	PreviousAnimationMode = EAnimationMode::AnimationBlueprint;
}

EBTNodeResult::Type UBTTask_PlayRoaring::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* const MyController = OwnerComp.GetAIOwner();
	if (!MyController)
	{
		DEBUGMESSAGE("!MyController");
		return EBTNodeResult::Failed;
	}
	AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(MyController);
	if (!EnemyAIController)
	{
		DEBUGMESSAGE("!EnemyAIController");
		return EBTNodeResult::Failed;
	}
	AEnemyCharacterMagicTrigger* Enemy = EnemyAIController->GetEnemy();
	if (!Enemy)
	{
		DEBUGMESSAGE("!Enemy");
		return EBTNodeResult::Failed;
	}

	MyOwnerComp = &OwnerComp;
	AnimationToPlay = Enemy->EnemyToBehaviorTreeStruct.AnimationRoaring;
	TimerHandle.Invalidate();

	if (!AnimationToPlay)
	{
		DEBUGMESSAGE("!AnimationToPlay");
		return EBTNodeResult::Failed;
	}
	if (!MyController->GetPawn())
	{
		DEBUGMESSAGE("!MyController->GetPawn()");
		return EBTNodeResult::Failed;
	}
	USkeletalMeshComponent* SkelMesh = nullptr;
	ACharacter* const MyCharacter = Cast<ACharacter>(MyController->GetPawn());
	if (MyCharacter)
	{
		SkelMesh = MyCharacter->GetMesh();
	}
	else
	{
		SkelMesh = MyController->GetPawn()->FindComponentByClass<USkeletalMeshComponent>();
	}
	if (!SkelMesh)
	{
		DEBUGMESSAGE("!SkelMesh");
		return EBTNodeResult::Failed;
	}

	const float FinishDelay = Enemy->EnemyToBehaviorTreeStruct.WaitTimeOfAnimationRoaring;
	if (FinishDelay <= 0)
	{
		DEBUGMESSAGE("FinishDelay <= 0");
		return EBTNodeResult::Succeeded;
	}

	PreviousAnimationMode = SkelMesh->GetAnimationMode();
	CachedSkelMesh = SkelMesh;
	SkelMesh->PlayAnimation(AnimationToPlay, false);
	MyController->GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, FinishDelay, /*bLoop=*/false);
	return EBTNodeResult::InProgress;

}

EBTNodeResult::Type UBTTask_PlayRoaring::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* const MyController = OwnerComp.GetAIOwner();

	if (!AnimationToPlay)
	{
		DEBUGMESSAGE("!AnimationToPlay");
		return EBTNodeResult::Failed;
	}
	if (!MyController)
	{
		DEBUGMESSAGE("!MyController");
		return EBTNodeResult::Failed;
	}
	if (!TimerHandle.IsValid())
	{
		DEBUGMESSAGE("!TimerHandle.IsValid()");
		return EBTNodeResult::Failed;
	}

	MyController->GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	TimerHandle.Invalidate();

	CleanUp(OwnerComp);

	return EBTNodeResult::Aborted;
}

FString UBTTask_PlayRoaring::GetStaticDescription() const
{
	return FString::Printf(TEXT("%s: '%s'"), *Super::GetStaticDescription(), *GetNameSafe(AnimationToPlay));
}

void UBTTask_PlayRoaring::OnAnimationTimerDone()
{
	if (MyOwnerComp)
	{

		AAIController* const MyController = MyOwnerComp->GetAIOwner();
		if (!MyController)
		{
			DEBUGMESSAGE("!MyController");
			return;
		}
		AEnemyAIController* EnemyAIController = Cast<AEnemyAIController>(MyController);
		if (!EnemyAIController)
		{
			DEBUGMESSAGE("!EnemyAIController");
			return;
		}

		UBlackboardComponent* Blackboard = EnemyAIController->BlackboardComponent;
		if (!Blackboard)
		{
			DEBUGMESSAGE("!Blackboard");
			return;
		}
		CleanUp(*MyOwnerComp);
		FinishLatentTask(*MyOwnerComp, EBTNodeResult::Succeeded);
		Blackboard->SetValueAsBool(BBKeys.bRoaring, false);

	}
	else
	{
		DEBUGMESSAGE("!MyOwnerComp");
	}
}

void UBTTask_PlayRoaring::CleanUp(UBehaviorTreeComponent& OwnerComp)
{
	if (!CachedSkelMesh)
	{
		DEBUGMESSAGE("!CachedSkelMesh");
		return;
	}
	if (PreviousAnimationMode == EAnimationMode::AnimationBlueprint)
	{
		CachedSkelMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	}
}

