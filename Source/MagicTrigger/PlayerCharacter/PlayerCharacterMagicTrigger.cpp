// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Персонаж игры.
 */

#pragma once

#include "PlayerCharacterMagicTrigger.h"
#include "MagicTrigger\AbilitySystem\AbilitySystemManager.h"
#include "MagicTrigger\AbilitySystem\SevenfoldShere\SevenfoldShere.h"
#include "MagicTrigger\PlayerCharacter\UpDownLiftUpItemComponent.h"
#include "MagicTrigger\PlayerCharacter\AnimationManagerComponent.h"
#include "MagicTrigger\Data\CollisionChannelsMagicTrigger.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "MagicTrigger\Enemy\EnemyCharacterMagicTrigger.h"
#include "MagicTrigger\SaveGame\SaveGameManager.h"
#include "MagicTrigger\CoreClasses\GameInstanceMagicTrigger.h"
#include "MagicTrigger\CoreClasses\HUDMagicTrigger.h"
#include "TargetSelectionComponent.h"

#include "MagicTrigger\Interfaces\HUDInterface.h"
#include "MagicTrigger\Interfaces\EnemyCharacterInterface.h"
#include "MagicTrigger\Interfaces\InteractionInterface.h"
#include "MagicTrigger\Interfaces\PlayerStateInterface.h"
#include "TargetSelectionPlugin\Public\TargetSelectionInterface.h"

#include "GameFramework\ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/TextureRenderTarget2D.h"

#include "Components\SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components\BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components\SceneCaptureComponent2D.h"
#include "Animation\AnimInstance.h"

#include "Camera\CameraComponent.h"

#include "GameFramework\SpringArmComponent.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework\HUD.h"
#include "GameFramework\PlayerState.h"

#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "Perception\AIPerceptionStimuliSourceComponent.h"


#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetRenderingLibrary.h"

class AThrowableItem;

