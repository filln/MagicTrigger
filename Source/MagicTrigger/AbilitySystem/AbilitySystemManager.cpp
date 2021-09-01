// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "AbilitySystemManager.h"
#include "MagicTrigger/AbilitySystem/MeleeAttack/MeleeAttackComponent.h"
#include "MagicTrigger/AbilitySystem/SevenfoldSphere/SevenfoldSphereComponent.h"
#include "MagicTrigger/AbilitySystem/Throw/ThrowComponent.h"
#include "MagicTrigger/PlayerCharacter/PlayerCharacterMagicTrigger.h"
#include "MagicTrigger/PlayerCharacter/AnimationManagerComponent.h"
#include "MagicTrigger/CoreClasses/HUDMagicTrigger.h"
#include "MagicTrigger/UI/PlayerGUIUserWidget.h"
#include "MagicTrigger/UI/AbilitySystem/PanelAbilityUserWidget.h"
#include "MagicTrigger/UI/AbilitySystem/MeleeAbilityUserWidget.h"
#include "MagicTrigger/UI/AbilitySystem/ThrowAbilityUserWidget.h"
#include "MagicTrigger/UI/AbilitySystem/SFSphereAbilityUserWidget.h"
#include "MagicTrigger/Data/DebugMessage.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAbilitySystemManager::AAbilitySystemManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	MeleeAttackComponent = CreateDefaultSubobject<UMeleeAttackComponent>(TEXT("MeleeAttackComponent"));
	ThrowComponent = CreateDefaultSubobject<UThrowComponent>(TEXT("ThrowComponent"));
	SevenfoldSphereComponent = CreateDefaultSubobject<USevenfoldSphereComponent>(TEXT("SevenfoldSphereComponent"));
	//SevenfoldSphereComponent->Deactivate();

	AvaliabilityAbilities = FAvaliabilityAbilitiesStruct();
	CurrentAbility = ECurrentAbility::ECA_Melee;

}

// Called when the game starts or when spawned
void AAbilitySystemManager::BeginPlay()
{
	Super::BeginPlay();
	if (!PlayerCharacter)
	{
		PlayerCharacter = Cast<APlayerCharacterMagicTrigger>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (!PlayerCharacter)
		{
			DEBUGMESSAGE("!PlayerCharacter");
		}
		else
		{
			MeleeAttackComponent->IgnoredActors.Add(PlayerCharacter);
		}
	}
	else
	{
		MeleeAttackComponent->IgnoredActors.Add(PlayerCharacter);
	}

}

void AAbilitySystemManager::Attack()
{
	switch (CurrentAbility)
	{
	case ECurrentAbility::ECA_Melee:
		UseMeleeAbility();
		break;
	case ECurrentAbility::ECA_Throw:
		ThrowComponent->Use();
		break;
	case ECurrentAbility::ECA_SSphere:
		SevenfoldSphereComponent->Use();
		break;
	}
}

void AAbilitySystemManager::SetCurrentAbility(ECurrentAbility InCurrentAbility)
{
	if (CurrentAbility == InCurrentAbility)
	{
		return;
	}

	switch (InCurrentAbility)
	{
	case ECurrentAbility::ECA_Melee:
		if (!AvaliabilityAbilities.bMelee)
		{
			return;
		}
		HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->MeleeBorder->SetBrushColor(HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->ActiveBorderColor);
		HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->MeleeAbilityUserWidget->SetColorAndOpacity(HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->ActiveAbilityWidgetColorAndOpacity);
		break;
	case ECurrentAbility::ECA_Throw:
		if (!AvaliabilityAbilities.bThrow)
		{
			return;
		}
		HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->ThrowBorder->SetBrushColor(HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->ActiveBorderColor);
		HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->ThrowAbilityUserWidget->SetColorAndOpacity(HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->ActiveAbilityWidgetColorAndOpacity);
		break;
	case ECurrentAbility::ECA_SSphere:
		if (!AvaliabilityAbilities.bSFSphere)
		{
			return;
		}
		HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->SFSphereBorder->SetBrushColor(HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->ActiveBorderColor);
		HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->SFSphereAbilityUserWidget->SetColorAndOpacity(HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->ActiveAbilityWidgetColorAndOpacity);
		break;
	}

	//Убрать выделение прошлой абилки.
	switch (CurrentAbility)
	{
	case ECurrentAbility::ECA_Melee:
		HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->MeleeBorder->SetBrushColor(HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->InactiveBorderColor);
		HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->MeleeAbilityUserWidget->SetColorAndOpacity(HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->InactiveAbilityWidgetColorAndOpacity);
		break;
	case ECurrentAbility::ECA_Throw:
		HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->ThrowBorder->SetBrushColor(HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->InactiveBorderColor);
		HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->ThrowAbilityUserWidget->SetColorAndOpacity(HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->InactiveAbilityWidgetColorAndOpacity);
		break;
	case ECurrentAbility::ECA_SSphere:
		HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->SFSphereBorder->SetBrushColor(HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->InactiveBorderColor);
		HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->SFSphereAbilityUserWidget->SetColorAndOpacity(HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->InactiveAbilityWidgetColorAndOpacity);
		break;
	}

	CurrentAbility = InCurrentAbility;
}

