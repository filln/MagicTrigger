// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Контроллер врага.
 */

#pragma once

#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "MagicTrigger\Enemy\EnemyCharacterMagicTrigger.h"
#include "UObject/ConstructorHelpers.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception\AISenseConfig_Sight.h"
#include "Perception\AISenseConfig_Hearing.h"
 //#include "BrainComponent.h"
#include "BehaviorTree\BehaviorTree.h"
#include "BehaviorTree\BlackboardData.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavMesh\RecastNavMesh.h"
#include "MagicTrigger\Data\DebugMessage.h"

class UAISense_Sight;

AEnemyAIController::AEnemyAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	AISightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISightConfig"));
	AIHearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("AIHearingConfig"));

	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));


	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT("/Game/MagicTrigger/AI/Enemy/BT_Enemy"));
	if (BTObject.Succeeded())
	{
		BehaviorTreeAsset = BTObject.Object;
	}
	else
	{
		DEBUGMESSAGE("!BTObject.Succeeded()")
	}
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Game/MagicTrigger/AI/Enemy/BB_Enemy"));
	if (BBObject.Succeeded())
	{
		BlackboardAsset = BBObject.Object;
	}
	else
	{
		DEBUGMESSAGE("!BBObject.Succeeded()")
	}
	BBKeys = FBlackboardKeyNamesStruct();
	DeltaAttackRadius = 20;
	BeginPlayTimerTime = 0.2;

	ConfigureAIPerception();

}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		this->PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		UAIPerceptionSystem::RegisterPerceptionStimuliSource(GetWorld(), this->AISightConfig->GetSenseImplementation(), this->PlayerCharacter);
		UAIPerceptionSystem::RegisterPerceptionStimuliSource(GetWorld(), this->AIHearingConfig->GetSenseImplementation(), this->PlayerCharacter);
	}
	else
	{
		DEBUGMESSAGE("!GetWorld()")
	}
	this->Enemy = GetPawn<AEnemyCharacterMagicTrigger>();
	if (!this->Enemy)
	{
		DEBUGMESSAGE("!this->Enemy")
	}

	StopLogic();

	StartBeginPlayTimer_IF_Implementation();
}

void AEnemyAIController::StartLogic()
{
	if (GetWorld())
	{
		this->PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (!this->PlayerCharacter)
		{
			DEBUGMESSAGE("!this->PlayerCharacter");
			return;
		}
	}
	else
	{
		DEBUGMESSAGE("!GetWorld()");
		return;
	}

	this->AIPerceptionComponent->Activate();
	this->AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::TargetPerceptionUpdate);
	this->Enemy = GetPawn<AEnemyCharacterMagicTrigger>();
	if (!this->Enemy)
	{
		DEBUGMESSAGE("!this->Enemy");
		return;
	}

	//GetBrainComponent()->StartLogic();
	this->BehaviorTreeComponent->StartLogic();
}

void AEnemyAIController::StopLogic()
{
	this->AIPerceptionComponent->Deactivate();
	FString Reason;
	//GetBrainComponent()->StopLogic(Reason);
	this->BehaviorTreeComponent->StopLogic(Reason);
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//ConfigureAIPerception();

	bool bInitializeBB = this->BlackboardComponent->InitializeBlackboard(*this->BlackboardAsset);
	if (!bInitializeBB)
	{
		DEBUGMESSAGE("!bInitializeBB");
		return;
	}
	this->BehaviorTreeComponent->StartTree(*this->BehaviorTreeAsset);

}

void AEnemyAIController::FindPlayer()
{
	if (!this->Enemy)
	{
		DEBUGMESSAGE("!this->Enemy");
		return;
	}
	if (!this->BlackboardComponent)
	{
		DEBUGMESSAGE("!this->BlackboardComponent");
		return;
	}
	if (!this->PlayerCharacter)
	{
		DEBUGMESSAGE("!this->PlayerCharacter");
		return;
	}

	UObject* TargetPlayer = this->BlackboardComponent->GetValueAsObject(this->BBKeys.TargetPlayer);

	if (TargetPlayer)
	{
		return;
	}

	this->BlackboardComponent->SetValueAsObject(this->BBKeys.TargetPlayer, this->PlayerCharacter);
	StopMovement();
	this->BlackboardComponent->SetValueAsBool(this->BBKeys.bRoaring, true);

}

