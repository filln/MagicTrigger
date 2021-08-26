// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Для поднимания или опускания поднимаемых предметов.
 */


#include "UpDownLiftUpItemComponent.h"
#include "MagicTrigger\PlayerCharacter\PlayerCharacterMagicTrigger.h"
#include "MagicTrigger\Interfaces\LiftUpItemInterface.h"
#include "MagicTrigger\Items\LiftUp\LiftUpItem.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "MagicTrigger\Data\DebugMessage.h"

class ALiftUpItem;

// Sets default values for this component's properties
UUpDownLiftUpItemComponent::UUpDownLiftUpItemComponent()
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
	AttachOverTime = 0.15;
	StartTraceObstacleSocketName = FName(TEXT("Hips"));
	LiftUpClass = ALiftUpItem::StaticClass();
}


// Called when the game starts
void UUpDownLiftUpItemComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	PlayerCharacter = Cast<APlayerCharacterMagicTrigger>(Owner);
	if (PlayerCharacter)
	{
		OwnersMesh = PlayerCharacter->GetMesh();
		InterractCollision = PlayerCharacter->InteractCollision;
	}
	else
	{
		DEBUGMESSAGE("!PlayerCharacter")
	}

}

void UUpDownLiftUpItemComponent::DetachLiftUpItem()
{

	if (!LiftUpItem)
	{
		DEBUGMESSAGE("!LiftUpItem");
		return;
	}
	if (!IsInterfaceImplementedBy<ILiftUpItemInterface>(LiftUpItem))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<ILiftUpItemInterface>(LiftUpItem)");
		return;
	}
	LiftUpItem->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, false));

	FTransform PointPutDownTransform = PlayerCharacter->GetPointPutDownTransform();
	FVector TargetRelativeLocation = DetachLiftUpItemTraceOut.Location;
	FRotator TargetRelativeRotation = PointPutDownTransform.Rotator();
	FLatentActionInfo LatentInfo = FLatentActionInfo();
	LatentInfo.CallbackTarget = this;

	UKismetSystemLibrary::MoveComponentTo
	(
		LiftUpItem->GetRootComponent(),
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
	FTimerDelegate TmpDelegate;
	TmpDelegate.BindLambda
	(
		[=]()
	{

		ILiftUpItemInterface::Execute_SetSimulatePhysics_IF(LiftUpItem, true);
		LiftUpItem->SetActorEnableCollision(true);
		LiftUpItem = nullptr;
	}
	);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TmpDelegate, DetachOverTime, false);
}

void UUpDownLiftUpItemComponent::AttachLiftUpItem()
{
	if (!LiftUpItem)
	{
		DEBUGMESSAGE("!LiftUpItem");
		return;
	}
	if (!OwnersMesh)
	{
		DEBUGMESSAGE("!OwnersMesh");
		return;
	}
	if (!IsInterfaceImplementedBy<ILiftUpItemInterface>(LiftUpItem))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<ILiftUpItemInterface>(LiftUpItem)");
		return;
	}

	AttachSocket = ILiftUpItemInterface::Execute_GetAttachSocket_IF(LiftUpItem);
	ILiftUpItemInterface::Execute_SetSimulatePhysics_IF(LiftUpItem, false);


	LiftUpItem->SetActorEnableCollision(false);

	FVector TargetRelativeLocation = OwnersMesh->GetSocketLocation(AttachSocket);
	FRotator TargetRelativeRotation = LiftUpItem->GetRootComponent()->GetSocketRotation(AttachSocket);
	FLatentActionInfo LatentInfo = FLatentActionInfo();
	LatentInfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo
	(
		LiftUpItem->GetRootComponent(),
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
	FTimerDelegate TmpDelegate;
	TmpDelegate.BindLambda
	(
		[=]()
	{
		FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, true);
		LiftUpItem->AttachToComponent(OwnersMesh, AttachmentTransformRules, AttachSocket);
	}
	);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TmpDelegate, AttachOverTime, false);
}

void UUpDownLiftUpItemComponent::LiftUp()
{
	if (LiftUpItem)
	{
		return;
	}

	LiftUpItem = FindLiftUpItem();

	if (!LiftUpItem)
	{
		return;
	}
	PlayerCharacter->OffWatchingActors();

	if (IsInterfaceImplementedBy<ILiftUpItemInterface>(LiftUpItem))
	{
		ILiftUpItemInterface::Execute_LiftUpItself_IF(LiftUpItem);
	}
	else
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<ILiftUpItemInterface>(LiftUpItem)");
		return;
	}

}

