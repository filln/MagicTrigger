// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Статуя здоровья, восполняет здоровье персу.
 */


#include "LifeStatue.h"
#include "Kismet\GameplayStatics.h"
#include "Kismet\KismetMathLibrary.h"
#include "GameFramework\PlayerState.h"
#include "GameFramework\Character.h"
#include "Components\StaticMeshComponent.h"
#include "Components\PointLightComponent.h"
#include "Components\SpotLightComponent.h"
#include "Components\BoxComponent.h"
#include "Components\CapsuleComponent.h"
#include "NavAreas\NavArea_Obstacle.h"
#include "MagicTrigger\Data\CollisionChannelsMagicTrigger.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "MagicTrigger\Interfaces\PlayerCharacterInterface.h"
#include "MagicTrigger\Interfaces\PlayerStateInterface.h"
#include "MagicTrigger\Interfaces\AnimationManagerInterface.h"

ALifeStatue::ALifeStatue()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	SpeedHealing = 10;
	MaxIntensitySpotLight = 300000;
	MaxIntensityPointLight = 3000;
	MaxAttenuationRadiusPointLight = 39;
	MaxLife = 100;
	InteractionText = FText::FromStringTable("/Game/MagicTrigger/Data/ST_Interaction.ST_Interaction", "HealingTip");
	if (InteractionText.IsEmpty())
	{
		DEBUGMESSAGE("InteractionText.IsEmpty()");

	}

	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollision"));
	SetRootComponent(CapsuleCollision);
	CapsuleCollision->Mobility = EComponentMobility::Stationary;
	CapsuleCollision->SetCapsuleHalfHeight(224);
	CapsuleCollision->SetCapsuleRadius(124);
	CapsuleCollision->AreaClass = UNavArea_Obstacle::StaticClass();
	CapsuleCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	CapsuleCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CapsuleCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	CapsuleCollision->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Ignore);
	CapsuleCollision->SetCollisionResponseToChannel(ECC_Attack, ECollisionResponse::ECR_Ignore);
	CapsuleCollision->SetCollisionResponseToChannel(ECC_AttackAbility, ECollisionResponse::ECR_Ignore);
	CapsuleCollision->SetCollisionResponseToChannel(ECC_InteractNPC, ECollisionResponse::ECR_Ignore);
	CapsuleCollision->SetCollisionResponseToChannel(ECC_InteractPlayerCharacter, ECollisionResponse::ECR_Ignore);
	CapsuleCollision->SetCollisionResponseToChannel(ECC_Observe, ECollisionResponse::ECR_Overlap);

	InteractCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractCollision"));
	InteractCollision->SetupAttachment(GetRootComponent());
	InteractCollision->Mobility = GetRootComponent()->Mobility;
	FHitResult HitResultTmp = FHitResult();
	InteractCollision->SetRelativeLocation(FVector(10, 0, 10), false, &HitResultTmp, ETeleportType::None);
	InteractCollision->SetBoxExtent(FVector(100), false);
	InteractCollision->AreaClass = UNavArea_Obstacle::StaticClass();
	InteractCollision->SetCollisionObjectType(ECollisionChannel::ECC_InteractNPC);
	InteractCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	InteractCollision->SetCollisionResponseToChannel(ECC_InteractPlayerCharacter, ECollisionResponse::ECR_Overlap);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetRelativeLocation(FVector(0, 0, -99), false, &HitResultTmp, ETeleportType::None);
	Mesh->Mobility = GetRootComponent()->Mobility;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/MagicTrigger/Meshes/Items/AngelStatue/SM_Plains_Angel_Statue_01"));
	if (MeshObj.Succeeded())
	{
		Mesh->SetStaticMesh(MeshObj.Object);
	}
	else
	{
		DEBUGMESSAGE("!MeshObj.Succeeded()");
	}
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(GetRootComponent());
	PointLight->SetRelativeLocation(FVector(13, -17, 98), false, &HitResultTmp, ETeleportType::None);
	PointLight->Mobility = GetRootComponent()->Mobility;
	PointLight->IntensityUnits = ELightUnits::Unitless;
	PointLight->Intensity = MaxIntensityPointLight;
	PointLight->LightColor = FColor(255, 54, 0, 0);
	PointLight->AttenuationRadius = MaxAttenuationRadiusPointLight;
	PointLight->SetCastShadows(false);

	SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
	SpotLight->SetupAttachment(GetRootComponent());
	SpotLight->SetRelativeLocation(FVector(100, 0, 615), false, &HitResultTmp, ETeleportType::None);
	SpotLight->SetRelativeRotation(FRotator(-90, 0, 0), false, &HitResultTmp, ETeleportType::None);
	SpotLight->Mobility = GetRootComponent()->Mobility;
	SpotLight->IntensityUnits = ELightUnits::Unitless;
	SpotLight->Intensity = 0;
	SpotLight->LightColor = FColor(0, 235, 255, 0);
	SpotLight->AttenuationRadius = 16384;
	SpotLight->InnerConeAngle = 17;
	SpotLight->OuterConeAngle = 32;
	SpotLight->IndirectLightingIntensity = 0;
	SpotLight->SetCastShadows(false);

	static ConstructorHelpers::FObjectFinder<UCurveFloat> BeginInteractCurveObject(TEXT("/Game/MagicTrigger/Data/Items/AngelStatue/Curve_BeginInteract_Float"));
	if (BeginInteractCurveObject.Object) 
	{
		BeginInteractCurve = BeginInteractCurveObject.Object;
	}
	else
	{
		DEBUGMESSAGE("!BeginInteractCurve.Object");
	}
	static ConstructorHelpers::FObjectFinder<UCurveFloat> AddLifeCurveObject(TEXT("/Game/MagicTrigger/Data/Items/AngelStatue/Curve_AddLife_Float"));
	if (AddLifeCurveObject.Object) 
	{
		AddLifeCurve = AddLifeCurveObject.Object;
	}
	else
	{
		DEBUGMESSAGE("!AddLifeCurveObject.Object");
	}
	static ConstructorHelpers::FObjectFinder<UCurveFloat> AddLifePointLightCurveObject(TEXT("/Game/MagicTrigger/Data/Items/AngelStatue/Curve_AddLifePointLight_Float"));
	if (AddLifePointLightCurveObject.Object)
	{
		AddLifePointLightCurve = AddLifePointLightCurveObject.Object;
	}
	else
	{
		DEBUGMESSAGE("!AddLifePointLightCurveObject.Object");
	}
	static ConstructorHelpers::FObjectFinder<UCurveFloat> ReverseIntensityLightCurveObject(TEXT("/Game/MagicTrigger/Data/Items/AngelStatue/Curve_ReverseIntensityLight_Float"));
	if (ReverseIntensityLightCurveObject.Object) 
	{
		ReverseIntensityLightCurve = ReverseIntensityLightCurveObject.Object;
	}
	else
	{
		DEBUGMESSAGE("!ReverseIntensityLightCurveObject.Object");
	}

	BeginInteractTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("BeginInteractTimeline"));
	AddLifeTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("AddLifeTimeline"));
	ReverseIntensityLightTimeline = CreateDefaultSubobject< UTimelineComponent>(TEXT("ReverseIntensityLightTimeline"));

}

