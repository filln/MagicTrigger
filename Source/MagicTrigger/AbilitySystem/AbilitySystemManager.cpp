// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "AbilitySystemManager.h"
#include "MagicTrigger\AbilitySystem\MeleeAttack\MeleeAttackComponent.h"
#include "MagicTrigger\AbilitySystem\SevenfoldShere\SevenfoldSphereComponent.h"
#include "MagicTrigger\AbilitySystem\ThrowableRock\ThrowComponent.h"
#include "MagicTrigger\PlayerCharacter\PlayerCharacterMagicTrigger.h"
#include "MagicTrigger\CoreClasses\HUDMagicTrigger.h"
#include "MagicTrigger\UI\PlayerGUIUserWidget.h"
#include "MagicTrigger\UI\AbilitySystem\PanelAbilityUserWidget.h"
#include "MagicTrigger\UI\AbilitySystem\MeleeAbilityUserWidget.h"
#include "MagicTrigger\UI\AbilitySystem\ThrowAbilityUserWidget.h"
#include "MagicTrigger\UI\AbilitySystem\SFSphereAbilityUserWidget.h"
#include "Components\Border.h"

// Sets default values
AAbilitySystemManager::AAbilitySystemManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	MeleeAttackComponent = CreateDefaultSubobject<UMeleeAttackComponent>(TEXT("MeleeAttackComponent"));
	ThrowComponent = CreateDefaultSubobject<UThrowComponent>(TEXT("ThrowComponent"));
	SevenfoldSphereComponent = CreateDefaultSubobject<USevenfoldSphereComponent>(TEXT("SevenfoldSphereComponent"));
	SevenfoldSphereComponent->Deactivate();

	AvaliabilityAbilities = FAvaliabilityAbilitiesStruct();
	CurrentAbility = ECurrentAbility::ECA_Melee;

}

// Called when the game starts or when spawned
void AAbilitySystemManager::BeginPlay()
{
	Super::BeginPlay();

}

void AAbilitySystemManager::Attack()
{
	switch (CurrentAbility)
	{
	case ECurrentAbility::ECA_Melee:
		PlayerCharacter->MeleeAttack();
		break;
	case ECurrentAbility::ECA_Throw:

		break;
	case ECurrentAbility::ECA_SFSphere:

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
	case ECurrentAbility::ECA_SFSphere:
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
	case ECurrentAbility::ECA_SFSphere:
		HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->SFSphereBorder->SetBrushColor(HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->InactiveBorderColor);
		HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->SFSphereAbilityUserWidget->SetColorAndOpacity(HUD->PlayerGUIUserWidget->PanelAbilityUserWidget->InactiveAbilityWidgetColorAndOpacity);
		break;
	}

	CurrentAbility = InCurrentAbility;
}

void AAbilitySystemManager::StartTraceAttackLeftFoot()
{
	FTimerDelegate TmpDelegate;
	TmpDelegate.BindLambda
	(
		[=]()
	{
		TArray<AActor*> IgnoredActors;
		MeleeAttackComponent->DoAttack(
			PlayerCharacter->GetArrowLeftFootSocketLocation(),
			PlayerCharacter->GetForwardVectorArrowLeftFoot(),
			IgnoredActors,
			PlayerCharacter->GetAllDamage(),
			PlayerCharacter->PlayerController,
			this
		);
	}
	);
	GetWorld()->GetTimerManager().SetTimer(MeleeAttackComponent->AttackTimer, TmpDelegate, MeleeAttackComponent->AttackTimerDeltaTime, true);
}

void AAbilitySystemManager::StartTraceAttackRightFoot()
{
	FTimerDelegate TmpDelegate;
	TmpDelegate.BindLambda
	(
		[=]()
	{
		TArray<AActor*> IgnoredActors;
		MeleeAttackComponent->DoAttack(
			PlayerCharacter->GetArrowRightFootSocketLocation(),
			PlayerCharacter->GetForwardVectorArrowRightFoot(),
			IgnoredActors,
			PlayerCharacter->GetAllDamage(),
			PlayerCharacter->PlayerController,
			this
		);
	}
	);
	GetWorld()->GetTimerManager().SetTimer(MeleeAttackComponent->AttackTimer, TmpDelegate, MeleeAttackComponent->AttackTimerDeltaTime, true);
}

void AAbilitySystemManager::StopTraceAttackLeftFoot()
{
	MeleeAttackComponent->StopAttackTimer();
}

void AAbilitySystemManager::StopTraceAttackRightFoot()
{
	MeleeAttackComponent->StopAttackTimer();
}


