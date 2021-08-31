// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "PickUpSSphere.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "MagicTrigger/Data/CollisionChannelsMagicTrigger.h"
#include "MagicTrigger/Data/DebugMessage.h"
#include "MagicTrigger/PlayerCharacter/PlayerCharacterMagicTrigger.h"
#include "Materials/MaterialInterface.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
APickUpSSphere::APickUpSSphere()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MoveUpOverTime = 0.5;
	MoveToCharacterOverTime = 1;
	FirstMaxEmissive = 2;
	SecondMaxEmissive = 3;
	MaxScale = 1.5;
	MinOpacity = 0.6;
	EmissiveMultiplierName = FName(TEXT("EmissiveMultiplier"));
	OpacityName = FName(TEXT("Opacity"));
	MoveUpHeigh = 200;
	MoveLittleSpheresHorizontalOverTime = 2;
	SpotLightIntensity = 20000;
	SpotLightAttenuationRadius = 150;
	SpotLightInnerConeAngle = 12;
	SpotLightOuterConeAngle = 12;
	SpotLightColor = FLinearColor(255, 212, 0);
	LittleSpheresDownLocationZ = -19;
	bWasOverlapLittleSphereCentralPointCollision = false;
	IncreaseEmissiveCurveLength = 0.5;
	IncreaseScaleAndEmissiveCurveLength = 2;
	DecreaseOpacityCurveLength = 1;
	MoveComponentToCounter = 0;

	/**
	 * SwitchOnCollision
	 */
	SwitchOnCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("SwitchOnCollision"));
	SetRootComponent(SwitchOnCollision);
	SwitchOnCollision->SetWorldScale3D(FVector(10));
	SwitchOnCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SwitchOnCollision->SetCollisionObjectType(ECC_InteractNPC);
	SwitchOnCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SwitchOnCollision->SetCollisionResponseToChannel(ECC_InteractPlayerCharacter, ECollisionResponse::ECR_Overlap);
	SwitchOnCollision->OnComponentBeginOverlap.AddDynamic(this, &APickUpSSphere::SwitchOn);

	/**
	 * LittleSphereCentralPoint
	 */
	LittleSpheresCentralPoint = CreateDefaultSubobject<UBillboardComponent>(TEXT("LittleSphereCentralPoint"));
	LittleSpheresCentralPoint->SetupAttachment(GetRootComponent());

	/**
	 * LittleSpherePoint1 - LittleSpherePoint7
	 */

	LittleSpherePoint1 = CreateDefaultSubobject<UBillboardComponent>(TEXT("LittleSpherePoint1"));
	SetupLittleSpherePoints(LittleSpherePoint1, FVector(-47.6, 80.7, 0));
	LittleSpherePoint2 = CreateDefaultSubobject<UBillboardComponent>(TEXT("LittleSpherePoint2"));
	SetupLittleSpherePoints(LittleSpherePoint2, FVector(-0.1, -86.3, 0));
	LittleSpherePoint3 = CreateDefaultSubobject<UBillboardComponent>(TEXT("LittleSpherePoint3"));
	SetupLittleSpherePoints(LittleSpherePoint3, FVector(86.4, 18.3, 0));
	LittleSpherePoint4 = CreateDefaultSubobject<UBillboardComponent>(TEXT("LittleSpherePoint4"));
	SetupLittleSpherePoints(LittleSpherePoint4, FVector(-95.6, 14.9, 0));
	LittleSpherePoint5 = CreateDefaultSubobject<UBillboardComponent>(TEXT("LittleSpherePoint5"));
	SetupLittleSpherePoints(LittleSpherePoint5, FVector(46.9, 79.3, 0));
	LittleSpherePoint6 = CreateDefaultSubobject<UBillboardComponent>(TEXT("LittleSpherePoint6"));
	SetupLittleSpherePoints(LittleSpherePoint6, FVector(-71.4, -63.8, 0));
	LittleSpherePoint7 = CreateDefaultSubobject<UBillboardComponent>(TEXT("LittleSpherePoint7"));
	SetupLittleSpherePoints(LittleSpherePoint7, FVector(73.5, -60.5, 0));

	/**
	 * SpotLight1 - SpotLight7
	 */
	SpotLight1 = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight1"));
	SetupSpotLights(SpotLight1, LittleSpherePoint1, FRotator(0, 302, 0));
	SpotLight2 = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight2"));
	SetupSpotLights(SpotLight2, LittleSpherePoint2, FRotator(0, 90, 0));
	SpotLight3 = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight3"));
	SetupSpotLights(SpotLight3, LittleSpherePoint3, FRotator(0, 191, 0));
	SpotLight4 = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight4"));
	SetupSpotLights(SpotLight4, LittleSpherePoint4, FRotator(0, 353, 0));
	SpotLight5 = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight5"));
	SetupSpotLights(SpotLight5, LittleSpherePoint5, FRotator(0, 238, 0));
	SpotLight6 = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight6"));
	SetupSpotLights(SpotLight6, LittleSpherePoint6, FRotator(0, 43, 0));
	SpotLight7 = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight7"));
	SetupSpotLights(SpotLight7, LittleSpherePoint7, FRotator(0, 140, 0));

	/**
	 * LittleSphere1 - LittleSphere7
	 */
	LittleSphere1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LittleSphere1"));
	SetupLittleSpheres(LittleSphere1);
	LittleSphere2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LittleSphere2"));
	SetupLittleSpheres(LittleSphere2);
	LittleSphere3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LittleSphere3"));
	SetupLittleSpheres(LittleSphere3);
	LittleSphere4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LittleSphere4"));
	SetupLittleSpheres(LittleSphere4);
	LittleSphere5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LittleSphere5"));
	SetupLittleSpheres(LittleSphere5);
	LittleSphere6 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LittleSphere6"));
	SetupLittleSpheres(LittleSphere6);
	LittleSphere7 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LittleSphere7"));
	SetupLittleSpheres(LittleSphere7);

	/**
	 * LittleSphereCentralPointCollision
	 */
	LittleSphereCentralPointCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("LittleSphereCentralPointCollision"));
	LittleSphereCentralPointCollision->SetupAttachment(LittleSpheresCentralPoint);
	LittleSphereCentralPointCollision->SetBoxExtent(FVector(110, 110, 10), false);
	LittleSphereCentralPointCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	LittleSphereCentralPointCollision->SetCollisionObjectType(ECC_InteractNPC);
	LittleSphereCentralPointCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	LittleSphereCentralPointCollision->SetCollisionResponseToChannel(ECC_InteractPlayerCharacter, ECollisionResponse::ECR_Overlap);
	LittleSphereCentralPointCollision->OnComponentBeginOverlap.AddDynamic(this, &APickUpSSphere::SwitchOnSpotLight);
	LittleSphereCentralPointCollision->OnComponentEndOverlap.AddDynamic(this, &APickUpSSphere::SwitchOffSpotLight);

	/**
	 * BigSphere
	 */
	BigSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BigSphere"));
	BigSphere->SetupAttachment(GetRootComponent());
	BigSphere->SetRelativeScale3D(FVector(0.35f));
	BigSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/MagicTrigger/Meshes/AttackAbilities/SM_AttackAbilitySphere"));
	if (MeshObj.Succeeded())
	{
		BigSphere->SetStaticMesh(MeshObj.Object);
		LittleSphere1->SetStaticMesh(MeshObj.Object);
		LittleSphere2->SetStaticMesh(MeshObj.Object);
		LittleSphere3->SetStaticMesh(MeshObj.Object);
		LittleSphere4->SetStaticMesh(MeshObj.Object);
		LittleSphere5->SetStaticMesh(MeshObj.Object);
		LittleSphere6->SetStaticMesh(MeshObj.Object);
		LittleSphere7->SetStaticMesh(MeshObj.Object);
	}
	else
	{
		DEBUGMESSAGE("!MeshObj.Succeeded()");
	}

	/**
	 * Material
	 */
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> SourceMaterialOpaqueInterfaceObj(TEXT("/Game/MagicTrigger/Materials/AbilitySystem/M_AttackAbility"));
	if (SourceMaterialOpaqueInterfaceObj.Succeeded())
	{
		SourceMaterialOpaque = SourceMaterialOpaqueInterfaceObj.Object;
		BigSphere->SetMaterial(0, SourceMaterialOpaque);
		LittleSphere1->SetMaterial(0, SourceMaterialOpaque);
		LittleSphere2->SetMaterial(0, SourceMaterialOpaque);
		LittleSphere3->SetMaterial(0, SourceMaterialOpaque);
		LittleSphere4->SetMaterial(0, SourceMaterialOpaque);
		LittleSphere5->SetMaterial(0, SourceMaterialOpaque);
		LittleSphere6->SetMaterial(0, SourceMaterialOpaque);
		LittleSphere7->SetMaterial(0, SourceMaterialOpaque);
	}
	else
	{
		DEBUGMESSAGE("!SourceMaterialOpaqueInterfaceObj.Succeeded()");
	}
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> SourceMaterialTranslucentInterfaceObj(TEXT("/Game/MagicTrigger/Materials/AbilitySystem/M_AttackAbility_Translucent"));
	if (SourceMaterialTranslucentInterfaceObj.Succeeded())
	{
		SourceMaterialTranslucent = SourceMaterialTranslucentInterfaceObj.Object;
	}
	else
	{
		DEBUGMESSAGE("!SourceMaterialTranslucentInterfaceObj.Succeeded()");
	}

	/**
	 * RotatingMovementComponent
	 */
	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
	RotatingMovementComponent->RotationRate.Yaw = 0;

	/**
	 * Curves
	 */
	static ConstructorHelpers::FObjectFinder<UCurveFloat> IncreaseEmissiveCurveObject(TEXT("/Game/MagicTrigger/Data/AttackAbilities/SevenfoldSphere/Curve_IncreaseEmissive_Float"));
	if (IncreaseEmissiveCurveObject.Object)
	{
		IncreaseEmissiveCurve = IncreaseEmissiveCurveObject.Object;
	}
	else
	{
		DEBUGMESSAGE("!IncreaseEmissiveCurveObject.Object");
	}
	static ConstructorHelpers::FObjectFinder<UCurveFloat> IncreaseScaleAndEmissiveCurveObject(TEXT("/Game/MagicTrigger/Data/AttackAbilities/SevenfoldSphere/Curve_IncreaseScaleAndEmissive_Float"));
	if (IncreaseScaleAndEmissiveCurveObject.Object)
	{
		IncreaseScaleAndEmissiveCurve = IncreaseScaleAndEmissiveCurveObject.Object;
	}
	else
	{
		DEBUGMESSAGE("!IncreaseScaleAndEmissiveCurveObject.Object");
	}
	static ConstructorHelpers::FObjectFinder<UCurveFloat> DecreaseOpacityCurveObject(TEXT("/Game/MagicTrigger/Data/AttackAbilities/SevenfoldSphere/Curve_DecreaseOpacity_Float"));
	if (DecreaseOpacityCurveObject.Object)
	{
		DecreaseOpacityCurve = DecreaseOpacityCurveObject.Object;
	}
	else
	{
		DEBUGMESSAGE("!DecreaseOpacityCurveObject.Object");
	}

	/**
	 * Timelines
	 */
	IncreaseEmissiveTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("IncreaseEmissiveTimeline"));
	IncreaseScaleAndEmissiveTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("IncreaseScaleAndEmissiveTimeline"));
	IncreaseEmissiveLittleSpheresTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("IncreaseEmissiveLittleSpheresTimeline"));
	DecreaseEmissiveLittleSpheresTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DecreaseEmissiveLittleSpheresTimeline"));
	DecreaseOpacityTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DecreaseOpacityTimeline"));
	DecreaseScaleAndOpacityTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DecreaseScaleAndOpacityTimeline"));

	IncreaseEmissiveTimeline->SetTimelineLength(IncreaseEmissiveCurveLength);
	IncreaseScaleAndEmissiveTimeline->SetTimelineLength(IncreaseScaleAndEmissiveCurveLength);
	IncreaseEmissiveLittleSpheresTimeline->SetTimelineLength(IncreaseEmissiveCurveLength);
	DecreaseEmissiveLittleSpheresTimeline->SetTimelineLength(IncreaseEmissiveCurveLength);
	DecreaseOpacityTimeline->SetTimelineLength(DecreaseOpacityCurveLength);
	DecreaseScaleAndOpacityTimeline->SetTimelineLength(DecreaseOpacityCurveLength);
}

