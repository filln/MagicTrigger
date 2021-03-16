// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Контроллер врага.
 */

#pragma once

#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"

#include "MagicTrigger\Enemy\EnemyCharacterMagicTrigger.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "MagicTrigger\Data\CollisionChannelsMagicTrigger.h"
#include "MagicTrigger\PlayerCharacter\PlayerCharacterMagicTrigger.h"

#include "UObject/ConstructorHelpers.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception\AISenseConfig_Sight.h"
#include "Perception\AISenseConfig_Hearing.h"
#include "Perception/AISense_Hearing.h"

#include "BehaviorTree\BehaviorTree.h"
#include "BehaviorTree\BlackboardData.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "NavMesh\RecastNavMesh.h"
#include "NavAreas\NavArea_Obstacle.h"
#include "Components\SphereComponent.h"

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

	SetPerceptionComponent(*AIPerceptionComponent);

	ConfigureAIPerception();

	//нужно биндить как можно раньше, т.к. OnTargetPerceptionUpdated.Broadcast() при нахождении перса в начале игры может произойти раньше бинда.
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::TargetPerceptionUpdate);

}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	StartBeginPlayTimer_IF_Implementation();
}

void AEnemyAIController::OnRunAI()
{

	//DEBUGMESSAGE("OnRunAI");
	GetPerceptionComponent()->Activate();
	this->BehaviorTreeComponent->StartLogic();
}

void AEnemyAIController::OnStopAI()
{
	//DEBUGMESSAGE("OnStopAI");
	GetPerceptionComponent()->Deactivate();
	FString Reason;
	this->BehaviorTreeComponent->StopLogic(Reason);
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	this->Enemy = GetPawn<AEnemyCharacterMagicTrigger>();

	this->AISightConfig->SightRadius = GetEnemy()->EnemyToBehaviorTreeStruct.SightRadius;
	this->AISightConfig->LoseSightRadius = GetEnemy()->EnemyToBehaviorTreeStruct.LoseSightRadius;
	this->AIHearingConfig->HearingRange = GetEnemy()->EnemyToBehaviorTreeStruct.HearingRange;

	bool bInitializeBB = this->BlackboardComponent->InitializeBlackboard(*this->BlackboardAsset);
	if (!bInitializeBB)
	{
		DEBUGMESSAGE("!bInitializeBB");
		return;
	}

	this->BehaviorTreeComponent->StartTree(*this->BehaviorTreeAsset);


	/////////////////////////////////////////////////////////
	/**
	 * Поиск перса и остановка логики, если перс не найден.
	 */
	TSubclassOf<ACharacter> ClassFilter;
	TArray<AActor*> OverlappingActors;
	bool bPlayerCharacterFound = false;


	this->Enemy->RunAISphere->GetOverlappingActors(OverlappingActors, ClassFilter);
	if (!OverlappingActors.Num())
	{
		//DEBUGMESSAGE("!OverlappingActors.Num()")
		OnStopAI();
	}
	else
	{
		for (const auto& OverlappingActor : OverlappingActors)
		{
			if (Cast<APlayerCharacterMagicTrigger>(OverlappingActor))
			{
				bPlayerCharacterFound = true;
				break;
			}
		}
		if (!bPlayerCharacterFound)
		{
			//DEBUGMESSAGE("!bPlayerCharacterFound")
			OnStopAI();
		}
	}
	/////////////////////////////////////////////////////////


}

void AEnemyAIController::FindPlayer(AActor* PlayerActor)
{
	if (!GetEnemy())
	{
		DEBUGMESSAGE("!GetEnemy()");
		return;
	}
	if (!this->BlackboardComponent)
	{
		DEBUGMESSAGE("!this->BlackboardComponent");
		return;
	}

	//DEBUGMESSAGE("FindPlayer");
	this->BlackboardComponent->SetValueAsObject(this->BBKeys.TargetPlayer, PlayerActor);
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
	//DEBUGMESSAGE("LosePlayer");
	this->Enemy->StopAttack();
	StopMovement();
	this->BlackboardComponent->ClearValue(this->BBKeys.bCanMoveToPlayer);
	this->BlackboardComponent->ClearValue(this->BBKeys.TargetPlayer);
	this->BlackboardComponent->ClearValue(this->BBKeys.bRoaring);

}


void AEnemyAIController::TargetPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus)
{
	//DEBUGMESSAGE("TargetPerceptionUpdate");
	//FString ActorName = Actor->GetName();
	//DEBUGSTRING(ActorName);

	//Не используем GetPlayerCharacter(), т.к. в начале игры может дать невалидную ссылку.
	if (!Cast<APlayerCharacterMagicTrigger>(Actor))
	{
		DEBUGMESSAGE("!Cast<APlayerCharacterMagicTrigger>(Actor)");
		return;
	}

	UObject* TargetPlayer = this->BlackboardComponent->GetValueAsObject(this->BBKeys.TargetPlayer);

	if (TargetPlayer)
	{
		//DEBUGMESSAGE("TargetPlayer");
		return;
	}

	bool bFindPlayer = Stimulus.WasSuccessfullySensed();
	//DEBUGMESSAGE("TargetPerceptionUpdate");
	if (bFindPlayer)
	{
		//DEBUGMESSAGE("bFindPlayer");
		FindPlayer(Actor);
	}

}


void AEnemyAIController::ConfigureAIPerception()
{
	this->AISightConfig->DetectionByAffiliation.bDetectEnemies = true;
	this->AISightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	this->AISightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	this->AIHearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	this->AIHearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	this->AIHearingConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->ConfigureSense(*this->AISightConfig);
	GetPerceptionComponent()->ConfigureSense(*this->AIHearingConfig);

	GetPerceptionComponent()->SetDominantSense(this->AISightConfig->GetSenseImplementation());
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
	ACharacter* PlayerCharacterTmp = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARecastNavMesh::StaticClass(), this->NavMeshArray);
	if (
		!this->NavMeshArray.Num()
		|| !this->NavMeshArray[0]
		|| !Cast<ARecastNavMesh>(this->NavMeshArray[0])
		|| !PlayerCharacterTmp
		)
	{
		return false;
	}

	return true;
}

void AEnemyAIController::DoBeginPlay_IF_Implementation()
{
	this->NavMesh = Cast<ARecastNavMesh>(this->NavMeshArray[0]);
	this->PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
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