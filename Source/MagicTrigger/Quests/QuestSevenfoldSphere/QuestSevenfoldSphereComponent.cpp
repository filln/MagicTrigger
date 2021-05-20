// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestSevenfoldSphereComponent.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "MagicTrigger\Quests\QuestSevenfoldSphere\PlatformForBox4.h"
#include "MagicTrigger\Quests\QuestSevenfoldSphere\PlatformForBox5.h"
#include "MagicTrigger\Interfaces\OwnerTargetSelectionInterface.h"
#include "MagicTrigger\Quests\QuestSevenfoldSphere\RockDoor.h"
#include "MagicTrigger\Quests\QuestSevenfoldSphere\BoxForPlatformParent.h"
#include "Components\BoxComponent.h"
#include "Components\SphereComponent.h"
#include "Components\StaticMeshComponent.h"
#include "Components\CapsuleComponent.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "GameFramework\Character.h"
#include "Kismet\GameplayStatics.h"
#include "Kismet\KismetSystemLibrary.h"


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

	if (this->PlatformForBox4 && this->PlatformForBox5)
	{
		this->PlatformForBox4->Platform4OverlapBoxDelegate.BindUObject(this, &UQuestSevenfoldSphereComponent::Platform4Or5BeginOverlapBox);
		this->PlatformForBox5->Platform5OverlapBoxDelegate.BindUObject(this, &UQuestSevenfoldSphereComponent::Platform4Or5BeginOverlapBox);
	}
	else
	{
		DEBUGMESSAGE("!this->PlatformForBox4 || !this->PlatformForBox5");
	}

}

void UQuestSevenfoldSphereComponent::LiftBeginOverlapCharacter(UPrimitiveComponent* InCharacterCollision)
{
	this->PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!this->PlayerCharacter)
	{
		DEBUGMESSAGE("!this->PlayerCharacter");
		return;
	}
	UCapsuleComponent* InCapsuleComponent = Cast<UCapsuleComponent>(InCharacterCollision);
	if (!InCapsuleComponent)
	{
		return;
	}
	if (this->PlayerCharacter->GetCapsuleComponent() != InCapsuleComponent || this->bDisableOverlapCharacter)
	{
		return;
	}

	BeginOverlapMoveDown();
}

void UQuestSevenfoldSphereComponent::LiftEndOverlapCharacter(UPrimitiveComponent* InCharacterCollision)
{
	this->PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!this->PlayerCharacter)
	{
		DEBUGMESSAGE("!this->PlayerCharacter");
		return;
	}
	UCapsuleComponent* InCapsuleComponent = Cast<UCapsuleComponent>(InCharacterCollision);
	if (!InCapsuleComponent)
	{
		return;
	}
	if (this->PlayerCharacter->GetCapsuleComponent() != InCapsuleComponent || this->bDisableOverlapCharacter)
	{
		return;
	}

	EndOverlapMoveUp();
}

void UQuestSevenfoldSphereComponent::BeginOverlapMoveDown()
{

	if (bLiftDown)
	{
		this->CurrentLocation = this->InitialLocation;
	}
	else
	{
		this->CurrentLocation = this->UpLocation;
	}

	//Лифт опускается на расстояние своей высоты ExtentZ.
	float ExtentZ = 2 * this->Mesh->Bounds.BoxExtent.Z;
	float TargetLocationZ = this->CurrentLocation.Z - ExtentZ;

	FVector TargetRelativeLocation = FVector(this->CurrentLocation.X, this->CurrentLocation.Y, TargetLocationZ);
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
		this->BeginOverlapMoveDownOverTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UQuestSevenfoldSphereComponent::CheckKey, this->PauseBeforeCheckKey);
}

void UQuestSevenfoldSphereComponent::EndOverlapMoveUp()
{
	if (bLiftDown)
	{
		this->CurrentLocation = this->InitialLocation;
	}
	else
	{
		this->CurrentLocation = this->UpLocation;
	}

	FVector TargetRelativeLocation = this->CurrentLocation;
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
		this->EndOverlapMoveUpOverTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);
}

void UQuestSevenfoldSphereComponent::CheckKey()
{
	if (!this->PlayerCharacter)
	{
		DEBUGMESSAGE("!this->PlayerCharacter");
		return;
	}
	//Не проверять и не двигать лифт, если перса нет на лифте.
	bool bOverlappingPlayerCharacter = OverlapCollision->IsOverlappingComponent(this->PlayerCharacter->GetCapsuleComponent());
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
	for (auto CurrentPlatform : this->PlatformsForBoxDown)
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
	for (auto CurrentPlatform : this->PlatformsForBoxUp)
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
	if (!this->PlayerCharacter)
	{
		DEBUGMESSAGE("!this->PlayerCharacter");
		return;
	}
	//Двигать лифт вверх или вниз в зависимости от this->bLiftDown.
	SetCharacterParameters(true);
	MoveCharacterToCenterLift();
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &UQuestSevenfoldSphereComponent::MoveLift, this->bLiftDown);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, this->MoveCharacterToCenterLiftOverTime, false);
}

