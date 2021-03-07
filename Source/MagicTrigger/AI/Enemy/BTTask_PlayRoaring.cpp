// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Проиграть анимацию рычания, когда найден пес и заблокировать повторное выполнение в дереве.
 */


#pragma once


#include "BTTask_PlayRoaring.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MagicTrigger\AI\Enemy\EnemyAIController.h"
#include "MagicTrigger\Enemy\EnemyCharacterMagicTrigger.h"
#include "MagicTrigger\Data\DebugMessage.h"
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
	UBlackboardComponent* Blackboard = EnemyAIController->BlackboardComponent;
	if (!Enemy)
	{
		DEBUGMESSAGE("!Enemy");
		return EBTNodeResult::Failed;
	}
	if (!Blackboard)
	{
		DEBUGMESSAGE("!Blackboard");
		return EBTNodeResult::Failed;
	}

	this->MyOwnerComp = &OwnerComp;
	this->AnimationToPlay = Enemy->EnemyToBehaviorTreeStruct.AnimationRoaring;
	this->TimerHandle.Invalidate();

	if (!this->AnimationToPlay)
	{
		DEBUGMESSAGE("!this->AnimationToPlay");
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

	const float FinishDelay = this->AnimationToPlay->GetMaxCurrentTime();
	if (FinishDelay <= 0)
	{
		DEBUGMESSAGE("FinishDelay <= 0");
		return EBTNodeResult::Succeeded;
	}

	this->PreviousAnimationMode = SkelMesh->GetAnimationMode();
	this->CachedSkelMesh = SkelMesh;
	SkelMesh->PlayAnimation(this->AnimationToPlay, false);
	Blackboard->SetValueAsBool(this->BBKeys.bRoaring, false);
	MyController->GetWorld()->GetTimerManager().SetTimer(this->TimerHandle, this->TimerDelegate, FinishDelay, /*bLoop=*/false);
	return EBTNodeResult::InProgress;

}

EBTNodeResult::Type UBTTask_PlayRoaring::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* const MyController = OwnerComp.GetAIOwner();

	if (!this->AnimationToPlay)
	{
		DEBUGMESSAGE("!this->AnimationToPlay");
		return EBTNodeResult::Failed;
	}
	if (!MyController)
	{
		DEBUGMESSAGE("!MyController");
		return EBTNodeResult::Failed;
	}
	if (!this->TimerHandle.IsValid())
	{
		DEBUGMESSAGE("!this->TimerHandle.IsValid()");
		return EBTNodeResult::Failed;
	}

	MyController->GetWorld()->GetTimerManager().ClearTimer(this->TimerHandle);
	this->TimerHandle.Invalidate();

	CleanUp(OwnerComp);

	return EBTNodeResult::Aborted;
}

FString UBTTask_PlayRoaring::GetStaticDescription() const
{
	return FString::Printf(TEXT("%s: '%s'"), *Super::GetStaticDescription(), *GetNameSafe(this->AnimationToPlay));
}

void UBTTask_PlayRoaring::OnAnimationTimerDone()
{
	if (this->MyOwnerComp)
	{
		CleanUp(*this->MyOwnerComp);
		FinishLatentTask(*this->MyOwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		DEBUGMESSAGE("!this->MyOwnerComp");
	}
}

void UBTTask_PlayRoaring::CleanUp(UBehaviorTreeComponent& OwnerComp)
{
	if (!this->CachedSkelMesh)
	{
		DEBUGMESSAGE("!this->CachedSkelMesh");
		return;
	}
	if (this->PreviousAnimationMode == EAnimationMode::AnimationBlueprint)
	{
		this->CachedSkelMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	}
}

