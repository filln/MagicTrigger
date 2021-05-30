// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Для поднимания или опускания поднимаемых предметов.
 */


#include "UpDownLiftingItemComponent.h"
#include "MagicTrigger\Interfaces\PlayerCharacterInterface.h"
#include "MagicTrigger\Interfaces\LiftingItemInterface.h"
#include "MagicTrigger\Interfaces\OwnerTargetSelectionInterface.h"
#include "MagicTrigger\Items\LiftingItem.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "MagicTrigger\Data\DebugMessage.h"

class ALiftingItem;

// Sets default values for this component's properties
UUpDownLiftingItemComponent::UUpDownLiftingItemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	DistanceOfTraceObstacle = 100;
	DeltaVerticalTraceZ = 20;
	TraceCollisionChannel = ECollisionChannel::ECC_Visibility;
	bDrawDebugTrace = false;
	DetachOverTime = 0.5;
	AttachOverTime = 0.5;
	StartTraceObstacleSocketName = FName(TEXT("Hips"));
	LiftUpClass = ALiftingItem::StaticClass();
}


// Called when the game starts
void UUpDownLiftingItemComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();

	if (Owner)
	{
		if (IsInterfaceImplementedBy<IPlayerCharacterInterface>(Owner))
		{
			OwnersMesh = IPlayerCharacterInterface::Execute_GetMesh_IF(Owner);
		}
		else
		{
			DEBUGMESSAGE("!IsInterfaceImplementedBy<IPlayerCharacterInterface>(Owner)")
		}

		if (IsInterfaceImplementedBy<IPlayerCharacterInterface>(Owner))
		{
			InterractCollision = IPlayerCharacterInterface::Execute_GetInteractCollision_IF(Owner);
		}
		else
		{
			DEBUGMESSAGE("!IsInterfaceImplementedBy<IPlayerCharacterInterface>(Owner)")
		}

	}
	else
	{
		DEBUGMESSAGE("!Owner")
	}
}

void UUpDownLiftingItemComponent::DetachLiftingActor()
{

	if (!LiftUpObject)
	{
		DEBUGMESSAGE("!LiftUpObject");
		return;
	}

	LiftUpObject->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, false));

	FTransform PointPutDownTransform;
	if (IsInterfaceImplementedBy<IPlayerCharacterInterface>(Owner))
	{
		PointPutDownTransform = IPlayerCharacterInterface::Execute_GetPointPutDownTransform_IF(Owner);
	}
	else
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IPlayerCharacterInterface>(Owner)");
		return;
	}

	FVector TargetRelativeLocation = DetachLiftingActorTraceOut.Location;
	FRotator TargetRelativeRotation = PointPutDownTransform.Rotator();
	FLatentActionInfo LatentInfo = FLatentActionInfo();
	LatentInfo.CallbackTarget = this;

	UKismetSystemLibrary::MoveComponentTo
	(
		LiftUpObject->GetRootComponent(),
		TargetRelativeLocation,
		TargetRelativeRotation,
		false,
		false,
		DetachOverTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UUpDownLiftingItemComponent::DoAfterMoveComponentInDetachLiftingActor, DetachOverTime);
}
void UUpDownLiftingItemComponent::DoAfterMoveComponentInDetachLiftingActor()
{
	if (IsInterfaceImplementedBy<ILiftingItemInterface>(LiftUpObject))
	{
		ILiftingItemInterface::Execute_SetSimulatePhysics_IF(LiftUpObject, true);
	}
	else
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<ILiftingItemInterface>(LiftUpObject)");
		return;
	}

	LiftUpObject->SetActorEnableCollision(true);
	LiftUpObject = nullptr;
}