// Sets default values
APlayerCharacterMagicTrigger::APlayerCharacterMagicTrigger()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	AutoReceiveInput = EAutoReceiveInput::Player0;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = nullptr;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->MaxAcceleration = 7000;
	GetCharacterMovement()->Mass = 60;
	GetCharacterMovement()->JumpZVelocity = 500;
	GetCharacterMovement()->AirControl = 0.5;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bScalePushForceToVelocity = false;
	GetCharacterMovement()->StandingDownwardForceScale = 0.5;
	GetCharacterMovement()->InitialPushForceFactor = 100;
	GetCharacterMovement()->PushForceFactor = 100;
	GetCharacterMovement()->RepulsionForce = 1;

	GetCapsuleComponent()->SetCapsuleSize(18, 88, false);
	GetCapsuleComponent()->bVisibleInReflectionCaptures = 0;
	GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionObjectType(ECC_Pawn);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Attack, ECollisionResponse::ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_ThrowableObject, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_AttackAbility, ECollisionResponse::ECR_Overlap);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Observe, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_InteractNPC, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_InteractPlayerCharacter, ECollisionResponse::ECR_Ignore);

	FHitResult HitResultTmp = FHitResult();

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88), false, &HitResultTmp, ETeleportType::None);
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0), false, &HitResultTmp, ETeleportType::None);
	GetMesh()->SetRelativeScale3D(FVector(0.85));
	GetMesh()->SetNotifyRigidBodyCollision(false);
	GetMesh()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_PhysicsBody, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Destructible, ECollisionResponse::ECR_Block);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshObj(TEXT("/Game/MagicTrigger/Meshes/PlayerCharacter/SK_Player_Idle_Kachujin"));
	if (MeshObj.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshObj.Object);
	}
	else
	{
		DEBUGMESSAGE("!MeshObj.Succeeded()")
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimationClass(TEXT("/Game/MagicTrigger/Animations/PlayerCharacter/ABP_PlayerCharacter"));
	if (AnimationClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimationClass.Class);
	}
	else
	{
		DEBUGMESSAGE("!AnimationClass.Succeeded()")
	}

	UpDownLiftUpItemComponent = CreateDefaultSubobject<UUpDownLiftUpItemComponent>(TEXT("UpDownLiftUpItemComponent"));
	AnimationManagerComponent = CreateDefaultSubobject<UAnimationManagerComponent>(TEXT("AnimationManagerComponent"));
	TargetSelectionComponent = CreateDefaultSubobject<UTargetSelectionComponent>(TEXT("TargetSelectionComponent"));

	PointStartTraceToPutDownPoint = CreateDefaultSubobject<USceneComponent>(TEXT("PointStartTraceToPutDownPoint"));
	PointCarryUp = CreateDefaultSubobject<USceneComponent>(TEXT("PointCarryUp"));
	PointPutDown = CreateDefaultSubobject<USceneComponent>(TEXT("PointPutDown"));

	InteractCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("InteractCollision"));

	UpDownLiftingArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("UpDownLiftingArrow"));
	ArrowRightFoot = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowRightFoot"));
	ArrowLeftFoot = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowLeftFoot"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	ScreenShotComponent = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("ScreenShotComponent"));

	AIPerceptionStimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIPerceptionStimuliSourceComponent"));

	bRotatingToTarget = true;
	ZoomIntencity = 50;
	SpringArmLengthMax = 2000;
	SpringArmLengthMin = -40;
	AxisValueRunningCoeff = 1;
	AxisValueShortWalkingCoeff = 0.1;
	AxisValueWalkingCoeff = 0.34;
	AxisValueMovementCoeff = AxisValueWalkingCoeff;
	AxisValueStopCoeff = 0;
	ArrowLeftFootSocketName = FName(TEXT("LeftFoot"));
	ArrowRightFootSocketName = FName(TEXT("RightFoot"));
	MovementStatus = EMovementStatus::EMM_Stop;
	LifeSpan = 5;
	bMoveEnable = true;

	TargetSelectionComponent->GetTargetSelectionCollision()->SetCollisionObjectType(ECC_Observe);
	TargetSelectionComponent->GetTargetSelectionCollision()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TargetSelectionComponent->GetTargetSelectionCollision()->SetCollisionResponseToAllChannels(ECR_Overlap);
	TargetSelectionComponent->GetTargetSelectionCollision()->SetCollisionResponseToChannel(ECC_Observe, ECR_Ignore);

	PointStartTraceToPutDownPoint->SetupAttachment(Cast<USceneComponent>(GetCapsuleComponent()));
	PointStartTraceToPutDownPoint->SetRelativeLocation(FVector(70, 0, 9), false, &HitResultTmp, ETeleportType::None);

	PointCarryUp->SetupAttachment(Cast<USceneComponent>(GetCapsuleComponent()));
	PointCarryUp->SetRelativeLocation(FVector(32, 0, 40), false, &HitResultTmp, ETeleportType::None);

	PointPutDown->SetupAttachment(Cast<USceneComponent>(GetCapsuleComponent()));
	PointPutDown->SetRelativeLocation(FVector(70, 0, -88), false, &HitResultTmp, ETeleportType::None);

	InteractCollision->SetupAttachment(GetCapsuleComponent());
	InteractCollision->SetRelativeLocation(FVector(42, 0, 0), false, &HitResultTmp, ETeleportType::None);
	InteractCollision->SetCapsuleSize(50, 88, false);
	InteractCollision->bVisibleInReflectionCaptures = 0;
	InteractCollision->SetCollisionObjectType(ECC_InteractPlayerCharacter);
	InteractCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractCollision->SetCollisionResponseToChannel(ECC_InteractNPC, ECR_Overlap);

	UpDownLiftingArrow->SetupAttachment(GetMesh());
	UpDownLiftingArrow->SetRelativeLocation(FVector(0, 0, 114.7), false, &HitResultTmp, ETeleportType::None);
	UpDownLiftingArrow->SetRelativeRotation(FRotator(0, 90, 0), false, &HitResultTmp, ETeleportType::None);

	ArrowRightFoot->SetupAttachment(GetMesh(), ArrowRightFootSocketName);
	ArrowRightFoot->SetRelativeRotation(FRotator(19, 86, 79), false, &HitResultTmp, ETeleportType::None);

	ArrowLeftFoot->SetupAttachment(GetMesh(), ArrowLeftFootSocketName);
	ArrowLeftFoot->SetRelativeRotation(FRotator(19, 93, 100), false, &HitResultTmp, ETeleportType::None);

	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->SetRelativeLocation(FVector(0, 0, 65), false, &HitResultTmp, ETeleportType::None);
	SpringArm->TargetArmLength = 1000;
	SpringArm->bUsePawnControlRotation = true;

	Camera->SetupAttachment(SpringArm);

	ScreenShotComponent->SetupAttachment(Camera);
	ScreenShotComponent->FOVAngle = 120;
	ScreenShotComponent->ProjectionType = ECameraProjectionMode::Perspective;
	ScreenShotComponent->OrthoWidth = 512;
	ScreenShotComponent->bCaptureEveryFrame = false;
	ScreenShotComponent->bCaptureOnMovement = false;
	static ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D> RenderTargetObject(TEXT("/Game/MagicTrigger/Textures/RTT_ScreenShot"));
	if (RenderTargetObject.Succeeded())
	{
		ScreenShotComponent->TextureTarget = RenderTargetObject.Object;
	}
	else
	{
		DEBUGMESSAGE("!RenderTargetObject.Succeeded()")
	}

	AIPerceptionStimuliSourceComponent->RegisterForSense(TSubclassOf<UAISense_Sight>());
	AIPerceptionStimuliSourceComponent->RegisterForSense(TSubclassOf<UAISense_Hearing>());

	AbilitySystemManagerClass = AAbilitySystemManager::StaticClass();

}