void UQuestSevenfoldSphereComponent::LiftIsClosed()
{
	/**
	 * Переместить боксы к начальному положению.
	 */
	if (this->bLiftDown)
	{
		for (auto CurrentPlatform : this->PlatformsForBoxDown)
		{
			if (CurrentPlatform->CurrentBox)
			{
				CurrentPlatform->CurrentBox->MoveToInitialLocation();
			}
		}
	}
	else
	{
		for (auto CurrentPlatform : this->PlatformsForBoxUp)
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
	FVector TargetRelativeLocation = this->AttachCharacterPoint->GetComponentLocation();
	FRotator TargetRelativeRotation = this->PlayerCharacter->GetActorRotation();
	FLatentActionInfo LatentInfo = FLatentActionInfo();
	LatentInfo.CallbackTarget = this;

	UKismetSystemLibrary::MoveComponentTo
	(
		this->PlayerCharacter->GetRootComponent(),
		TargetRelativeLocation,
		TargetRelativeRotation,
		false,
		false,
		this->MoveCharacterToCenterLiftOverTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);
}

void UQuestSevenfoldSphereComponent::MoveLift(bool bMoveUp)
{
	FAttachmentTransformRules TransformRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, true);
	this->PlayerCharacter->AttachToComponent(AttachCharacterPoint, TransformRules);

	FVector TargetRelativeLocation;
	if (bMoveUp)
	{
		TargetRelativeLocation = this->UpLocation;
	} 
	else
	{
		TargetRelativeLocation = this->InitialLocation;
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
		this->MoveLiftOverTime,
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
		GetWorld()->GetTimerManager().ClearTimer(this->MoveCameraTimer);
		this->bLiftDown = !bMoveUp;
		SetCharacterParameters(false);
		BeginOverlapMoveDown();
	}
	);
	GetWorld()->GetTimerManager().SetTimer(TmpTimer, TmpDelegate, this->MoveLiftOverTime, false);

	//Вращать камеру, пока двигается лифт.
	FTimerDelegate MoveCameraTmpDelegate;
	MoveCameraTmpDelegate.BindLambda
	(
		[=]()
	{
		this->PlayerCharacter->AddControllerYawInput(this->MoveCameraSpeed);
	}
	);
	GetWorld()->GetTimerManager().SetTimer(this->MoveCameraTimer, MoveCameraTmpDelegate, 0.017, true);

}

void UQuestSevenfoldSphereComponent::SetCharacterParameters(bool bCharacterInLift)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController)
	{
		DEBUGMESSAGE("!PlayerController");
		return;
	}

	bDisableOverlapCharacter = bCharacterInLift;
	if (bCharacterInLift)
	{
		this->PlayerCharacter->DisableInput(PlayerController);
		if (!IsInterfaceImplementedBy<IOwnerTargetSelectionInterface>(this->PlayerCharacter))
		{
			DEBUGMESSAGE("!IsInterfaceImplementedBy<IOwnerTargetSelectionInterface>(this->PlayerCharacter)");
			return;
		}
		IOwnerTargetSelectionInterface::Execute_OffWatchingActors_IF(this->PlayerCharacter);
		this->PlayerCharacter->GetCharacterMovement()->DisableMovement();
		this->PlayerCharacter->SetActorEnableCollision(false);
	} 
	else
	{
		this->PlayerCharacter->EnableInput(PlayerController);
		this->PlayerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		FDetachmentTransformRules DetachmentRules = FDetachmentTransformRules(EDetachmentRule::KeepWorld, true);
		this->PlayerCharacter->DetachFromActor(DetachmentRules);
		this->PlayerCharacter->SetActorEnableCollision(true);
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
	if (!this->PlatformForBox4)
	{
		DEBUGMESSAGE("!this->PlatformForBox4");
		return false;
	}
	if (!this->PlatformForBox5)
	{
		DEBUGMESSAGE("!this->PlatformForBox5");
		return false;
	}
	if (!this->PlatformForBox4->CurrentBox || !this->PlatformForBox5->CurrentBox)
	{
		return false;
	}

	if 
		(
			this->PlatformForBox4->CurrentBox->ActorHasTag(this->OpenBigWallTag) 
			&& this->PlatformForBox5->CurrentBox->ActorHasTag(this->OpenBigWallTag)
			)
	{
		return true;
	}

	return false;
}

void UQuestSevenfoldSphereComponent::OpenRockDoor()
{
	if (!this->RockDoor)
	{
		DEBUGMESSAGE("!this->RockDoor");
		return;
	}
	FVector TargetRelativeLocation = FVector(this->RockDoor->DoorInitialLocation.X, this->RockDoor->DoorInitialLocation.Y + this->OpenRockDoorOffset, this->RockDoor->DoorInitialLocation.Z);
	FRotator TargetRelativeRotation = this->RockDoor->DoorCollision->GetComponentRotation();
	FLatentActionInfo LatentInfo = FLatentActionInfo();
	LatentInfo.CallbackTarget = this;

	UKismetSystemLibrary::MoveComponentTo
	(
		this->RockDoor->DoorCollision,
		TargetRelativeLocation,
		TargetRelativeRotation,
		false,
		false,
		this->OpenRockDoorOverTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);
}