void APickUpSSphere::BeginPlay()
{
	Super::BeginPlay();

	BigSphereMaterial = BigSphere->CreateAndSetMaterialInstanceDynamicFromMaterial(0, SourceMaterialOpaque);
	LittleSpheresMaterial = LittleSphere1->CreateAndSetMaterialInstanceDynamicFromMaterial(0, SourceMaterialOpaque);
	LittleSphere2->SetMaterial(0, LittleSpheresMaterial);
	LittleSphere3->SetMaterial(0, LittleSpheresMaterial);
	LittleSphere4->SetMaterial(0, LittleSpheresMaterial);
	LittleSphere5->SetMaterial(0, LittleSpheresMaterial);
	LittleSphere6->SetMaterial(0, LittleSpheresMaterial);
	LittleSphere7->SetMaterial(0, LittleSpheresMaterial);
}

void APickUpSSphere::SetupLittleSpherePoints(UBillboardComponent* InLittleSpherePoint, FVector InLocation)
{
	FHitResult HitResultTmp = FHitResult();
	InLittleSpherePoint->SetupAttachment(LittleSpheresCentralPoint);
	InLittleSpherePoint->SetRelativeLocation(InLocation, false, &HitResultTmp, ETeleportType::None);
}

void APickUpSSphere::SetupSpotLights(USpotLightComponent* InSpotLight, UBillboardComponent* InParentComponent, FRotator InRotation)
{
	FHitResult HitResultTmp = FHitResult();
	InSpotLight->SetupAttachment(InParentComponent);
	InSpotLight->SetRelativeRotation(InRotation, false, &HitResultTmp, ETeleportType::None);
	InSpotLight->AttenuationRadius = SpotLightAttenuationRadius;
	InSpotLight->InnerConeAngle = SpotLightInnerConeAngle;
	InSpotLight->OuterConeAngle = SpotLightOuterConeAngle;
	InSpotLight->SetIntensity(0);
	InSpotLight->SetLightColor(SpotLightColor, false);
}

