// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Компонент атакующей абилки фаербола.
 */

#pragma once

#include "FireBallComponent.h"
#include "MagicTrigger\AbilitySystem\FireBall\FireBall.h"
#include "MagicTrigger\Data\DebugMessage.h"

// Sets default values for this component's properties
UFireBallComponent::UFireBallComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	FireBallStruct = FFireBallStruct();
	DamageTypeClass = nullptr;
	OwnersAttachSocket = FName(TEXT("FireBallSocket"));
	ScaleAndEmissiveTimerTime = 0.02;
	DeltaMultiplierOfScaleEveryTick = 0;
	DeltaMultiplierOfEmissiveEveryTick = 0;
	CountOfTimerStepsInHands = 0;
	TextureParameterName = FName(TEXT("Texture"));
	EmissiveColorParameterName = FName(TEXT("EmissiveColor"));
	EmissiveMultiplierParameterName = FName(TEXT("EmissiveMultiplier"));

}


// Called when the game starts
void UFireBallComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	if (!Owner)
	{
		DEBUGMESSAGE("!Owner");
	}
	else
	{
		FireBallMoveToTargetInputsStruct.Owner = Owner;
	}
	
	CountOfTimerStepsInHands = CalcCountOfStepsInHands();
}


void UFireBallComponent::CreateFireBall(USkeletalMeshComponent* InOwnersMesh)
{
	if (!InOwnersMesh)
	{
		DEBUGMESSAGE("!InOwnersMesh");
		return;
	}
	if (!GetWorld())
	{
		DEBUGMESSAGE("!GetWorld()");
		return;
	}

	OwnersMesh = InOwnersMesh;

	if (FireBallInHands)
	{
		bool bDestroyed = FireBallInHands->Destroy();
		if (!bDestroyed)
		{
			DEBUGMESSAGE("!bDestroyed");
			return;
		}
		FireBallInHands = nullptr;
	}

	FTransform SocketTransform = OwnersMesh->GetSocketTransform(OwnersAttachSocket);
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketTransform.GetLocation());
	SpawnTransform.SetRotation(SocketTransform.GetRotation());
	SpawnTransform.SetScale3D(FVector(1));
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FireBallInHands = GetWorld()->SpawnActor<AFireBall>(AFireBall::StaticClass(), SpawnTransform, ActorSpawnParameters);
	if (!FireBallInHands)
	{
		DEBUGMESSAGE("!FireBallInHands");
		return;
	}

	FireBallInHandsMaterial = CreateMaterialFireBall(FireBallInHands);
	if (!FireBallInHandsMaterial)
	{
		DEBUGMESSAGE("!FireBallInHandsMaterial");
		return;
	}
	FireBallInHands->SetActorEnableCollision(false);
	FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, true);
	FireBallInHands->AttachToComponent(OwnersMesh, AttachmentRules, OwnersAttachSocket);
	FireBallInHands->SaveInitialScale();

	DeltaMultiplierOfScaleEveryTick = CalcDeltaEveryTick(FireBallStruct.MaxMultiplierOfScaleInOwnersHand, FireBallInHands->CurrentMultiplierOfScale, CountOfTimerStepsInHands);
	DeltaMultiplierOfEmissiveEveryTick = CalcDeltaEveryTick(FireBallStruct.MaxEmissiveMultiplierInOwnersHand, FireBallInHands->CurrentMultiplierOfEmissive, CountOfTimerStepsInHands);

	GetWorld()->GetTimerManager().ClearTimer(ScaleAndEmissiveTimer);
	GetWorld()->GetTimerManager().SetTimer(ScaleAndEmissiveTimer, this, &UFireBallComponent::ScaleAndEmissive, ScaleAndEmissiveTimerTime, true);

}