// Called when the game starts or when spawned
void APlayerCharacterMagicTrigger::BeginPlay()
{
	Super::BeginPlay();
	UGameInstanceMagicTrigger* GameInstance = Cast<UGameInstanceMagicTrigger>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		GameInstance->SaveGameManager->PlayerCharacter = this;
	}
	else
	{
		DEBUGMESSAGE("!GameInstance");
	}
	if (GetWorld())
	{
		PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController)
		{
			HUD = PlayerController->GetHUD();
		}
		else
		{
			DEBUGMESSAGE("!PlayerController")
		}

		GameMode = UGameplayStatics::GetGameMode(GetWorld());
	}
	else
	{
		DEBUGMESSAGE("!GetWorld()")
	}
	InteractCollision->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacterMagicTrigger::InteractCollisionBeginOverlap);
	InteractCollision->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacterMagicTrigger::InteractCollisionEndOverlap);

	TargetSelectionComponent->GetTargetSelectionCollision()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacterMagicTrigger::TargetSelectionCollisionBeginOverlap);
	TargetSelectionComponent->GetTargetSelectionCollision()->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacterMagicTrigger::TargetSelectionCollisionEndOverlap);

	SpawnAbilitySystemManager();

}

// Called to bind functionality to input
void APlayerCharacterMagicTrigger::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (!PlayerInputComponent)
	{
		DEBUGMESSAGE("!PlayerInputComponent")
			return;
	}

	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacterMagicTrigger::MoveForward_InAx);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacterMagicTrigger::MoveRight_InAx);
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacterMagicTrigger::Turn_InAx);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacterMagicTrigger::LookUp_InAx);

	PlayerInputComponent->BindAction("MoveAct", IE_Pressed, this, &APlayerCharacterMagicTrigger::StartMove_InAct);
	PlayerInputComponent->BindAction("MoveAct", IE_Released, this, &APlayerCharacterMagicTrigger::StopMove_InAct);

	PlayerInputComponent->BindAction("Running", IE_Pressed, this, &APlayerCharacterMagicTrigger::StartRunning_InAct);
	PlayerInputComponent->BindAction("Running", IE_Released, this, &APlayerCharacterMagicTrigger::StopRunning_InAct);

	PlayerInputComponent->BindAction("ShortWalking", IE_Pressed, this, &APlayerCharacterMagicTrigger::StartShortWalking_InAct);
	PlayerInputComponent->BindAction("ShortWalking", IE_Released, this, &APlayerCharacterMagicTrigger::StopShortWalking_InAct);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacterMagicTrigger::StartJump_InAct);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacterMagicTrigger::StopJump_InAct);

	PlayerInputComponent->BindAction("ZoomUp", IE_Pressed, this, &APlayerCharacterMagicTrigger::ZoomUp_InAct);
	PlayerInputComponent->BindAction("ZoomDown", IE_Pressed, this, &APlayerCharacterMagicTrigger::ZoomDown_InAct);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacterMagicTrigger::Attack_InAct);
	PlayerInputComponent->BindAction("ShowGameMenu", IE_Pressed, this, &APlayerCharacterMagicTrigger::ShowGameMenu_InAct);
	PlayerInputComponent->BindAction("AutoRun", IE_Pressed, this, &APlayerCharacterMagicTrigger::AutoRunning_InAct);

	PlayerInputComponent->BindAction("WatchEnemies_IA", IE_Pressed, this, &APlayerCharacterMagicTrigger::WatchEnemies_InAct);
	PlayerInputComponent->BindAction("OffWatchingActors_IA", IE_Pressed, this, &APlayerCharacterMagicTrigger::OffWatchingActors_InAct);
	PlayerInputComponent->BindAction("WatchOtherActors_IA", IE_Pressed, this, &APlayerCharacterMagicTrigger::WatchOtherActors_InAct);

	PlayerInputComponent->BindAction("Interact_IA", IE_Pressed, this, &APlayerCharacterMagicTrigger::Interact_InAct);

	PlayerInputComponent->BindAction("MeleeAbility", IE_Pressed, this, &APlayerCharacterMagicTrigger::MeleeAbility_InAct);
	PlayerInputComponent->BindAction("ThrowAbility", IE_Pressed, this, &APlayerCharacterMagicTrigger::ThrowAbility_InAct);
	PlayerInputComponent->BindAction("SSphereAbility", IE_Pressed, this, &APlayerCharacterMagicTrigger::SSphereAbility_InAct);

}