void UUpDownLiftingItemComponent::AttachLiftingActor()
{
	if (!LiftUpObject)
	{
		DEBUGMESSAGE("!LiftUpObject");
		return;
	}
	if (!OwnersMesh)
	{
		DEBUGMESSAGE("!OwnersMesh");
		return;
	}
	if (!IsInterfaceImplementedBy<ILiftingItemInterface>(LiftUpObject))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<ILiftingItemInterface>(LiftUpObject)");
		return;
	}

	AttachSocket = ILiftingItemInterface::Execute_GetAttachSocket_IF(LiftUpObject);
	ILiftingItemInterface::Execute_SetSimulatePhysics_IF(LiftUpObject, false);


	LiftUpObject->SetActorEnableCollision(false);

	FVector TargetRelativeLocation = OwnersMesh->GetSocketLocation(AttachSocket);
	FRotator TargetRelativeRotation = LiftUpObject->GetRootComponent()->GetSocketRotation(AttachSocket);
	FLatentActionInfo LatentInfo = FLatentActionInfo();
	LatentInfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo
	(
		LiftUpObject->GetRootComponent(),
		TargetRelativeLocation,
		TargetRelativeRotation,
		false,
		false,
		AttachOverTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UUpDownLiftingItemComponent::DoAfterMoveComponentInAttachLiftingActor, AttachOverTime);

}

void UUpDownLiftingItemComponent::DoAfterMoveComponentInAttachLiftingActor()
{
	FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, true);
	LiftUpObject->AttachToComponent(OwnersMesh, AttachmentTransformRules, AttachSocket);

}


void UUpDownLiftingItemComponent::LiftUp()
{
	if (LiftUpObject)
	{
		return;
	}

	LiftUpObject = FindLifUpObject();

	if (!LiftUpObject)
	{
		return;
	}

	if (IsInterfaceImplementedBy<IOwnerTargetSelectionInterface>(Owner))
	{
		IOwnerTargetSelectionInterface::Execute_OffWatchingActors_IF(Owner);
	}
	else
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IOwnerTargetSelectionInterface>(Owner)");
		return;
	}

	if (IsInterfaceImplementedBy<ILiftingItemInterface>(LiftUpObject))
	{
		ILiftingItemInterface::Execute_SetPlayingAnimationLiftUp_IF(LiftUpObject, true);
	}
	else
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<ILiftingItemInterface>(LiftUpObject)");
		return;
	}

}

void UUpDownLiftingItemComponent::PutDown()
{
	if (!LiftUpObject)
	{
		//DEBUGMESSAGE("!LiftUpObject");
		return;
	}

	if (TraceObstacle())
	{
		return;
	}

	if (!TracePutDownPoint())
	{
		return;
	}

	if (IsInterfaceImplementedBy<ILiftingItemInterface>(LiftUpObject))
	{
		ILiftingItemInterface::Execute_SetPlayingAnimationPutDown_IF(LiftUpObject, true);
	}
	else
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<ILiftingItemInterface>(LiftUpObject)");
	}
}

void UUpDownLiftingItemComponent::DestroyLiftingActor()
{
	if (!LiftUpObject)
	{
		DEBUGMESSAGE("!LiftUpObject");
		return;
	}

	bool bDestroyed = LiftUpObject->Destroy();
	if (bDestroyed)
	{
		LiftUpObject = nullptr;
	}
	else
	{
		DEBUGMESSAGE("!bDestroyed")
	}
}

AActor* UUpDownLiftingItemComponent::FindLifUpObject()
{
	AActor* LiftUpObjectTmp = nullptr;


	if (!InterractCollision)
	{
		DEBUGMESSAGE("!InterractCollision");
		return LiftUpObjectTmp;
	}
	if (!LiftUpClass)
	{
		DEBUGMESSAGE("!LiftUpClass");
		return LiftUpObjectTmp;
	}

	TArray<AActor*> OverlappingActorsArr;
	InterractCollision->GetOverlappingActors(OverlappingActorsArr, LiftUpClass);

	if (!OverlappingActorsArr.Num())
	{
		return LiftUpObjectTmp;
	}

	AActor* ObservedActor = nullptr;
	if (IsInterfaceImplementedBy<IOwnerTargetSelectionInterface>(Owner))
	{
		ObservedActor = IOwnerTargetSelectionInterface::Execute_GetObservedActor_IF(Owner);
	}

	if (ObservedActor)
	{
		for (const auto& CurrentActor : OverlappingActorsArr)
		{
			if (!CurrentActor)
			{
				continue;
			}

			if (CurrentActor == ObservedActor)
			{
				return CurrentActor;
			}
		}
	}
	else
	{
		for (const auto& CurrentActor : OverlappingActorsArr)
		{
			if (CurrentActor)
			{
				return CurrentActor;
			}
			else
			{
				DEBUGMESSAGE("!CurrentActor")
			}
		}
	}

	return LiftUpObjectTmp;
}

