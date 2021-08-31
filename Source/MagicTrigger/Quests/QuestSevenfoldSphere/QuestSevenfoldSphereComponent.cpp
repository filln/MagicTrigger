// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSevenfoldSphereComponent.h"
#include "MagicTrigger/Data/DebugMessage.h"
#include "MagicTrigger/Quests/QuestSevenfoldSphere/PlatformForBox4.h"
#include "MagicTrigger/Quests/QuestSevenfoldSphere/PlatformForBox5.h"
#include "MagicTrigger/Quests/QuestSevenfoldSphere/RockDoor.h"
#include "MagicTrigger/Quests/QuestSevenfoldSphere/BoxForPlatformParent.h"
#include "MagicTrigger/PlayerCharacter/PlayerCharacterMagicTrigger.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UQuestSevenfoldSphereComponent::UQuestSevenfoldSphereComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	UpLocation = FVector(-82006.828, -60527.711, 5010);
	PauseBeforeCheckKey = 2;
	OpenBigWallTag = FName(TEXT("OpenBigWall"));
	bLiftDown = true;
	bDisableOverlapCharacter = false;
	BeginOverlapMoveDownOverTime = 1;
	EndOverlapMoveUpOverTime = 1;
	MoveCharacterToCenterLiftOverTime = 0.2;
	MoveLiftOverTime = 4;
	OpenRockDoorOverTime = 5;
	OpenRockDoorOffset = 70;
	MoveCameraSpeed = 0.4;
}


// Called when the game starts
void UQuestSevenfoldSphereComponent::BeginPlay()
{
	Super::BeginPlay();

	if (PlatformForBox4 && PlatformForBox5)
	{
		PlatformForBox4->Platform4OverlapBoxDelegate.BindUObject(this, &UQuestSevenfoldSphereComponent::Platform4Or5BeginOverlapBox);
		PlatformForBox5->Platform5OverlapBoxDelegate.BindUObject(this, &UQuestSevenfoldSphereComponent::Platform4Or5BeginOverlapBox);
	}
	else
	{
		DEBUGMESSAGE("!PlatformForBox4 || !PlatformForBox5");
	}

}

void UQuestSevenfoldSphereComponent::LiftBeginOverlapCharacter(UPrimitiveComponent* InCharacterCollision)
{
	ACharacter* PlayerCharacterTmp = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	PlayerCharacter = Cast<APlayerCharacterMagicTrigger>(PlayerCharacterTmp);
	if (!PlayerCharacter)
	{
		DEBUGMESSAGE("!PlayerCharacter");
		return;
	}
	UCapsuleComponent* InCapsuleComponent = Cast<UCapsuleComponent>(InCharacterCollision);
	if (!InCapsuleComponent)
	{
		return;
	}
	if (PlayerCharacter->GetCapsuleComponent() != InCapsuleComponent || bDisableOverlapCharacter)
	{
		return;
	}

	BeginOverlapMoveDown();
}

void UQuestSevenfoldSphereComponent::LiftEndOverlapCharacter(UPrimitiveComponent* InCharacterCollision)
{
	ACharacter* PlayerCharacterTmp = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	PlayerCharacter = Cast<APlayerCharacterMagicTrigger>(PlayerCharacterTmp);
	if (!PlayerCharacter)
	{
		DEBUGMESSAGE("!PlayerCharacter");
		return;
	}
	UCapsuleComponent* InCapsuleComponent = Cast<UCapsuleComponent>(InCharacterCollision);
	if (!InCapsuleComponent)
	{
		return;
	}
	if (PlayerCharacter->GetCapsuleComponent() != InCapsuleComponent || bDisableOverlapCharacter)
	{
		return;
	}

	EndOverlapMoveUp();
}

void UQuestSevenfoldSphereComponent::BeginOverlapMoveDown()
{

	if (bLiftDown)
	{
		CurrentLocation = InitialLocation;
	}
	else
	{
		CurrentLocation = UpLocation;
	}

	//Лифт опускается на расстояние своей высоты ExtentZ.
	float ExtentZ = 2 * Mesh->Bounds.BoxExtent.Z;
	float TargetLocationZ = CurrentLocation.Z - ExtentZ;

	FVector TargetRelativeLocation = FVector(CurrentLocation.X, CurrentLocation.Y, TargetLocationZ);
	FRotator TargetRelativeRotation = GetOwner()->GetActorRotation();
	FLatentActionInfo LatentInfo = FLatentActionInfo();
	LatentInfo.CallbackTarget = this;

	UKismetSystemLibrary::MoveComponentTo
	(
		GetOwner()->GetRootComponent(),
		TargetRelativeLocation,
		TargetRelativeRotation,
		false,
		false,
		BeginOverlapMoveDownOverTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UQuestSevenfoldSphereComponent::CheckKey, PauseBeforeCheckKey);
}