APlayerCharacterMagicTrigger* AAbilitySystemManager::GetPlayerCharacter() const
{
	return PlayerCharacter;
}

APlayerController* AAbilitySystemManager::GetPlayerController() const
{
	return PlayerCharacter->GetPlayerController();
}

void AAbilitySystemManager::UseMeleeAbility()
{
	PlayerCharacter->AnimationManagerComponent->MeleeAttackAnimation();
}

void AAbilitySystemManager::StartTraceAttackLeftFoot()
{
	//DEBUGMESSAGE("StartTraceAttackLeftFoot");
	MeleeAttackComponent->StartAttackTimer(
		PlayerCharacter->GetArrowLeftFootSocketLocation(),
		PlayerCharacter->GetForwardVectorArrowLeftFoot(),
		PlayerCharacter->GetAllDamage(),
		PlayerCharacter->PlayerController,
		PlayerCharacter
	);
}

void AAbilitySystemManager::StartTraceAttackRightFoot()
{
	//DEBUGMESSAGE("StartTraceAttackRightFoot");
	MeleeAttackComponent->StartAttackTimer(
		PlayerCharacter->GetArrowRightFootSocketLocation(),
		PlayerCharacter->GetForwardVectorArrowRightFoot(),
		PlayerCharacter->GetAllDamage(),
		PlayerCharacter->PlayerController,
		PlayerCharacter
	);
}

void AAbilitySystemManager::StopTraceAttackLeftFoot()
{
	//DEBUGMESSAGE("StopTraceAttackLeftFoot");
	MeleeAttackComponent->StopAttackTimer();
}

void AAbilitySystemManager::StopTraceAttackRightFoot()
{
	//DEBUGMESSAGE("StopTraceAttackRightFoot");
	MeleeAttackComponent->StopAttackTimer();
}

void AAbilitySystemManager::UseThrowAbility()
{
	PlayerCharacter->AnimationManagerComponent->ThrowAnimation();
}

void AAbilitySystemManager::IncreaseCountOfThrowableItem()
{
	ThrowComponent->IncreaseCountOfThrowableItem();
}

void AAbilitySystemManager::SetCountOfThrowableItemText()
{
	FString CountString = FString::FromInt(ThrowComponent->GetCountOfThrowableItem());
	HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->ThrowAbilityUserWidget->CountText->SetText(FText::FromString(CountString));
}

void AAbilitySystemManager::SpawnThrowableItem()
{
	ThrowComponent->SpawnThrowableItem();
}

void AAbilitySystemManager::ThrowThrowableItem()
{
	ThrowComponent->Throw();
}

FTransform AAbilitySystemManager::GetSocketTransform(FName& SocketName) const
{
	return PlayerCharacter->GetSocketTransform(SocketName);
}

USkeletalMeshComponent* AAbilitySystemManager::GetPlayerCharacterMesh() const
{
	if (!PlayerCharacter)
	{
		return nullptr;
	}
	return PlayerCharacter->GetMesh();
}

AActor* AAbilitySystemManager::GetObservedActor() const
{
	return PlayerCharacter->GetObservedActor();
}

FVector AAbilitySystemManager::GetPlayerCharacterForwardVector() const
{
	return PlayerCharacter->GetActorForwardVector();
}

FVector AAbilitySystemManager::GetPlayerCharacterUpVector() const
{
	return PlayerCharacter->GetActorUpVector();
}

FVector AAbilitySystemManager::GetPlayerCharacterVelocity() const
{
	return PlayerCharacter->GetVelocity();
}

void AAbilitySystemManager::SwitchOnSSphereAbility()
{
	SevenfoldSphereComponent->Activate();
	AvaliabilityAbilities.bSFSphere = true;
}

void AAbilitySystemManager::UseSSphereAbility()
{
	PlayerCharacter->AnimationManagerComponent->SpawnSSphereAnimation();
}

void AAbilitySystemManager::SpawnSSphere()
{
	SevenfoldSphereComponent->SpawnSSphere();
}

void AAbilitySystemManager::SetCountOfSpheresText()
{
	FString CountString = FString::FromInt(SevenfoldSphereComponent->GetCountOfSpheres());
	HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->SFSphereAbilityUserWidget->CountText->SetText(FText::FromString(CountString));
}