void APlayerCharacterMagicTrigger::MoveForward_InAx(float AxisValue)
{
	if (!bMoveEnable)
	{
		return;
	}
	if (!PlayerController)
	{
		DEBUGMESSAGE("!PlayerController")
			return;
	}

	float ScaleAxisValue = CalcScaleMovementInput(AxisValue);

	/*Get Direction of movement from current rotation.*/

	const FRotator Rotation = PlayerController->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	/*Move to Direction in X axe.*/
	AddMovementInput(Direction, ScaleAxisValue);
	RotateToTarget();
}

void APlayerCharacterMagicTrigger::MoveRight_InAx(float AxisValue)
{
	if (!bMoveEnable)
	{
		return;
	}
	if (!PlayerController)
	{
		DEBUGMESSAGE("!PlayerController")
			return;
	}

	float ScaleAxisValue = CalcScaleMovementInput(AxisValue);

	/*Get Direction of movement from current rotation.*/
	const FRotator Rotation = PlayerController->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	/*Move to Direction in Y axe.*/
	AddMovementInput(Direction, ScaleAxisValue);
	RotateToTarget();
}

void APlayerCharacterMagicTrigger::Turn_InAx(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void APlayerCharacterMagicTrigger::LookUp_InAx(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void APlayerCharacterMagicTrigger::StartMove_InAct()
{
	if (!bMoveEnable)
	{
		return;
	}
	if (!AnimationManagerComponent->bCanRun)
	{
		return;
	}

	AnimationManagerComponent->bCanInteract = false;
}

void APlayerCharacterMagicTrigger::StopMove_InAct()
{
	if (!bMoveEnable)
	{
		return;
	}
	if (!AnimationManagerComponent->bCanRun)
	{
		return;
	}

	AnimationManagerComponent->bCanInteract = true;
}

void APlayerCharacterMagicTrigger::StartRunning_InAct()
{
	if (!bMoveEnable)
	{
		return;
	}
	if (
		MovementStatus == EMovementStatus::EMM_ShortWalking
		|| MovementStatus == EMovementStatus::EMM_AutoRunning
		|| !AnimationManagerComponent->bCanRun
		)
	{
		return;
	}

	AxisValueMovementCoeff = AxisValueRunningCoeff;
	MovementStatus = EMovementStatus::EMM_Running;

}

void APlayerCharacterMagicTrigger::StopRunning_InAct()
{
	if (!bMoveEnable)
	{
		return;
	}
	if (
		MovementStatus == EMovementStatus::EMM_ShortWalking
		|| MovementStatus != EMovementStatus::EMM_Running
		|| MovementStatus == EMovementStatus::EMM_AutoRunning
		)
	{
		return;
	}

	AxisValueMovementCoeff = AxisValueWalkingCoeff;
	MovementStatus = EMovementStatus::EMM_Walking;

}

void APlayerCharacterMagicTrigger::StartShortWalking_InAct()
{
	if (!bMoveEnable)
	{
		return;
	}
	if (
		MovementStatus == EMovementStatus::EMM_Running
		|| MovementStatus == EMovementStatus::EMM_AutoRunning
		|| !AnimationManagerComponent->bCanRun
		)
	{
		return;
	}

	AxisValueMovementCoeff = AxisValueShortWalkingCoeff;
	MovementStatus = EMovementStatus::EMM_ShortWalking;
	AnimationManagerComponent->bShortWalk = true;

}

void APlayerCharacterMagicTrigger::StopShortWalking_InAct()
{
	if (!bMoveEnable)
	{
		return;
	}
	if (
		MovementStatus == EMovementStatus::EMM_Running
		|| MovementStatus != EMovementStatus::EMM_ShortWalking
		|| MovementStatus == EMovementStatus::EMM_AutoRunning
		)
	{
		return;
	}

	AxisValueMovementCoeff = AxisValueWalkingCoeff;
	MovementStatus = EMovementStatus::EMM_Walking;
	AnimationManagerComponent->bShortWalk = false;
}

void APlayerCharacterMagicTrigger::StartJump_InAct()
{
	if (!bMoveEnable)
	{
		return;
	}
	AnimationManagerComponent->StartJump();
}

void APlayerCharacterMagicTrigger::StopJump_InAct()
{
	if (!bMoveEnable)
	{
		return;
	}
	AnimationManagerComponent->StopJump();
}

void APlayerCharacterMagicTrigger::ZoomUp_InAct()
{
	if (SpringArm->TargetArmLength <= SpringArmLengthMin)
	{
		return;
	}

	float SpringArmLength = ZoomIntencity * -1 + SpringArm->TargetArmLength;
	if (SpringArmLength < SpringArmLengthMin)
	{
		SpringArmLength = SpringArmLengthMin;
	}
	SpringArm->TargetArmLength = SpringArmLength;
}

void APlayerCharacterMagicTrigger::ZoomDown_InAct()
{
	if (SpringArm->TargetArmLength >= SpringArmLengthMax)
	{
		return;
	}

	float SpringArmLength = ZoomIntencity + SpringArm->TargetArmLength;
	if (SpringArmLength > SpringArmLengthMax)
	{
		SpringArmLength = SpringArmLengthMax;
	}
	SpringArm->TargetArmLength = SpringArmLength;
}

void APlayerCharacterMagicTrigger::Attack_InAct()
{
	if (!bMoveEnable)
	{
		return;
	}
	AbilitySystemManager->Attack();
}

void APlayerCharacterMagicTrigger::ShowGameMenu_InAct()
{
	if (IsInterfaceImplementedBy<IHUDInterface>(HUD))
	{
		IHUDInterface::Execute_SetPauseGame_IF(HUD, true, nullptr);
	}
	else
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IHUDInterface>(HUD)")
	}
}

void APlayerCharacterMagicTrigger::AutoRunning_InAct()
{
	if (!bMoveEnable)
	{
		return;
	}
	if (!GetWorld())
	{
		DEBUGMESSAGE("!GetWorld()");
		return;
	}
	if (
		MovementStatus == EMovementStatus::EMM_Running
		|| MovementStatus == EMovementStatus::EMM_ShortWalking
		|| !AnimationManagerComponent->bCanRun
		)
	{
		return;
	}

	if (MovementStatus == EMovementStatus::EMM_AutoRunning)
	{
		GetWorld()->GetTimerManager().ClearTimer(AutoRunningTimer);
		AxisValueMovementCoeff = AxisValueWalkingCoeff;
		MovementStatus = EMovementStatus::EMM_Walking;
		AnimationManagerComponent->bCanInteract = true;
	}
	else
	{
		AxisValueMovementCoeff = AxisValueRunningCoeff;
		MovementStatus = EMovementStatus::EMM_AutoRunning;
		AnimationManagerComponent->bCanInteract = false;
		GetWorld()->GetTimerManager().SetTimer(AutoRunningTimer, this, &APlayerCharacterMagicTrigger::AutoRunning, 0.017, true);
	}
}

void APlayerCharacterMagicTrigger::LiftUpLiftUpItem()
{
	UpDownLiftUpItemComponent->LiftUp();
}

void APlayerCharacterMagicTrigger::DetachLiftUpItem()
{
	UpDownLiftUpItemComponent->DetachLiftUpItem();
}

void APlayerCharacterMagicTrigger::WatchEnemies_InAct(FKey InputKey)
{
	TArray<TSubclassOf<AActor>> ClassesFilter;
	ClassesFilter.Add(AEnemyCharacterMagicTrigger::StaticClass());
	TArray<TSubclassOf<AActor>> ClassesFilterException;
	TSubclassOf<UTargetSelectionInterface> InterfaceFilter = UTargetSelectionInterface::StaticClass();

	TargetSelectionComponent->WatchActors(ClassesFilter, ClassesFilterException, InterfaceFilter, InputKey);

	/**
	 * Check on Enemy's dying.
	 */

	if (IsInterfaceImplementedBy<IEnemyCharacterInterface>(TargetSelectionComponent->GetObservedActor()))
	{
		bool bDying = IEnemyCharacterInterface::Execute_GetDying_IF(TargetSelectionComponent->GetObservedActor());

		if (bDying)
		{
			RemoveAndSwitchActors(TargetSelectionComponent->GetObservedActor());
			return;
		}
	}
	else
	{
		//DEBUGMESSAGE("!IsInterfaceImplementedBy<IEnemyCharacterInterface>(TargetSelectionComponent->GetObservedActor())");
		return;
	}

	AnimationManagerComponent->bWatchingNow = TargetSelectionComponent->GetIsWatchingNow();

}

void APlayerCharacterMagicTrigger::WatchOtherActors_InAct(FKey InputKey)
{
	TArray<TSubclassOf<AActor>> ClassesFilter;
	ClassesFilter.Add(AActor::StaticClass());
	TArray<TSubclassOf<AActor>> ClassesFilterException;
	ClassesFilterException.Add(AEnemyCharacterMagicTrigger::StaticClass());
	TSubclassOf<UTargetSelectionInterface> InterfaceFilter;

	TargetSelectionComponent->WatchActors(ClassesFilter, ClassesFilterException, InterfaceFilter, InputKey);
	AnimationManagerComponent->bWatchingNow = TargetSelectionComponent->GetIsWatchingNow();
}

void APlayerCharacterMagicTrigger::OffWatchingActors_InAct()
{
	TargetSelectionComponent->OffWatchingActors();
	AnimationManagerComponent->bWatchingNow = TargetSelectionComponent->GetIsWatchingNow();
}

void APlayerCharacterMagicTrigger::Interact_InAct()
{
	if (!AnimationManagerComponent->bCanInteract && !AnimationManagerComponent->bCarrying)
	{
		return;
	}
	AnimationManagerComponent->StopAnimations();

	if (AnimationManagerComponent->bCarrying)
	{
		UpDownLiftUpItemComponent->PutDown();
		return;
	}

	TSubclassOf<AActor> ClassFilter;
	TArray<AActor*> OverlappingActors;
	InteractCollision->GetOverlappingActors(OverlappingActors, ClassFilter);

	if (!OverlappingActors.Num())
	{
		return;
	}

	AActor* FirstActor = OverlappingActors[0];
	if (IsInterfaceImplementedBy<IInteractionInterface>(FirstActor))
	{
		IInteractionInterface::Execute_Interact_IF(FirstActor, this);
	}
	else
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IInteractionInterface>(FirstActor)");
		return;
	}

}