// Called when the game starts or when spawned
void ALifeStatue::BeginPlay()
{
	Super::BeginPlay();

	BeginInteractDelegate.BindUFunction(this, FName("BeginInteractTimelineFunction"));
	BeginInteractFinishedDelegate.BindUFunction(this, FName("AddLife"));
	BeginInteractTimeline->AddInterpFloat(BeginInteractCurve, BeginInteractDelegate, FName("InAlphaIntensity"), FName("InAlphaIntensity"));
	BeginInteractTimeline->SetTimelineFinishedFunc(BeginInteractFinishedDelegate);
	BeginInteractTimeline->SetTimelineLength(1);

	AddLifeDelegate.BindUFunction(this, FName("AddLifeTimelineFunction"));
	AddLifeFinishedDelegate.BindUFunction(this, FName("ReverseIntensityLight"));
	AddLifeTimeline->AddInterpFloat(AddLifeCurve, AddLifeDelegate, FName("InAlphaLife"), FName("InAlphaLife"));
	AddLifeTimeline->SetTimelineFinishedFunc(AddLifeFinishedDelegate);
	AddLifeTimeline->SetTimelineLength(1);

	ReverseIntensityLightDelegate.BindUFunction(this, FName("ReverseIntensityLightTimelineFunction"));
	ReverseIntensityLightFinishedDelegate.BindUFunction(this, FName("SetCanInteractTrue"));
	ReverseIntensityLightTimeline->AddInterpFloat(ReverseIntensityLightCurve, ReverseIntensityLightDelegate, FName("InAlphaIntensity"), FName("InAlphaIntensity"));
	ReverseIntensityLightTimeline->SetTimelineFinishedFunc(ReverseIntensityLightFinishedDelegate);
	ReverseIntensityLightTimeline->SetTimelineLength(5);

	InteractionText = FText::FromStringTable("/Game/MagicTrigger/Data/ST_Interaction.ST_Interaction", "HealingTip");
	if (InteractionText.IsEmpty())
	{
		DEBUGMESSAGE("InteractionText.IsEmpty()");

	}
	StartBeginPlayTimer_IF_Implementation();
}

void ALifeStatue::BeginInteractTimelineFunction(float InAlphaIntensity)
{	
	float NewIntensity = FMath::Lerp(0.f, MaxIntensitySpotLight, InAlphaIntensity);
	SpotLight->SetIntensity(NewIntensity);
}