void APickUpSSphere::SetupLittleSpheres(UStaticMeshComponent* InLittleSphere)
{
	InLittleSphere->SetupAttachment(LittleSpheresCentralPoint);
	InLittleSphere->SetRelativeScale3D(FVector(2.5f));
	InLittleSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APickUpSSphere::SwitchOnSpotLight(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bWasOverlapLittleSphereCentralPointCollision)
	{
		return;
	}
	for (auto Spot : SpotLightArray)
	{
		Spot->SetIntensity(SpotLightIntensity);
	}
	bWasOverlapLittleSphereCentralPointCollision = true;
}

void APickUpSSphere::SwitchOffSpotLight(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	for (auto Spot : SpotLightArray)
	{
		Spot->SetIntensity(0);
	}
}

void APickUpSSphere::SwitchOn(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PlayerCharacter = Cast<APlayerCharacterMagicTrigger>(OtherActor);
	if (!PlayerCharacter)
	{
		return;
		DEBUGMESSAGE("!PlayerCharacter");
	}
	RotatingMovementComponent->RotationRate.Yaw = 180;
	SetEnableCharacterMovement(false);
	IncreaseEmissive();

}

void APickUpSSphere::SetEnableCharacterMovement(bool bInEnable)
{
	PlayerCharacter->SetEnableMovement(bInEnable);
}