void APlayerCharacterMagicTrigger::MeleeAbility_InAct()
{
	AbilitySystemManager->SetCurrentAbility(ECurrentAbility::ECA_Melee);
}

void APlayerCharacterMagicTrigger::ThrowAbility_InAct()
{
	AbilitySystemManager->SetCurrentAbility(ECurrentAbility::ECA_Throw);
}

void APlayerCharacterMagicTrigger::SSphereAbility_InAct()
{
	AbilitySystemManager->SetCurrentAbility(ECurrentAbility::ECA_SSphere);
}

void APlayerCharacterMagicTrigger::AutoRunning()
{
	MoveForward_InAx(1.0);
}

void APlayerCharacterMagicTrigger::ShowOrHideInteractionText(bool bShow, AActor* InteractionActor)
{
	if (!IsInterfaceImplementedBy<IInteractionInterface>(InteractionActor))
	{
		//DEBUGMESSAGE("!IsInterfaceImplementedBy<IInteractionInterface>(InteractionActor)");
		return;
	}
	if (!IsInterfaceImplementedBy<IHUDInterface>(HUD))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IHUDInterface>(HUD)");
		return;
	}
	if (!PlayerController)
	{
		DEBUGMESSAGE("!PlayerController");
		return;
	}

	if (bShow)
	{
		FText InteractionText = IInteractionInterface::Execute_GetInteractionText_IF(InteractionActor);
		IHUDInterface::Execute_ShowInteractionWidget_IF(HUD, InteractionText);
	}
	else
	{
		IHUDInterface::Execute_HideInteractionWidget_IF(HUD);
	}
}