void UQuestSevenfoldSphereComponent::EndOverlapMoveUp()
{
	if (bLiftDown)
	{
		CurrentLocation = InitialLocation;
	}
	else
	{
		CurrentLocation = UpLocation;
	}

	FVector TargetRelativeLocation = CurrentLocation;
	FRotator TargetRelativeRotation = GetOwner()->GetActorRotation();
	FLatentActionInfo LatentInfo = FLatentActionInfo();
	LatentInfo.CallbackTarget = this;

	UKismetSystemLibrary::MoveComponentTo
	(
		GetOwner()->GetRootComponent(),
		TargetRelativeLocation,
		TargetRelativeRotation,
		false,
		false,
		EndOverlapMoveUpOverTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);
}

void UQuestSevenfoldSphereComponent::CheckKey()
{
	if (!PlayerCharacter)
	{
		DEBUGMESSAGE("!PlayerCharacter");
		return;
	}
	//Не проверять и не двигать лифт, если перса нет на лифте.
	bool bOverlappingPlayerCharacter = OverlapCollision->IsOverlappingComponent(PlayerCharacter->GetCapsuleComponent());
	if (!bOverlappingPlayerCharacter)
	{
		return;
	}
	if (bLiftDown)
	{
		if (IsRightPlacingsDown())
		{
			LiftIsOpen();
		}
		else
		{
			LiftIsClosed();
		}
	}
	//!bLiftDown
	else
	{
		if (IsRightPlacingsUp())
		{
			LiftIsOpen();
		}
		else
		{
			LiftIsClosed();
		}
	}
}

bool UQuestSevenfoldSphereComponent::IsRightPlacingsDown()
{
	//Все нижние платформы должны иметь правильные боксы.
	for (auto CurrentPlatform : PlatformsForBoxDown)
	{
		if (!CurrentPlatform->CurrentBox)
		{
			return false;
		}
		if (CurrentPlatform->Tags.Num() == 0 || CurrentPlatform->CurrentBox->Tags.Num() == 0)
		{
			return false;
		}
		if (CurrentPlatform->Tags[0] != CurrentPlatform->CurrentBox->Tags[0])
		{
			return false;
		}
	}
	return true;
}

bool UQuestSevenfoldSphereComponent::IsRightPlacingsUp()
{
	//Любая одна из верхних платформ должна иметь правильный бокс.
	for (auto CurrentPlatform : PlatformsForBoxUp)
	{
		if (!CurrentPlatform->CurrentBox)
		{
			return false;
		}
		if (CurrentPlatform->Tags.Num() == 0 || CurrentPlatform->CurrentBox->Tags.Num() == 0)
		{
			return false;
		}
		if (CurrentPlatform->Tags[0] == CurrentPlatform->CurrentBox->Tags[0])
		{
			return true;
		}
	}
	return false;
}

void UQuestSevenfoldSphereComponent::LiftIsOpen()
{
	if (!PlayerCharacter)
	{
		DEBUGMESSAGE("!PlayerCharacter");
		return;
	}
	//Двигать лифт вверх или вниз в зависимости от bLiftDown.
	SetCharacterParameters(true);
	MoveCharacterToCenterLift();
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UQuestSevenfoldSphereComponent::MoveLift, bLiftDown);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, MoveCharacterToCenterLiftOverTime, false);
}

void UQuestSevenfoldSphereComponent::LiftIsClosed()
{
	/**
	 * Переместить боксы к начальному положению.
	 */
	if (bLiftDown)
	{
		for (auto CurrentPlatform : PlatformsForBoxDown)
		{
			if (CurrentPlatform->CurrentBox)
			{
				CurrentPlatform->CurrentBox->MoveToInitialLocation();
			}
		}
	}
	else
	{
		for (auto CurrentPlatform : PlatformsForBoxUp)
		{
			if (CurrentPlatform->CurrentBox)
			{
				CurrentPlatform->CurrentBox->MoveToInitialLocation();
			}
		}
	}
}

void UQuestSevenfoldSphereComponent::MoveCharacterToCenterLift()
{
	FVector TargetRelativeLocation = AttachCharacterPoint->GetComponentLocation();
	FRotator TargetRelativeRotation = PlayerCharacter->GetActorRotation();
	FLatentActionInfo LatentInfo = FLatentActionInfo();
	LatentInfo.CallbackTarget = this;

	UKismetSystemLibrary::MoveComponentTo
	(
		PlayerCharacter->GetRootComponent(),
		TargetRelativeLocation,
		TargetRelativeRotation,
		false,
		false,
		MoveCharacterToCenterLiftOverTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);
}