void AEnemyAIController::LosePlayer()
{
	if (!this->Enemy)
	{
		DEBUGMESSAGE("!this->Enemy");
		return;
	}
	if (!this->BlackboardComponent)
	{
		DEBUGMESSAGE("!this->BlackboardComponent");
		return;
	}
	if (!this->PlayerCharacter)
	{
		DEBUGMESSAGE("!this->PlayerCharacter");
		return;
	}

	this->Enemy->StopAttack();
	StopMovement();
	this->BlackboardComponent->ClearValue(this->BBKeys.bCanMoveToPlayer);
	this->BlackboardComponent->ClearValue(this->BBKeys.TargetPlayer);
	this->BlackboardComponent->ClearValue(this->BBKeys.bRoaring);
	this->Enemy->StopRoaring();

}

void AEnemyAIController::TargetPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus)
{
	if (!this->PlayerCharacter)
	{
		DEBUGMESSAGE("!this->PlayerCharacter");
		return;
	}

	if (Actor != this->PlayerCharacter)
	{
		return;
	}

	bool bFindPlayer = Stimulus.WasSuccessfullySensed();

	if (bFindPlayer)
	{
		FindPlayer();
	}
	else
	{
		LosePlayer();
	}

}


void AEnemyAIController::ConfigureAIPerception()
{
	this->AISightConfig->DetectionByAffiliation.bDetectEnemies = true;
	this->AISightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	this->AISightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	this->AIHearingConfig->HearingRange = 600;
	this->AIHearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	this->AIHearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	this->AIHearingConfig->DetectionByAffiliation.bDetectNeutrals = true;

	this->AIPerceptionComponent->ConfigureSense(*this->AISightConfig);
	this->AIPerceptionComponent->ConfigureSense(*this->AIHearingConfig);

	this->AIPerceptionComponent->SetDominantSense(this->AISightConfig->GetSenseImplementation());
}

ACharacter* AEnemyAIController::GetPlayerCharacter() const
{
	if (!this->PlayerCharacter)
	{
		DEBUGMESSAGE("!this->PlayerCharacter");
	}
	return this->PlayerCharacter;
}

AEnemyCharacterMagicTrigger* AEnemyAIController::GetEnemy() const
{
	if (!this->Enemy)
	{
		DEBUGMESSAGE("!this->Enemy");
	}
	return this->Enemy;
}

void AEnemyAIController::LosePlayer_IF_Implementation()
{
	LosePlayer();
}

/**
 * BeginPlayInterface
 */
 ///////////////////////////////////////////////////////////////////////////////////////
bool AEnemyAIController::CheckReferences_IF_Implementation()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARecastNavMesh::StaticClass(), this->NavMeshArray);
	if (
		!this->NavMeshArray.Num()
		|| !this->NavMeshArray[0]
		|| !Cast<ARecastNavMesh>(this->NavMeshArray[0])
		)
	{
		return false;
	}

	return true;
}

void AEnemyAIController::DoBeginPlay_IF_Implementation()
{
	this->NavMesh = Cast<ARecastNavMesh>(this->NavMeshArray[0]);
}

void AEnemyAIController::StartBeginPlayTimer_IF_Implementation()
{
	if (!GetWorld())
	{
		DEBUGMESSAGE("!GetWorld()");
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(this->BeginPlayTimer, this, &AEnemyAIController::BeforeBeginPlay_IF_Implementation, this->BeginPlayTimerTime, true);
}

void AEnemyAIController::BeforeBeginPlay_IF_Implementation()
{
	if (CheckReferences_IF_Implementation())
	{
		GetWorld()->GetTimerManager().ClearTimer(this->BeginPlayTimer);
		DoBeginPlay_IF_Implementation();
	}
}
////////////////////////////////////////////////////////////////////////////////////////








/**
 * // Fill out your copyright notice in the Description page of Project Settings.
#include "EnemyAIController.h"
#include "EnemyCharacter.h"
#include "BehaviorTree/BehaviorTree.h"


AEnemyAIController::AEnemyAIController()
{
	// Initialize components
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}

// Called when the controller possesses a Pawn/Character
void AEnemyAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	// Convert InPawn to EnemyCharacter
	auto Character = Cast<AEnemyCharacter>(InPawn);

	// Check if pointers are valid
	if(Character && Character->EnemyBehaviorTree)
	{
		BlackboardComp->InitializeBlackboard(*Character->EnemyBehaviorTree->BlackboardAsset);

		TargetKeyID = BlackboardComp->GetKeyID("Target");

		BehaviorComp->StartTree(*Character->EnemyBehaviorTree);
	}
}
 */