float APlayerCharacterMagicTrigger::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{

	if (!IsInterfaceImplementedBy<IPlayerStateInterface>(GetPlayerState()))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IPlayerStateInterface>(GetPlayerState())");
		return 0;
	}
	if (!IsInterfaceImplementedBy<IEnemyCharacterInterface>(EventInstigator))
	{
		//DEBUGMESSAGE("!IsInterfaceImplementedBy<IEnemyCharacterInterface>(EventInstigator)");
		return 0;
	}

	AnimationManagerComponent->bGettingDamage = true;

	float LifeBeforeDamage = GetLife();
	float CurrentDefence = GetDefence();
	float CurrentLife;
	if (CurrentDefence > 1)
	{
		CurrentLife = LifeBeforeDamage - (DamageAmount / CurrentDefence);
	}
	else
	{
		CurrentLife = LifeBeforeDamage - DamageAmount;
	}


	if (CurrentLife > 0)
	{
		IPlayerStateInterface::Execute_SetLife_IF(GetPlayerState(), CurrentLife);
	}
	else
	{
		IPlayerStateInterface::Execute_SetLife_IF(GetPlayerState(), 0);
		IEnemyCharacterInterface::Execute_LosePlayer_IF(EventInstigator);
		AnimationManagerComponent->bDying = true;
		GetCharacterMovement()->DisableMovement();
		SetLifeSpan(LifeSpan);
	}

	return DamageAmount;
}

void APlayerCharacterMagicTrigger::RotateToTarget()
{
	if (
		!bRotatingToTarget
		|| !TargetSelectionComponent->GetIsWatchingNow()
		|| !TargetSelectionComponent->GetObservedActor()
		)
	{
		return;
	}

	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetSelectionComponent->GetObservedActor()->GetActorLocation()).Yaw;
	SetActorRotation(NewRotation);
}

void APlayerCharacterMagicTrigger::InteractCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ShowOrHideInteractionText(true, OtherActor);
}