void UUpDownLiftUpItemComponent::PickUpPickUpItem()
{
	if (!LiftUpItem)
	{
		//DEBUGMESSAGE("!LiftUpItem");
		return;
	}
	if (IsInterfaceImplementedBy<ILiftUpItemInterface>(LiftUpItem))
	{
		ILiftUpItemInterface::Execute_PickUpItself_IF(LiftUpItem);
	}
	else
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<ILiftUpItemInterface>(LiftUpItem)");
	}
}

void UUpDownLiftUpItemComponent::PutDown()
{
	if (!LiftUpItem)
	{
		//DEBUGMESSAGE("!LiftUpItem");
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

	if (IsInterfaceImplementedBy<ILiftUpItemInterface>(LiftUpItem))
	{
		ILiftUpItemInterface::Execute_PutDownItself_IF(LiftUpItem);
	}
	else
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<ILiftUpItemInterface>(LiftUpItem)");
	}
}

void UUpDownLiftUpItemComponent::DestroyLiftUpItem()
{
	if (!LiftUpItem)
	{
		DEBUGMESSAGE("!LiftUpItem");
		return;
	}

	bool bDestroyed = LiftUpItem->Destroy();
	if (bDestroyed)
	{
		LiftUpItem = nullptr;
	}
	else
	{
		DEBUGMESSAGE("!bDestroyed")
	}
}

AActor* UUpDownLiftUpItemComponent::FindLiftUpItem()
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

	AActor* ObservedActor = PlayerCharacter->GetObservedActor();
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

bool UUpDownLiftUpItemComponent::TracePutDownPoint()
{
	if (!GetWorld())
	{
		DEBUGMESSAGE("!GetWorld()");
		return false;
	}

	FTransform StartTraceTransform = PlayerCharacter->GetPointStartTraceToPutDownPointTransform();
	FTransform EndTraceTransform = PlayerCharacter->GetPointPutDownTransform();
	FVector StartTrace = StartTraceTransform.GetLocation();
	FVector EndTrace = EndTraceTransform.GetLocation();
	EndTrace.Z = EndTrace.Z - DeltaVerticalTraceZ;

	FName TraceTag = FName(TEXT("TracePutDownPoint"));
	FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams(TraceTag, FCollisionQueryParams::GetUnknownStatId());
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(Owner);
	IgnoredActors.Add(LiftUpItem);
	CollisionQueryParams.AddIgnoredActors(IgnoredActors);

	FCollisionResponseParams CollisionResponseParams;

#if WITH_EDITOR
	if (bDrawDebugTrace)
	{
		GetWorld()->DebugDrawTraceTag = TraceTag;
	}
	else
	{
		GetWorld()->DebugDrawTraceTag = FName();
	}
#endif

	bool bTraceResult = GetWorld()->LineTraceSingleByChannel(DetachLiftUpItemTraceOut, StartTrace, EndTrace, TraceCollisionChannel, CollisionQueryParams, CollisionResponseParams);

	return bTraceResult;
}

bool UUpDownLiftUpItemComponent::TraceObstacle()
{
	if (!Owner)
	{
		DEBUGMESSAGE("!Owner");
		return true;
	}

	FTransform StartTraceObstacleSocketNameTransform = PlayerCharacter->GetSocketTransform(StartTraceObstacleSocketName);
	FVector UpDownLiftingArrowForwardVector = PlayerCharacter->GetUpDownLiftingArrowForwardVector();
	FVector StartTrace = StartTraceObstacleSocketNameTransform.GetLocation();
	FVector EndTrace = StartTrace + UpDownLiftingArrowForwardVector * DistanceOfTraceObstacle;

	FName TraceTag = FName(TEXT("TraceObstacle"));
	FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams(TraceTag, FCollisionQueryParams::GetUnknownStatId());
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(Owner);
	IgnoredActors.Add(LiftUpItem);
	CollisionQueryParams.AddIgnoredActors(IgnoredActors);

	FCollisionResponseParams CollisionResponseParams;

#if WITH_EDITOR
	if (bDrawDebugTrace)
	{
		GetWorld()->DebugDrawTraceTag = TraceTag;
	}
	else
	{
		GetWorld()->DebugDrawTraceTag = FName();
	}
#endif

	FHitResult HitResultTmp;
	bool bTraceResult = GetWorld()->LineTraceSingleByChannel(HitResultTmp, StartTrace, EndTrace, TraceCollisionChannel, CollisionQueryParams, CollisionResponseParams);

	return bTraceResult;

}