void ALifeStatue::AddLifeTimelineFunction(float InAlphaLife)
{
	bool bPlayerNearStatue = UKismetMathLibrary::EqualEqual_VectorVector(PlayerCharacter->GetActorLocation(), InitialLocationCharacter, 0.1);
	if (bPlayerNearStatue)
	{
		float Life = FMath::Lerp(CurrentLife, MaxLife, InAlphaLife);
		IPlayerStateInterface::Execute_SetLife_IF(PlayerCharacter->GetPlayerState(), Life);

		float AlphaIntensity = AddLifePointLightCurve->GetFloatValue(AddLifeTimeline->GetPlaybackPosition());
		float Prc = CurrentLife / MaxLife;
		float MinIntensityPointLight = MaxIntensityPointLight * Prc;
		float NewIntensity = FMath::Lerp(MaxIntensityPointLight, MinIntensityPointLight, AlphaIntensity);
		PointLight->SetIntensity(NewIntensity);
		float MinAttenuationRadiusPointLight = MaxAttenuationRadiusPointLight * Prc;
		float NewAttenuationRadius = FMath::Lerp(MaxAttenuationRadiusPointLight, MinAttenuationRadiusPointLight, AlphaIntensity);
		PointLight->AttenuationRadius = NewAttenuationRadius;

	}
	else
	{
		StopAddingLife();
		ReverseIntensityLight();
	}
}

void ALifeStatue::ReverseIntensityLightTimelineFunction(float InAlphaIntensity)
{
	//Reverse with ReverseFromEnd() from B to A.

	float NewIntensitySpotLight = FMath::Lerp(0.f, MaxIntensitySpotLight, InAlphaIntensity);
	SpotLight->SetIntensity(NewIntensitySpotLight);

	float NewIntensityPointLight = FMath::Lerp(MaxIntensityPointLight, CurrentIntensityPointLight, InAlphaIntensity);
	PointLight->SetIntensity(NewIntensityPointLight);
}

void ALifeStatue::SetCanInteractTrue()
{
	IAnimationManagerInterface::Execute_SetCanInteract_IF(AnimationManager, true);
}

float ALifeStatue::GetLife() const
{
	return IPlayerStateInterface::Execute_GetLife_IF(PlayerCharacter->GetPlayerState());
}

float ALifeStatue::GetMaxLife() const
{
	return IPlayerStateInterface::Execute_GetMaxLife_IF(PlayerCharacter->GetPlayerState());
}

void ALifeStatue::AddLife()
{
	CurrentLife = GetLife();
	if (CurrentLife >= MaxLife)
	{
		ReverseIntensityLight();
		return;
	}

	float NewRate = 1 / ((MaxLife - CurrentLife) / SpeedHealing);
	AddLifeTimeline->SetPlayRate(NewRate);
	AddLifeTimeline->PlayFromStart();
}

void ALifeStatue::ReverseIntensityLight()
{
	CurrentIntensityPointLight = PointLight->Intensity;
	ReverseIntensityLightTimeline->ReverseFromEnd();
}

void ALifeStatue::StopAddingLife()
{
	AddLifeTimeline->Stop();
}

void ALifeStatue::StartBeginPlayTimer_IF_Implementation()
{
	if (!GetWorld())
	{
		DEBUGMESSAGE("!GetWorld()");
		return;
	}
	FTimerDelegate BeginPlayDelegate;
	BeginPlayDelegate.BindLambda
	(
		[=]
	()
	{
		if (UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
		{
			PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
			GetWorld()->GetTimerManager().ClearTimer(BeginPlayTimer);
		}
		else
		{
			DEBUGMESSAGE("!UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)");
		}
	}
	);
	GetWorld()->GetTimerManager().SetTimer(BeginPlayTimer, BeginPlayDelegate, 0.2, true);
}

FText ALifeStatue::GetInteractionText_IF_Implementation() const
{
	return InteractionText;
}

void ALifeStatue::Interact_IF_Implementation()
{
	/**
	 * Check all variables.
	 */
	//////////////////////////////////////////////////////////////////////////
	if (!PlayerCharacter)
	{
		DEBUGMESSAGE("!PlayerCharacter");
		return;
	}
	if (!IsInterfaceImplementedBy<IAnimationManagerInterface>(PlayerCharacter))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IAnimationManagerInterface>(!PlayerCharacter)");
		return;
	}
	AnimationManager = IAnimationManagerInterface::Execute_GetAnimationManagerComponent_IF(PlayerCharacter);
	if (!AnimationManager)
	{
		DEBUGMESSAGE("!AnimationManager");
		return;
	}
	if (!IsInterfaceImplementedBy<IAnimationManagerInterface>(AnimationManager))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IAnimationManagerInterface>(AnimationManager)");
		return;
	}
	if (!PlayerCharacter->GetPlayerState())
	{
		DEBUGMESSAGE("!PlayerCharacter->GetPlayerState()");
		return;
	}
	if (!IsInterfaceImplementedBy<IPlayerStateInterface>(PlayerCharacter->GetPlayerState()))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IPlayerStateInterface>(PlayerCharacter->GetPlayerState())");
		return;
	}
	//////////////////////////////////////////////////////////////////////////

	//Begin Interact.
	MaxLife = GetMaxLife();
	InitialLocationCharacter = PlayerCharacter->GetActorLocation();
	IAnimationManagerInterface::Execute_SetCanInteract_IF(AnimationManager, false);
	BeginInteractTimeline->PlayFromStart();	
}

void ALifeStatue::IsObserved_Implementation()
{
	Mesh->SetRenderCustomDepth(true);
}

void ALifeStatue::IsNotObserved_Implementation()
{
	Mesh->SetRenderCustomDepth(false);
}