void APickUpSSphere::IncreaseEmissive()
{
	FOnTimelineFloat UpdateDelegate;
	UpdateDelegate.BindUFunction(this, FName("IncreaseEmissiveTimelineUpdate"));
	FOnTimelineEvent FinishedDelegate;
	FinishedDelegate.BindUFunction(this, FName("MoveUp"));
	IncreaseEmissiveTimeline->AddInterpFloat(IncreaseEmissiveCurve, UpdateDelegate, FName("InAlpha"), FName("InAlpha"));
	IncreaseEmissiveTimeline->SetTimelineFinishedFunc(FinishedDelegate);
	IncreaseEmissiveTimeline->PlayFromStart();
}

void APickUpSSphere::IncreaseEmissiveTimelineUpdate(float InAlpha)
{
	if (!BigSphereMaterial)
	{
		DEBUGMESSAGE("!Material");
		return;
	}
	float Value = FMath::Lerp(0.0f, FirstMaxEmissive, InAlpha);
	BigSphereMaterial->SetScalarParameterValue(EmissiveMultiplierName, Value);
}

void APickUpSSphere::MoveUp()
{
	RotatingMovementComponent->RotationRate.Yaw = 0;
	FVector TargetRelativeLocation = FVector(GetActorLocation().X, GetActorLocation().Y, PlayerCharacter->GetActorLocation().Z + MoveUpHeigh);
	FRotator TargetRelativeRotation = FRotator(0, 180, 0);
	FLatentActionInfo LatentInfo = FLatentActionInfo();
	LatentInfo.CallbackTarget = this;
	LatentInfo.UUID = ++MoveComponentToCounter;
	UKismetSystemLibrary::MoveComponentTo
	(
		GetRootComponent(),
		TargetRelativeLocation,
		TargetRelativeRotation,
		false,
		false,
		MoveUpOverTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APickUpSSphere::MoveToCharacter, MoveUpOverTime, false);
}