bool UUpDownLiftingItemComponent::TracePutDownPoint()
{
	if (!GetWorld())
	{
		DEBUGMESSAGE("!GetWorld()");
		return false;
	}

	FTransform StartTraceTransform;
	FTransform EndTraceTransform;
	if (IsInterfaceImplementedBy<IPlayerCharacterInterface>(Owner))
	{
		StartTraceTransform = IPlayerCharacterInterface::Execute_GetPointStartTraceToPutDownPointTransform_IF(Owner);
		EndTraceTransform = IPlayerCharacterInterface::Execute_GetPointPutDownTransform_IF(Owner);
	}
	else
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IPlayerCharacterInterface>(Owner)");
		return false;
	}

	FVector StartTrace = StartTraceTransform.GetLocation();
	FVector EndTrace = EndTraceTransform.GetLocation();
	EndTrace.Z = EndTrace.Z - DeltaVerticalTraceZ;

	FName TraceTag = FName(TEXT("TracePutDownPoint"));
	FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams(TraceTag, FCollisionQueryParams::GetUnknownStatId());
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(Owner);
	IgnoredActors.Add(LiftUpObject);
	CollisionQueryParams.AddIgnoredActors(IgnoredActors);

	FCollisionResponseParams CollisionResponseParams;


	if (bDrawDebugTrace)
	{
		GetWorld()->DebugDrawTraceTag = TraceTag;
	}
	else
	{
		GetWorld()->DebugDrawTraceTag = FName();
	}

	bool bTraceResult = GetWorld()->LineTraceSingleByChannel(DetachLiftingActorTraceOut, StartTrace, EndTrace, TraceCollisionChannel, CollisionQueryParams, CollisionResponseParams);

	return bTraceResult;
}

bool UUpDownLiftingItemComponent::TraceObstacle()
{
	if (!Owner)
	{
		DEBUGMESSAGE("!Owner");
		return true;
	}

	FTransform StartTraceObstacleSocketNameTransform;
	FVector UpDownLiftingArrowForwardVector;
	if (IsInterfaceImplementedBy<IPlayerCharacterInterface>(Owner))
	{
		StartTraceObstacleSocketNameTransform = IPlayerCharacterInterface::Execute_GetSocketTransform_IF(Owner, StartTraceObstacleSocketName);
		UpDownLiftingArrowForwardVector = IPlayerCharacterInterface::Execute_GetUpDownLiftingArrowForwardVector_IF(Owner);
	}
	else
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IPlayerCharacterInterface>(Owner)");
		return true;
	}

	FVector StartTrace = StartTraceObstacleSocketNameTransform.GetLocation();
	FVector EndTrace = StartTrace + UpDownLiftingArrowForwardVector * DistanceOfTraceObstacle;

	FName TraceTag = FName(TEXT("TraceObstacle"));
	FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams(TraceTag, FCollisionQueryParams::GetUnknownStatId());
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(Owner);
	IgnoredActors.Add(LiftUpObject);
	CollisionQueryParams.AddIgnoredActors(IgnoredActors);

	FCollisionResponseParams CollisionResponseParams;


	if (bDrawDebugTrace)
	{
		GetWorld()->DebugDrawTraceTag = TraceTag;
	}
	else
	{
		GetWorld()->DebugDrawTraceTag = FName();
	}

	FHitResult HitResultTmp;
	bool bTraceResult = GetWorld()->LineTraceSingleByChannel(HitResultTmp, StartTrace, EndTrace, TraceCollisionChannel, CollisionQueryParams, CollisionResponseParams);

	return bTraceResult;

}