void UFireBallComponent::MoveFireBallToTarget(AController* OwnersController, AActor* BallsTarget)
{
	if (!OwnersController)
	{
		DEBUGMESSAGE("!OwnersController");
		return;
	}
	if (!Owner)
	{
		DEBUGMESSAGE("!Owner");
		return;
	}
	if (!BallsTarget)
	{
		//DEBUGMESSAGE("!BallsTarget");
		FireBallInHands->Destroy();
		return;
	}
	if (!FireBallInHands)
	{
		DEBUGMESSAGE("!FireBallInHands");
		return;
	}
	FireBallMoveToTargetInputsStruct.OwnersController = OwnersController;
	FireBallMoveToTargetInputsStruct.Target = BallsTarget;
	FireBallMoveToTargetInputsStruct.DamageTypeClass = DamageTypeClass;
	FireBallMoveToTargetInputsStruct.Damage = FireBallStruct.Damage * FireBallStruct.MultiplierOfDamage;
	FireBallMoveToTargetInputsStruct.SpeedOfMoveToTarget = FireBallStruct.SpeedOfMoveToTarget;

	FTransform SpawnTransform = FireBallInHands->GetActorTransform();
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FireBallInFly = GetWorld()->SpawnActor<AFireBall>(AFireBall::StaticClass(), SpawnTransform, ActorSpawnParameters);
	if (!FireBallInFly)
	{
		DEBUGMESSAGE("!FireBallInFly");
		return;
	}

	FireBallInFly->CurrentMultiplierOfEmissive = FireBallInHands->CurrentMultiplierOfEmissive;

	FireBallInFlyMaterial = CreateMaterialFireBall(FireBallInFly);
	FireBallInHands->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
	bool bDestroyed = FireBallInHands->Destroy();
	if (!bDestroyed)
	{
		DEBUGMESSAGE("!bDestroyed");
		return;
	}
	FireBallInHands = nullptr;

	FireBallInFly->MoveToTarget(FireBallMoveToTargetInputsStruct);
}

void UFireBallComponent::DestroyAllFireBalls()
{
	if (FireBallInHands)
	{
		FireBallInHands->Destroy();
		FireBallInHands = nullptr;
	}
	if (FireBallInFly)
	{
		FireBallInFly->Destroy();
		FireBallInFly = nullptr;
	}
}

float UFireBallComponent::CalcDeltaEveryTick(float MaxValue, float CurrentValue, float CountOfTicks)
{
	float Delta = MaxValue - CurrentValue;
	if (CountOfTicks < 1)
	{
		DEBUGMESSAGE("CountOfTicks < 1");
		CountOfTicks = 1;
	}
	float DeltaEveryTick = Delta / CountOfTicks;
	return DeltaEveryTick;
}

float UFireBallComponent::CalcCountOfStepsInHands()
{
	float DeltaTime = ScaleAndEmissiveTimerTime;
	if (DeltaTime <= 0)
	{
		DEBUGMESSAGE("DeltaTime <= 0");
		DeltaTime = 0.02;
	}
	float Count = FireBallStruct.TimeInOwnersHand / DeltaTime;
	return Count;
}

UMaterialInstanceDynamic* UFireBallComponent::CreateMaterialFireBall(AFireBall* FireBall)
{
	UMaterialInstanceDynamic* Material = FireBall->Mesh->CreateDynamicMaterialInstance(0, FireBall->SourceMaterial, FName());
	Material->SetTextureParameterValue(TextureParameterName, FireBall->Texture);
	Material->SetVectorParameterValue(EmissiveColorParameterName, FireBall->EmissiveColor);
	Material->SetScalarParameterValue(EmissiveMultiplierParameterName, FireBall->CurrentMultiplierOfEmissive);
	return Material;
}

void UFireBallComponent::ScaleAndEmissive()
{
	if (!FireBallInHands)
	{
		//DEBUGMESSAGE("!FireBallInHands");
		GetWorld()->GetTimerManager().ClearTimer(ScaleAndEmissiveTimer);
		return;
	}
	FireBallInHands->CurrentMultiplierOfScale += DeltaMultiplierOfScaleEveryTick;
	//DEBUGSTRING(FString::SanitizeFloat(FireBallInHands->CurrentMultiplierOfScale));
	FVector ScaleVector = FireBallInHands->GetInitialScale() * FireBallInHands->CurrentMultiplierOfScale;

	FireBallInHands->SetActorScale3D(ScaleVector);

	FireBallInHands->CurrentMultiplierOfEmissive += DeltaMultiplierOfEmissiveEveryTick;
	FireBallInHandsMaterial->SetScalarParameterValue(EmissiveMultiplierParameterName, FireBallInHands->CurrentMultiplierOfEmissive);

	if (FireBallInHands->CurrentMultiplierOfScale >= FireBallStruct.MaxMultiplierOfScaleInOwnersHand)
	{
		GetWorld()->GetTimerManager().ClearTimer(ScaleAndEmissiveTimer);
	}

}