void APickUpSSphere::MoveToCharacter()
{
	FVector TargetRelativeLocation = FVector(PlayerCharacter->GetActorLocation().X, PlayerCharacter->GetActorLocation().Y, GetActorLocation().Z);
	FRotator TargetRelativeRotation = FRotator(0, 360, 0);
	FLatentActionInfo LatentInfo = FLatentActionInfo();
	LatentInfo.CallbackTarget = this;
	LatentInfo.UUID = ++MoveComponentToCounter;
	UKismetSystemLibrary::MoveComponentTo
	(
		GetRootComponent(),
		TargetRelativeLocation,
		TargetRelativeRotation,
		false,
		false,
		MoveToCharacterOverTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APickUpSSphere::IncreaseScaleAndEmissive, MoveToCharacterOverTime, false);
}

void APickUpSSphere::IncreaseScaleAndEmissive()
{
	RotatingMovementComponent->RotationRate.Yaw = 180;
	InitialScale = GetActorScale3D();

	FOnTimelineFloat UpdateDelegate;
	UpdateDelegate.BindUFunction(this, FName("IncreaseScaleAndEmissiveTimelineUpdate"));
	FOnTimelineEvent FinishedDelegate;
	FinishedDelegate.BindUFunction(this, FName("MoveLittleSpheresOutside"));
	IncreaseScaleAndEmissiveTimeline->AddInterpFloat(IncreaseScaleAndEmissiveCurve, UpdateDelegate, FName("InAlpha"), FName("InAlpha"));
	IncreaseScaleAndEmissiveTimeline->SetTimelineFinishedFunc(FinishedDelegate);
	IncreaseScaleAndEmissiveTimeline->PlayFromStart();
}

void APickUpSSphere::IncreaseScaleAndEmissiveTimelineUpdate(float InAlpha)
{
	float Value = FMath::Lerp(0.f, SecondMaxEmissive, InAlpha);
	BigSphereMaterial->SetScalarParameterValue(EmissiveMultiplierName, Value);

	float ScaleMultiplier = FMath::Lerp(1.f, MaxScale, InAlpha);
	FVector NewScale = InitialScale * ScaleMultiplier;
	SetActorScale3D(NewScale);
}

void APickUpSSphere::MoveLittleSpheresOutside()
{
	LittleSpheresArray =
	{
			LittleSphere1,
			LittleSphere2,
			LittleSphere3,
			LittleSphere4,
			LittleSphere5,
			LittleSphere6,
			LittleSphere7
	};

	TArray<UBillboardComponent*> PointsArray =
	{
			LittleSpherePoint1,
			LittleSpherePoint2,
			LittleSpherePoint3,
			LittleSpherePoint4,
			LittleSpherePoint5,
			LittleSpherePoint6,
			LittleSpherePoint7
	};
	int32 Index;
	MoveComponentToCounter++;
	for (Index = 0; Index < LittleSpheresArray.Num(); Index++)
	{
		FVector TargetRelativeLocation = PointsArray[Index]->GetRelativeLocation();
		FRotator TargetRelativeRotation = FRotator(0);
		FLatentActionInfo LatentInfo = FLatentActionInfo();
		LatentInfo.CallbackTarget = this;
		LatentInfo.UUID = Index + MoveComponentToCounter;

		UKismetSystemLibrary::MoveComponentTo
		(
			LittleSpheresArray[Index],
			TargetRelativeLocation,
			TargetRelativeRotation,
			false,
			false,
			MoveLittleSpheresHorizontalOverTime,
			false,
			EMoveComponentAction::Move,
			LatentInfo
		);
	}
	MoveComponentToCounter += Index;
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APickUpSSphere::IncreaseEmissiveLittleSpheres, MoveLittleSpheresHorizontalOverTime, false);
}