void APlayerCharacterMagicTrigger::InteractCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ShowOrHideInteractionText(false, OtherActor);
}

bool APlayerCharacterMagicTrigger::IsFalling()
{
	return GetMovementComponent()->IsFalling();
}

void APlayerCharacterMagicTrigger::SetPlayingAnimationLiftUp2Hands(bool InbPlaying)
{
	AnimationManagerComponent->SetPlayingAnimationLiftUp2Hands(InbPlaying);
}

void APlayerCharacterMagicTrigger::SetPlayingAnimationLiftUp1Hand(bool InbPlaying)
{
	AnimationManagerComponent->SetPlayingAnimationLiftUp1Hand(InbPlaying);
}

void APlayerCharacterMagicTrigger::SetPlayingAnimationPutDown2Hands(bool InbPlaying)
{
	AnimationManagerComponent->SetPlayingAnimationPutDown2Hands(InbPlaying);
}

void APlayerCharacterMagicTrigger::SetCanInteract(bool InbCanInteract)
{
	AnimationManagerComponent->bCanInteract = InbCanInteract;
}

FVector APlayerCharacterMagicTrigger::GetForwardVectorArrowLeftFoot()
{
	return ArrowLeftFoot->GetForwardVector();
}

FVector APlayerCharacterMagicTrigger::GetForwardVectorArrowRightFoot()
{
	return ArrowRightFoot->GetForwardVector();
}

FVector APlayerCharacterMagicTrigger::GetArrowLeftFootSocketLocation()
{
	return 	GetMesh()->GetSocketLocation(ArrowLeftFootSocketName);
}

FVector APlayerCharacterMagicTrigger::GetArrowRightFootSocketLocation()
{
	return 	GetMesh()->GetSocketLocation(ArrowRightFootSocketName);
}

void APlayerCharacterMagicTrigger::SpawnAbilitySystemManager()
{
	FTransform SpawnTransform = FTransform();
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AbilitySystemManager = GetWorld()->SpawnActor<AAbilitySystemManager>(AbilitySystemManagerClass, SpawnTransform, ActorSpawnParameters);
	if (!AbilitySystemManager)
	{
		DEBUGMESSAGE("!AbilitySystemManager");
		return;
	}
	AbilitySystemManager->PlayerCharacter = this;
	AHUDMagicTrigger* HUDMT = Cast<AHUDMagicTrigger>(HUD);
	if (!HUDMT)
	{
		DEBUGMESSAGE("!HUDMT");
		return;
	}
	AbilitySystemManager->HUD = HUDMT;
}

float APlayerCharacterMagicTrigger::CalcScaleMovementInput(float AxisValue)
{
	if (!AnimationManagerComponent->bCanRun)
	{
		return 0;
	}

	float ScaleValue = AxisValueMovementCoeff * AxisValue;
	return ScaleValue;
}

void APlayerCharacterMagicTrigger::SetEnableMovement(bool bInEnable)
{
	bMoveEnable = bInEnable;
	if (bInEnable)
	{
		MovementStatus = EMovementStatus::EMM_Walking;
	}
	else
	{
		MovementStatus = EMovementStatus::EMM_Stop;
	}
}

UTextureRenderTarget2D* APlayerCharacterMagicTrigger::CreateScreenShot()
{
	if (!GetWorld())
	{
		DEBUGMESSAGE("!GetWorld()");
		return nullptr;
	}
	UTextureRenderTarget2D* TextureTarget = UKismetRenderingLibrary::CreateRenderTarget2D(GetWorld());
	ScreenShotComponent->TextureTarget = TextureTarget;
	ScreenShotComponent->CaptureScene();

	return ScreenShotComponent->TextureTarget;

}

void APlayerCharacterMagicTrigger::RemoveAndSwitchActors(AActor* RemovingActor)
{
	TargetSelectionComponent->RemoveAndSwitchActors(RemovingActor);
	AnimationManagerComponent->bWatchingNow = TargetSelectionComponent->GetIsWatchingNow();
}

void APlayerCharacterMagicTrigger::TargetSelectionCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TargetSelectionComponent->AddActor(OtherActor);
}

void APlayerCharacterMagicTrigger::TargetSelectionCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	TargetSelectionComponent->RemoveAndSwitchActors(OtherActor);
}


float APlayerCharacterMagicTrigger::GetDamage() const
{
	float Damage = 0;
	if (IsInterfaceImplementedBy<IPlayerStateInterface>(GetPlayerState()))
	{
		Damage = IPlayerStateInterface::Execute_GetDamage_IF(GetPlayerState());
	}
	else
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IPlayerStateInterface>(GetPlayerState())");
	}

	return Damage;
}

