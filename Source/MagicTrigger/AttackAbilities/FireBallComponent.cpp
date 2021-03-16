// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Компонент атакующей абилки фаербола.
 */

#pragma once

#include "FireBallComponent.h"
#include "MagicTrigger\AttackAbilities\FireBall.h"
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

	this->Owner = GetOwner();
	if (!this->Owner)
	{
		DEBUGMESSAGE("!this->Owner");
	}
	else
	{
		this->FireBallMoveToTargetInputsStruct.Owner = this->Owner;
	}
	
	this->CountOfTimerStepsInHands = CalcCountOfStepsInHands();
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

	this->OwnersMesh = InOwnersMesh;

	if (this->FireBallInHands)
	{
		bool bDestroyed = this->FireBallInHands->Destroy();
		if (!bDestroyed)
		{
			DEBUGMESSAGE("!bDestroyed");
			return;
		}
		this->FireBallInHands = nullptr;
	}

	FTransform SocketTransform = this->OwnersMesh->GetSocketTransform(this->OwnersAttachSocket);
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketTransform.GetLocation());
	SpawnTransform.SetRotation(SocketTransform.GetRotation());
	SpawnTransform.SetScale3D(FVector(1));
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	this->FireBallInHands = GetWorld()->SpawnActor<AFireBall>(AFireBall::StaticClass(), SpawnTransform, ActorSpawnParameters);
	if (!this->FireBallInHands)
	{
		DEBUGMESSAGE("!this->FireBallInHands");
		return;
	}

	this->FireBallInHandsMaterial = CreateMaterialFireBall(this->FireBallInHands);
	if (!this->FireBallInHandsMaterial)
	{
		DEBUGMESSAGE("!this->FireBallInHandsMaterial");
		return;
	}
	this->FireBallInHands->SetActorEnableCollision(false);
	FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules(EAttachmentRule::KeepWorld, true);
	this->FireBallInHands->AttachToComponent(this->OwnersMesh, AttachmentRules, this->OwnersAttachSocket);
	this->FireBallInHands->SaveInitialScale();

	this->DeltaMultiplierOfScaleEveryTick = CalcDeltaEveryTick(this->FireBallStruct.MaxMultiplierOfScaleInOwnersHand, this->FireBallInHands->CurrentMultiplierOfScale, this->CountOfTimerStepsInHands);
	this->DeltaMultiplierOfEmissiveEveryTick = CalcDeltaEveryTick(this->FireBallStruct.MaxEmissiveMultiplierInOwnersHand, this->FireBallInHands->CurrentMultiplierOfEmissive, this->CountOfTimerStepsInHands);

	GetWorld()->GetTimerManager().ClearTimer(this->ScaleAndEmissiveTimer);
	GetWorld()->GetTimerManager().SetTimer(this->ScaleAndEmissiveTimer, this, &UFireBallComponent::ScaleAndEmissive, ScaleAndEmissiveTimerTime, true);

}

void UFireBallComponent::MoveFireBallToTarget(AController* OwnersController, AActor* BallsTarget)
{
	if (!OwnersController)
	{
		DEBUGMESSAGE("!OwnersController");
		return;
	}
	if (!this->Owner)
	{
		DEBUGMESSAGE("!this->Owner");
		return;
	}
	if (!BallsTarget)
	{
		//DEBUGMESSAGE("!BallsTarget");
		this->FireBallInHands->Destroy();
		return;
	}
	if (!this->FireBallInHands)
	{
		DEBUGMESSAGE("!this->FireBallInHands");
		return;
	}
	this->FireBallMoveToTargetInputsStruct.OwnersController = OwnersController;
	this->FireBallMoveToTargetInputsStruct.Target = BallsTarget;
	this->FireBallMoveToTargetInputsStruct.DamageTypeClass = this->DamageTypeClass;
	this->FireBallMoveToTargetInputsStruct.Damage = FireBallStruct.Damage * FireBallStruct.MultiplierOfDamage;
	this->FireBallMoveToTargetInputsStruct.SpeedOfMoveToTarget = FireBallStruct.SpeedOfMoveToTarget;

	FTransform SpawnTransform = this->FireBallInHands->GetActorTransform();
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	this->FireBallInFly = GetWorld()->SpawnActor<AFireBall>(AFireBall::StaticClass(), SpawnTransform, ActorSpawnParameters);
	if (!this->FireBallInFly)
	{
		DEBUGMESSAGE("!this->FireBallInFly");
		return;
	}

	this->FireBallInFlyMaterial = CreateMaterialFireBall(this->FireBallInFly);
	this->FireBallInHands->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
	bool bDestroyed = this->FireBallInHands->Destroy();
	if (!bDestroyed)
	{
		DEBUGMESSAGE("!bDestroyed");
		return;
	}
	this->FireBallInHands = nullptr;

	this->FireBallInFly->MoveToTarget(this->FireBallMoveToTargetInputsStruct);
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
	float DeltaTime = this->ScaleAndEmissiveTimerTime;
	if (DeltaTime <= 0)
	{
		DEBUGMESSAGE("DeltaTime <= 0");
		DeltaTime = 0.02;
	}
	float Count = this->FireBallStruct.TimeInOwnersHand / DeltaTime;
	return Count;
}

UMaterialInstanceDynamic* UFireBallComponent::CreateMaterialFireBall(AFireBall* FireBall)
{
	UMaterialInstanceDynamic* Material = FireBall->Mesh->CreateDynamicMaterialInstance(0, FireBall->SourceMaterial, FName());
	Material->SetTextureParameterValue(this->TextureParameterName, FireBall->Texture);
	Material->SetVectorParameterValue(this->EmissiveColorParameterName, FireBall->EmissiveColor);
	Material->SetScalarParameterValue(this->EmissiveMultiplierParameterName, FireBall->CurrentMultiplierOfEmissive);
	return Material;
}

void UFireBallComponent::ScaleAndEmissive()
{
	if (!this->FireBallInHands)
	{
		//DEBUGMESSAGE("!this->FireBallInHands");
		GetWorld()->GetTimerManager().ClearTimer(this->ScaleAndEmissiveTimer);
		return;
	}
	this->FireBallInHands->CurrentMultiplierOfScale += this->DeltaMultiplierOfScaleEveryTick;
	//DEBUGSTRING(FString::SanitizeFloat(this->FireBallInHands->CurrentMultiplierOfScale));
	FVector ScaleVector = this->FireBallInHands->GetInitialScale() * this->FireBallInHands->CurrentMultiplierOfScale;

	this->FireBallInHands->SetActorScale3D(ScaleVector);

	this->FireBallInHands->CurrentMultiplierOfEmissive += this->DeltaMultiplierOfEmissiveEveryTick;
	this->FireBallInHandsMaterial->SetScalarParameterValue(this->EmissiveMultiplierParameterName, this->FireBallInHands->CurrentMultiplierOfEmissive);

	if (this->FireBallInHands->CurrentMultiplierOfScale >= this->FireBallStruct.MaxMultiplierOfScaleInOwnersHand)
	{
		GetWorld()->GetTimerManager().ClearTimer(this->ScaleAndEmissiveTimer);
	}

}