void UQuestSevenfoldSphereComponent::MoveLift(bool bMoveUp)
{
	FAttachmentTransformRules TransformRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, true);
	PlayerCharacter->AttachToComponent(AttachCharacterPoint, TransformRules);
	FVector TargetRelativeLocation;
	if (bMoveUp)
	{
		TargetRelativeLocation = UpLocation;
	} 
	else
	{
		TargetRelativeLocation = InitialLocation;
	}
	FRotator TargetRelativeRotation = FRotator(GetOwner()->GetActorRotation().Pitch, GetOwner()->GetActorRotation().Yaw + 180, GetOwner()->GetActorRotation().Roll);
	FLatentActionInfo LatentInfo = FLatentActionInfo();
	LatentInfo.CallbackTarget = this;
	UKismetSystemLibrary::MoveComponentTo
	(
		GetOwner()->GetRootComponent(),
		TargetRelativeLocation,
		TargetRelativeRotation,
		false,
		false,
		MoveLiftOverTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);
	FTimerHandle TmpTimer;
	FTimerDelegate TmpDelegate;
	TmpDelegate.BindLambda
	(
		[=]()
	{
		GetWorld()->GetTimerManager().ClearTimer(MoveCameraTimer);
		bLiftDown = !bMoveUp;
		SetCharacterParameters(false);
		BeginOverlapMoveDown();
	}
	);
	GetWorld()->GetTimerManager().SetTimer(TmpTimer, TmpDelegate, MoveLiftOverTime, false);

	//Вращать камеру, пока двигается лифт.
	FTimerDelegate MoveCameraTmpDelegate;
	MoveCameraTmpDelegate.BindLambda
	(
		[=]()
	{
		PlayerCharacter->AddControllerYawInput(MoveCameraSpeed);
	}
	);
	GetWorld()->GetTimerManager().SetTimer(MoveCameraTimer, MoveCameraTmpDelegate, 0.017, true);
}

void UQuestSevenfoldSphereComponent::SetCharacterParameters(bool bCharacterInLift)
{
	bDisableOverlapCharacter = bCharacterInLift;
	PlayerCharacter->SetEnableMovement(!bCharacterInLift);
	if (bCharacterInLift)
	{
		PlayerCharacter->OffWatchingActors();
		PlayerCharacter->GetCharacterMovement()->DisableMovement();
		PlayerCharacter->SetActorEnableCollision(false);
	} 
	else
	{
		PlayerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		FDetachmentTransformRules DetachmentRules = FDetachmentTransformRules(EDetachmentRule::KeepWorld, true);
		PlayerCharacter->DetachFromActor(DetachmentRules);
		PlayerCharacter->SetActorEnableCollision(true);
	}

}

void UQuestSevenfoldSphereComponent::Platform4Or5BeginOverlapBox()
{
	if (IsRightPlacingsForRockDoor())
	{
		OpenRockDoor();
	}
}

bool UQuestSevenfoldSphereComponent::IsRightPlacingsForRockDoor()
{
	if (!PlatformForBox4)
	{
		DEBUGMESSAGE("!PlatformForBox4");
		return false;
	}
	if (!PlatformForBox5)
	{
		DEBUGMESSAGE("!PlatformForBox5");
		return false;
	}
	if (!PlatformForBox4->CurrentBox || !PlatformForBox5->CurrentBox)
	{
		return false;
	}

	if 
		(
			PlatformForBox4->CurrentBox->ActorHasTag(OpenBigWallTag) 
			&& PlatformForBox5->CurrentBox->ActorHasTag(OpenBigWallTag)
			)
	{
		return true;
	}

	return false;
}

void UQuestSevenfoldSphereComponent::OpenRockDoor()
{
	if (!RockDoor)
	{
		DEBUGMESSAGE("!RockDoor");
		return;
	}
	FVector TargetRelativeLocation = FVector(RockDoor->DoorInitialLocation.X, RockDoor->DoorInitialLocation.Y + OpenRockDoorOffset, RockDoor->DoorInitialLocation.Z);
	FRotator TargetRelativeRotation = RockDoor->DoorCollision->GetComponentRotation();
	FLatentActionInfo LatentInfo = FLatentActionInfo();
	LatentInfo.CallbackTarget = this;

	UKismetSystemLibrary::MoveComponentTo
	(
		RockDoor->DoorCollision,
		TargetRelativeLocation,
		TargetRelativeRotation,
		false,
		false,
		OpenRockDoorOverTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);
}