void APickUpSSphere::IncreaseEmissiveLittleSpheres()
{
	FOnTimelineFloat UpdateDelegate;
	UpdateDelegate.BindUFunction(this, FName("IncreaseEmissiveLittleSpheresTimelineUpdate"));
	FOnTimelineEvent FinishedDelegate;
	FinishedDelegate.BindUFunction(this, FName("MoveLittleSpheresVertical"));
	IncreaseEmissiveLittleSpheresTimeline->AddInterpFloat(IncreaseEmissiveCurve, UpdateDelegate, FName("InAlpha"), FName("InAlpha"));
	IncreaseEmissiveLittleSpheresTimeline->SetTimelineFinishedFunc(FinishedDelegate);
	IncreaseEmissiveLittleSpheresTimeline->PlayFromStart();
}

void APickUpSSphere::IncreaseEmissiveLittleSpheresTimelineUpdate(float InAlpha)
{
	float Value = FMath::Lerp(0.f, FirstMaxEmissive, InAlpha);
	LittleSpheresMaterial->SetScalarParameterValue(EmissiveMultiplierName, Value);
}

void APickUpSSphere::MoveLittleSpheresVertical()
{
	SpotLightArray =
	{
		SpotLight1,
		SpotLight2,
		SpotLight3,
		SpotLight4,
		SpotLight5,
		SpotLight6,
		SpotLight7
	};

	//Move Down
	FVector TargetRelativeLocation = FVector(0, 0, LittleSpheresDownLocationZ);
	FRotator TargetRelativeRotation = FRotator(0);
	FLatentActionInfo LatentInfo = FLatentActionInfo();
	LatentInfo.CallbackTarget = this;
	LatentInfo.UUID = ++MoveComponentToCounter;
	UKismetSystemLibrary::MoveComponentTo
	(
		LittleSpheresCentralPoint,
		TargetRelativeLocation,
		TargetRelativeRotation,
		false,
		false,
		MoveToCharacterOverTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);

	//Move Up
	FTimerHandle TmpTimerMoveUp;
	FTimerDelegate TmpDelegate;
	TmpDelegate.BindLambda
	(
		[=]()
	{
		FVector TargetRelativeLocation = FVector(0);
		FRotator TargetRelativeRotation = FRotator(0);
		FLatentActionInfo LatentInfo = FLatentActionInfo();
		LatentInfo.CallbackTarget = this;
		LatentInfo.UUID = ++MoveComponentToCounter;
		UKismetSystemLibrary::MoveComponentTo
		(
			LittleSpheresCentralPoint,
			TargetRelativeLocation,
			TargetRelativeRotation,
			false,
			false,
			MoveToCharacterOverTime,
			false,
			EMoveComponentAction::Move,
			LatentInfo
		);
		FTimerHandle TmpTimerDecreaseEmissiveLittleSpheres;
		GetWorld()->GetTimerManager().SetTimer(TmpTimerDecreaseEmissiveLittleSpheres, this, &APickUpSSphere::DecreaseEmissiveLittleSpheres, MoveToCharacterOverTime, false);
	}
	);
	GetWorld()->GetTimerManager().SetTimer(TmpTimerMoveUp, TmpDelegate, MoveToCharacterOverTime, false);

}

void APickUpSSphere::DecreaseEmissiveLittleSpheres()
{
	FOnTimelineFloat UpdateDelegate;
	UpdateDelegate.BindUFunction(this, FName("IncreaseEmissiveLittleSpheresTimelineUpdate"));
	FOnTimelineEvent FinishedDelegate;
	FinishedDelegate.BindUFunction(this, FName("MoveLittleSpheresInside"));
	DecreaseEmissiveLittleSpheresTimeline->AddInterpFloat(IncreaseEmissiveCurve, UpdateDelegate, FName("InAlpha"), FName("InAlpha"));
	DecreaseEmissiveLittleSpheresTimeline->SetTimelineFinishedFunc(FinishedDelegate);
	DecreaseEmissiveLittleSpheresTimeline->ReverseFromEnd();
}