float APlayerCharacterMagicTrigger::GetMultiplierOfDamage() const
{
	float MultiplierOfDamage = 0;
	if (IsInterfaceImplementedBy<IPlayerStateInterface>(GetPlayerState()))
	{
		MultiplierOfDamage = IPlayerStateInterface::Execute_GetMultiplierOfDamage_IF(GetPlayerState());
	}
	else
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IPlayerStateInterface>(GetPlayerState())");
	}

	return MultiplierOfDamage;
}

float APlayerCharacterMagicTrigger::GetAllDamage() const
{
	return GetDamage() * GetMultiplierOfDamage();
}

float APlayerCharacterMagicTrigger::GetDefence()
{
	float Defence = 0;
	if (IsInterfaceImplementedBy<IPlayerStateInterface>(GetPlayerState()))
	{
		Defence = IPlayerStateInterface::Execute_GetDefence_IF(GetPlayerState());
	}
	else
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IPlayerStateInterface>(GetPlayerState())");
	}

	return Defence;
}

float APlayerCharacterMagicTrigger::GetLife()
{
	float Life = 0;
	if (IsInterfaceImplementedBy<IPlayerStateInterface>(GetPlayerState()))
	{
		Life = IPlayerStateInterface::Execute_GetLife_IF(GetPlayerState());
	}
	else
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IPlayerStateInterface>(GetPlayerState())");
	}

	return Life;
}

void APlayerCharacterMagicTrigger::ReportNoise()
{
	if (!GetWorld())
	{
		DEBUGMESSAGE("!GetWorld()");
		return;
	}

	UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), 1, this);
}

void APlayerCharacterMagicTrigger::AttachLiftUpItem()
{
	UpDownLiftUpItemComponent->AttachLiftUpItem();
}

void APlayerCharacterMagicTrigger::PickUpPickUpItem()
{
	UpDownLiftUpItemComponent->PickUpPickUpItem();
}

void APlayerCharacterMagicTrigger::SpawnThrowableItem()
{
	AbilitySystemManager->SpawnThrowableItem();
}

void APlayerCharacterMagicTrigger::StopTraceAttackLeftFoot()
{
	AbilitySystemManager->StopTraceAttackLeftFoot();
}

void APlayerCharacterMagicTrigger::StartTraceAttackLeftFoot()
{
	AbilitySystemManager->StartTraceAttackLeftFoot();
}

void APlayerCharacterMagicTrigger::StopTraceAttackRightFoot()
{
	AbilitySystemManager->StopTraceAttackRightFoot();
}

void APlayerCharacterMagicTrigger::PickUpThrowableItem()
{
	AbilitySystemManager->IncreaseCountOfThrowableItem();
	UpDownLiftUpItemComponent->DestroyLiftUpItem();
}

FVector APlayerCharacterMagicTrigger::GetVelocity() const
{
	return GetCharacterMovement()->Velocity;
}

void APlayerCharacterMagicTrigger::ThrowThrowableItem()
{
	AbilitySystemManager->ThrowThrowableItem();
}

void APlayerCharacterMagicTrigger::SwitchOnSSphereAbility()
{
	AbilitySystemManager->SwitchOnSSphereAbility();
}

void APlayerCharacterMagicTrigger::StartTraceAttackRightFoot()
{
	AbilitySystemManager->StartTraceAttackRightFoot();
}

void APlayerCharacterMagicTrigger::OffWatchingActors()
{
	TargetSelectionComponent->OffWatchingActors();
	AnimationManagerComponent->bWatchingNow = TargetSelectionComponent->GetIsWatchingNow();
}

void APlayerCharacterMagicTrigger::RemoveAndSwitchActors_IF_Implementation(AActor* RemovingActor)
{
	RemoveAndSwitchActors(RemovingActor);
}

AActor* APlayerCharacterMagicTrigger::GetObservedActor() const
{
	return TargetSelectionComponent->GetObservedActor();
}

UTextureRenderTarget2D* APlayerCharacterMagicTrigger::CreateScreenShot_IF_Implementation()
{
	return CreateScreenShot();
}

FTransform APlayerCharacterMagicTrigger::GetSocketTransform(FName& SocketName) const
{
	return GetMesh()->GetSocketTransform(SocketName);
}

FVector APlayerCharacterMagicTrigger::GetUpDownLiftingArrowForwardVector() const
{
	return UpDownLiftingArrow->GetForwardVector();
}

FTransform APlayerCharacterMagicTrigger::GetPointPutDownTransform() const
{
	return PointPutDown->GetComponentTransform();
}

FTransform APlayerCharacterMagicTrigger::GetPointStartTraceToPutDownPointTransform() const
{
	return PointStartTraceToPutDownPoint->GetComponentTransform();
}

