// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "ThrowComponent.h"
#include "MagicTrigger/AbilitySystem/Throw/ThrowableItem.h"
#include "MagicTrigger/AbilitySystem/AbilitySystemManager.h"
#include "MagicTrigger/Data/DebugMessage.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UThrowComponent::UThrowComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	ThrowableItemClass = AThrowableItem::StaticClass();
	CountOfThrowableItem = 0;
	AttachSocket = FName(TEXT("PickUpRightHand"));
}


// Called when the game starts
void UThrowComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (!Owner)
	{
		DEBUGMESSAGE("!Owner");
		return;
	}
	AbilitySystemManager = Cast<AAbilitySystemManager>(Owner);
	if (!AbilitySystemManager)
	{
		DEBUGMESSAGE("!AbilitySystemManager");
		return;
	}
}

void UThrowComponent::Use()
{
	if (GetCountOfThrowableItem() < 1)
	{
		return;
	}
	AbilitySystemManager->UseThrowAbility();
}

int UThrowComponent::GetCountOfThrowableItem() const
{
	return CountOfThrowableItem;
}

void UThrowComponent::SetCountOfThrowableItem(int InCount)
{
	CountOfThrowableItem = InCount;
}

void UThrowComponent::IncreaseCountOfThrowableItem()
{
	CountOfThrowableItem++;
	AbilitySystemManager->SetCountOfThrowableItemText();
}

void UThrowComponent::DecreaseCountOfThrowableItem()
{
	CountOfThrowableItem--;
	AbilitySystemManager->SetCountOfThrowableItemText();
}

void UThrowComponent::SpawnThrowableItem()
{
	if (!GetWorld())
	{
		DEBUGMESSAGE("!GetWorld()");
		return;
	}
	if (!AbilitySystemManager)
	{
		DEBUGMESSAGE("!AbilitySystemManager");
		return;
	}
	if (!PlayerCharacterMesh)
	{
		if (AbilitySystemManager->GetPlayerCharacterMesh())
		{
			PlayerCharacterMesh = AbilitySystemManager->GetPlayerCharacterMesh();
		}
		else
		{
			DEBUGMESSAGE("!PlayerCharacterMesh");
			return;
		}
	}

	if (ThrowableItemInHand)
	{
		//DEBUGMESSAGE("TempThrowableItem");
		ThrowableItemInHand->Destroy();
		ThrowableItemInHand = nullptr;
	}

	ThrowableItemInHand = SpawnThrowableItem_Internal();
	if (!ThrowableItemInHand)
	{
		DEBUGMESSAGE("!TempThrowableItem");
		return;
	}
	ThrowableItemInHand->SetActorEnableCollision(false);
	ThrowableItemInHand->SetSimulatePhysics(false);
	FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, true);
	ThrowableItemInHand->AttachToComponent(PlayerCharacterMesh, AttachmentTransformRules, AttachSocket);

}

void UThrowComponent::Throw()
{
	if (!ThrowableItemInHand)
	{
		DEBUGMESSAGE("!TempThrowableItem");
		return;
	}
	ThrowableItemInHand->Destroy();
	ThrowableItemInHand = nullptr;

	ThrowableItemInFly = SpawnThrowableItem_Internal();
	AActor* ObservedActor = AbilitySystemManager->GetObservedActor();
	FVector LaunchVelocity;
	if (ObservedActor)
	{
		bool bCalcVelocitySuccessful = 
			UGameplayStatics::SuggestProjectileVelocity_CustomArc
			(
				GetWorld(),
				LaunchVelocity,
				ThrowableItemInFly->GetActorLocation(),
				ObservedActor->GetActorLocation(),
				0,
				ThrowableItemInFly->ArcParam
			);
		if (!bCalcVelocitySuccessful)
		{
			DEBUGMESSAGE("!bCalcVelocitySuccessful");
			return;
		}
	}
	else
	{
		FVector UnitItemVelocity = UKismetMathLibrary::VLerp(AbilitySystemManager->GetPlayerCharacterForwardVector(), AbilitySystemManager->GetPlayerCharacterUpVector(), ThrowableItemInFly->ArcAlpha);
		FVector ItemVelocity = UnitItemVelocity * ThrowableItemInFly->Speed;
		LaunchVelocity = ItemVelocity + AbilitySystemManager->GetPlayerCharacterVelocity();
	}
	ThrowableItemInFly->PrepareBeforeFly(LaunchVelocity);
	DecreaseCountOfThrowableItem();
}

AThrowableItem* UThrowComponent::SpawnThrowableItem_Internal()
{
	FTransform SocketTransform = AbilitySystemManager->GetSocketTransform(AttachSocket);
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketTransform.GetLocation());
	SpawnTransform.SetRotation(SocketTransform.GetRotation());
	SpawnTransform.SetScale3D(FVector(1));
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AThrowableItem* ReturnThrowableItem = GetWorld()->SpawnActor<AThrowableItem>(ThrowableItemClass, SpawnTransform, ActorSpawnParameters);
	return ReturnThrowableItem;
}