void APickUpSSphere::MoveLittleSpheresInside()
{
	int32 Index;
	MoveComponentToCounter++;
	for (Index = 0; Index < LittleSpheresArray.Num(); Index++)
	{
		FVector TargetRelativeLocation = FVector(0);
		FRotator TargetRelativeRotation = FRotator(0);
		FLatentActionInfo LatentInfo = FLatentActionInfo();
		LatentInfo.CallbackTarget = this;
		LatentInfo.UUID = Index + MoveComponentToCounter;

		UKismetSystemLibrary::MoveComponentTo
		(
			LittleSpheresArray[Index],
			TargetRelativeLocation,
			TargetRelativeRotation,
			false,
			false,
			MoveLittleSpheresHorizontalOverTime,
			false,
			EMoveComponentAction::Move,
			LatentInfo
		);
	}
	MoveComponentToCounter += Index;
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APickUpSSphere::DecreaseOpacity, MoveLittleSpheresHorizontalOverTime, false);
}

void APickUpSSphere::DecreaseOpacity()
{
	for (auto Sphere : LittleSpheresArray)
	{
		Sphere->SetHiddenInGame(true);
	}
	BigSphereMaterial = BigSphere->CreateAndSetMaterialInstanceDynamicFromMaterial(0, SourceMaterialTranslucent);

	FOnTimelineFloat UpdateDelegate;
	UpdateDelegate.BindUFunction(this, FName("DecreaseOpacityTimelineUpdate"));
	FOnTimelineEvent FinishedDelegate;
	FinishedDelegate.BindUFunction(this, FName("DecreaseScaleAndOpacity"));
	DecreaseOpacityTimeline->AddInterpFloat(DecreaseOpacityCurve, UpdateDelegate, FName("InAlpha"), FName("InAlpha"));
	DecreaseOpacityTimeline->SetTimelineFinishedFunc(FinishedDelegate);
	DecreaseOpacityTimeline->PlayFromStart();
	MoveBigSphereDown();
}

void APickUpSSphere::DecreaseOpacityTimelineUpdate(float InAlpha)
{
	float Value = FMath::Lerp(1.f, MinOpacity, InAlpha);
	BigSphereMaterial->SetScalarParameterValue(OpacityName, Value);
}

void APickUpSSphere::MoveBigSphereDown()
{
	RotatingMovementComponent->RotationRate.Yaw = 0;
	FVector TargetRelativeLocation = PlayerCharacter->GetActorLocation();
	FRotator TargetRelativeRotation = FRotator(0, 360, 0);
	FLatentActionInfo LatentInfo = FLatentActionInfo();
	LatentInfo.CallbackTarget = this;
	LatentInfo.UUID = ++MoveComponentToCounter;
	UKismetSystemLibrary::MoveComponentTo
	(
		GetRootComponent(),
		TargetRelativeLocation,
		TargetRelativeRotation,
		false,
		false,
		DecreaseOpacityCurveLength,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);
}

void APickUpSSphere::DecreaseScaleAndOpacity()
{
	RotatingMovementComponent->RotationRate.Yaw = 180;
	InitialScale = GetActorScale3D();
	FOnTimelineFloat UpdateDelegate;
	UpdateDelegate.BindUFunction(this, FName("DecreaseScaleAndOpacityTimelineUpdate"));
	FOnTimelineEvent FinishedDelegate;
	FinishedDelegate.BindUFunction(this, FName("Finish"));
	DecreaseScaleAndOpacityTimeline->AddInterpFloat(DecreaseOpacityCurve, UpdateDelegate, FName("InAlpha"), FName("InAlpha"));
	DecreaseScaleAndOpacityTimeline->SetTimelineFinishedFunc(FinishedDelegate);
	DecreaseScaleAndOpacityTimeline->PlayFromStart();
}

void APickUpSSphere::DecreaseScaleAndOpacityTimelineUpdate(float InAlpha)
{
	float Value = FMath::Lerp(MinOpacity, -0.3f, InAlpha);
	BigSphereMaterial->SetScalarParameterValue(OpacityName, Value);

	float ScaleMultiplier = FMath::Lerp(1.f, 0.f, InAlpha);
	FVector NewScale = InitialScale * ScaleMultiplier;
	SetActorScale3D(NewScale);
}

void APickUpSSphere::Finish()
{
	SwitchOnSSphereAbility();
	SetEnableCharacterMovement(true);
	Destroy();
}

void APickUpSSphere::SwitchOnSSphereAbility()
{
	PlayerCharacter->SwitchOnSSphereAbility();
}





