// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Персонаж игры.
 */

#pragma once

#include "PlayerCharacterMagicTrigger.h"
#include "MagicTrigger\AttackAbilities\MeleeAttackComponent.h"
#include "MagicTrigger\AttackAbilities\SevenfoldSphereComponent.h"
#include "MagicTrigger\PlayerCharacter\UpDownLiftingItemComponent.h"
#include "MagicTrigger\PlayerCharacter\AnimationManagerComponent.h"
#include "MagicTrigger\Data\CollisionChannelsMagicTrigger.h"
#include "MagicTrigger\Enemy\EnemyCharacterMagicTrigger.h"
#include "MagicTrigger\Items\ThrowableRock.h"
#include "MagicTrigger\AttackAbilities\SevenfoldShere.h"
#include "TargetSelectionComponent.h"

#include "MagicTrigger\Interfaces\HUDInterface.h"
#include "MagicTrigger\Interfaces\EnemyCharacterInterface.h"
#include "MagicTrigger\Interfaces\InteractionInterface.h"
#include "MagicTrigger\Interfaces\PlayerStateInterface.h"
#include "TargetSelectionPlugin\Public\TargetSelectionInterface.h"

#include "Components\BoxComponent.h"
#include "GameFramework\ProjectileMovementComponent.h"

#include "Components\SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components\SceneCaptureComponent2D.h"

#include "Perception\AIPerceptionStimuliSourceComponent.h"
#include "Camera\CameraComponent.h"

#include "GameFramework\SpringArmComponent.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework\HUD.h"
#include "GameFramework\PlayerState.h"

#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/TextureRenderTarget2D.h"

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


	MeleeAttackComponent = CreateDefaultSubobject<UMeleeAttackComponent>(TEXT("MeleeAttackComponent"));
	UpDownLiftingItemComponent = CreateDefaultSubobject<UUpDownLiftingItemComponent>(TEXT("UpDownLiftingItemComponent"));
	AnimationManagerComponent = CreateDefaultSubobject<UAnimationManagerComponent>(TEXT("AnimationManagerComponent"));
	TargetSelectionComponent = CreateDefaultSubobject<UTargetSelectionComponent>(TEXT("TargetSelectionComponent"));
	SevenfoldSphereComponent = CreateDefaultSubobject<USevenfoldSphereComponent>(TEXT("SevenfoldSphereComponent"));

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
	AxisValueStopCoeff = 0;
	ArrowLeftFootSocketName = FName(TEXT("LeftFoot"));
	ArrowRightFootSocketName = FName(TEXT("RightFoot"));
	MovementStatus = EMovementStatus::EMM_Stop;
	LifeSpan = 5;

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

}

// Called when the game starts or when spawned
void APlayerCharacterMagicTrigger::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		this->PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (this->PlayerController)
		{
			this->HUD = PlayerController->GetHUD();
		}

		this->GameMode = UGameplayStatics::GetGameMode(GetWorld());
	}

}

// Called to bind functionality to input
void APlayerCharacterMagicTrigger::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (!PlayerInputComponent)
	{
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
	PlayerInputComponent->BindAction("Throw", IE_Pressed, this, &APlayerCharacterMagicTrigger::Throw_InAct);
	PlayerInputComponent->BindAction("ShowGameMenu", IE_Pressed, this, &APlayerCharacterMagicTrigger::ShowGameMenu_InAct);
	PlayerInputComponent->BindAction("CastArtefactAbility", IE_Pressed, this, &APlayerCharacterMagicTrigger::UseSevenfoldSphereAbility_InAct);
	PlayerInputComponent->BindAction("AutoRun", IE_Pressed, this, &APlayerCharacterMagicTrigger::AutoRunning_InAct);

	PlayerInputComponent->BindAction("LiftUp/PutDown", IE_Pressed, this, &APlayerCharacterMagicTrigger::LiftUpLiftingItem_InAct);
	PlayerInputComponent->BindAction("LiftUp/PutDown", IE_Released, this, &APlayerCharacterMagicTrigger::PutDownLiftingItem_InAct);

	PlayerInputComponent->BindAction("WatchEnemies_IA", IE_Pressed, this, &APlayerCharacterMagicTrigger::WatchEnemies_InAct);
	PlayerInputComponent->BindAction("OffWatchingActors_IA", IE_Pressed, this, &APlayerCharacterMagicTrigger::OffWatchingActors_InAct);
	PlayerInputComponent->BindAction("WatchOtherActors_IA", IE_Pressed, this, &APlayerCharacterMagicTrigger::WatchOtherActors_InAct);

	PlayerInputComponent->BindAction("Interact_IA", IE_Pressed, this, &APlayerCharacterMagicTrigger::Interact_InAct);

}

void APlayerCharacterMagicTrigger::MoveForward_InAx(float AxisValue)
{
	if (!this->PlayerController)
	{
		return;
	}

	float ScaleAxisValue = CalcScaleMovementInput(AxisValue);

	/*Get Direction of movement from current rotation.*/

	const FRotator Rotation = this->PlayerController->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	/*Move to Direction in X axe.*/
	AddMovementInput(Direction, ScaleAxisValue);

	RotateToTarget();
}

void APlayerCharacterMagicTrigger::MoveRight_InAx(float AxisValue)
{
	if (!this->PlayerController)
	{
		return;
	}

	float ScaleAxisValue = CalcScaleMovementInput(AxisValue);

	/*Get Direction of movement from current rotation.*/
	const FRotator Rotation = this->PlayerController->GetControlRotation();
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
	if (!this->AnimationManagerComponent->bCanRun)
	{
		return;
	}

	this->AnimationManagerComponent->bCanInteract = false;
}

void APlayerCharacterMagicTrigger::StopMove_InAct()
{
	if (!this->AnimationManagerComponent->bCanRun)
	{
		return;
	}

	this->AnimationManagerComponent->bCanInteract = true;
}

void APlayerCharacterMagicTrigger::StartRunning_InAct()
{
	if (
		this->MovementStatus == EMovementStatus::EMM_ShortWalking
		|| this->MovementStatus == EMovementStatus::EMM_AutoRunning
		|| !this->AnimationManagerComponent->bCanRun
		)
	{
		return;
	}

	this->AxisValueMovementCoeff = AxisValueRunningCoeff;
	this->MovementStatus = EMovementStatus::EMM_Running;

}

void APlayerCharacterMagicTrigger::StopRunning_InAct()
{
	if (
		this->MovementStatus == EMovementStatus::EMM_ShortWalking
		|| this->MovementStatus != EMovementStatus::EMM_Running
		|| this->MovementStatus == EMovementStatus::EMM_AutoRunning
		)
	{
		return;
	}

	this->AxisValueMovementCoeff = AxisValueWalkingCoeff;
	this->MovementStatus = EMovementStatus::EMM_Walking;

}

void APlayerCharacterMagicTrigger::StartShortWalking_InAct()
{
	if (
		this->MovementStatus == EMovementStatus::EMM_Running
		|| this->MovementStatus == EMovementStatus::EMM_AutoRunning
		|| !this->AnimationManagerComponent->bCanRun
		)
	{
		return;
	}

	this->AxisValueMovementCoeff = AxisValueShortWalkingCoeff;
	this->MovementStatus = EMovementStatus::EMM_ShortWalking;

}

void APlayerCharacterMagicTrigger::StopShortWalking_InAct()
{
	if (
		this->MovementStatus == EMovementStatus::EMM_Running
		|| this->MovementStatus != EMovementStatus::EMM_ShortWalking
		|| this->MovementStatus == EMovementStatus::EMM_AutoRunning
		)
	{
		return;
	}

	this->AxisValueMovementCoeff = AxisValueWalkingCoeff;
	this->MovementStatus = EMovementStatus::EMM_Walking;

}

void APlayerCharacterMagicTrigger::StartJump_InAct()
{
	this->AnimationManagerComponent->StartJump();
}

void APlayerCharacterMagicTrigger::StopJump_InAct()
{
	this->AnimationManagerComponent->StopJump();
}

void APlayerCharacterMagicTrigger::ZoomUp_InAct()
{
	if (this->SpringArm->TargetArmLength <= this->SpringArmLengthMin)
	{
		return;
	}

	float SpringArmLength = ZoomIntencity * -1 + this->SpringArm->TargetArmLength;
	if (SpringArmLength < this->SpringArmLengthMin)
	{
		SpringArmLength = this->SpringArmLengthMin;
	}
	this->SpringArm->TargetArmLength = SpringArmLength;
}

void APlayerCharacterMagicTrigger::ZoomDown_InAct()
{
	if (this->SpringArm->TargetArmLength >= this->SpringArmLengthMax)
	{
		return;
	}

	float SpringArmLength = ZoomIntencity + this->SpringArm->TargetArmLength;
	if (SpringArmLength > this->SpringArmLengthMax)
	{
		SpringArmLength = this->SpringArmLengthMax;
	}
	this->SpringArm->TargetArmLength = SpringArmLength;
}

void APlayerCharacterMagicTrigger::Attack_InAct()
{
	this->AnimationManagerComponent->AttackAnimation();
}

void APlayerCharacterMagicTrigger::Throw_InAct()
{
	if (!this->UpDownLiftingItemComponent->LiftUpObject)
	{
		return;
	}

	if (Cast<AThrowableItem>(this->UpDownLiftingItemComponent->LiftUpObject))
	{
		this->AnimationManagerComponent->ThrowAnimation();
	}
}

void APlayerCharacterMagicTrigger::ShowGameMenu_InAct()
{
	if (IsInterfaceImplementedBy<IHUDInterface>(this->HUD))
	{
		IHUDInterface::Execute_PauseOrUnpauseGame_IF(this->HUD, true, nullptr);
	}
}

void APlayerCharacterMagicTrigger::UseSevenfoldSphereAbility_InAct()
{
	this->SevenfoldSphereComponent->UseSevenfoldSphereAbility();
}

void APlayerCharacterMagicTrigger::AutoRunning_InAct()
{
	if (
		this->MovementStatus == EMovementStatus::EMM_Running
		|| this->MovementStatus == EMovementStatus::EMM_ShortWalking
		|| !this->AnimationManagerComponent->bCanRun
		|| !GetWorld()
		)
	{
		return;
	}

	if (this->MovementStatus == EMovementStatus::EMM_AutoRunning)
	{
		GetWorld()->GetTimerManager().ClearTimer(this->AutoRunningTimer);
		this->AxisValueMovementCoeff = AxisValueWalkingCoeff;
		this->MovementStatus = EMovementStatus::EMM_Walking;
		this->AnimationManagerComponent->bCanInteract = true;
	}
	else
	{
		this->AxisValueMovementCoeff = AxisValueRunningCoeff;
		this->MovementStatus = EMovementStatus::EMM_AutoRunning;
		this->AnimationManagerComponent->bCanInteract = false;
		GetWorld()->GetTimerManager().SetTimer(this->AutoRunningTimer, this, &APlayerCharacterMagicTrigger::AutoRunning, 0.017, true);
	}
}

void APlayerCharacterMagicTrigger::LiftUpLiftingItem_InAct()
{
	if (!this->AnimationManagerComponent->bCanInteract)
	{
		return;
	}
	this->AnimationManagerComponent->StopAnimations();
	this->UpDownLiftingItemComponent->LiftUp();
}

void APlayerCharacterMagicTrigger::PutDownLiftingItem_InAct()
{
	if (!this->AnimationManagerComponent->bCanInteract)
	{
		return;
	}
	this->AnimationManagerComponent->StopAnimations();
	this->UpDownLiftingItemComponent->PutDown();

}

void APlayerCharacterMagicTrigger::WatchEnemies_InAct(FKey InputKey)
{
	TArray<TSubclassOf<AActor>> ClassesFilter;
	ClassesFilter.Add(AEnemyCharacterMagicTrigger::StaticClass());
	TArray<TSubclassOf<AActor>> ClassesFilterException;
	TSubclassOf<UTargetSelectionInterface> InterfaceFilter;

	this->TargetSelectionComponent->WatchActors(ClassesFilter, ClassesFilterException, InterfaceFilter, InputKey);

	/**
	 * Check on Enemy's dying.
	 */

	if (IsInterfaceImplementedBy<IEnemyCharacterInterface>(this->TargetSelectionComponent->GetObservedActor()))
	{
		bool bDying = IEnemyCharacterInterface::Execute_GetDying_IF(this->TargetSelectionComponent->GetObservedActor());

		if (bDying)
		{
			RemoveAndSwitchActors(this->TargetSelectionComponent->GetObservedActor());
			return;
		}
	}

	this->AnimationManagerComponent->bWatchingNow = this->TargetSelectionComponent->GetIsWatchingNow();

}

void APlayerCharacterMagicTrigger::WatchOtherActors_InAct(FKey InputKey)
{
	TArray<TSubclassOf<AActor>> ClassesFilter;
	ClassesFilter.Add(AActor::StaticClass());
	TArray<TSubclassOf<AActor>> ClassesFilterException;
	ClassesFilterException.Add(AEnemyCharacterMagicTrigger::StaticClass());
	TSubclassOf<UTargetSelectionInterface> InterfaceFilter;

	this->TargetSelectionComponent->WatchActors(ClassesFilter, ClassesFilterException, InterfaceFilter, InputKey);
	this->AnimationManagerComponent->bWatchingNow = this->TargetSelectionComponent->GetIsWatchingNow();
}

void APlayerCharacterMagicTrigger::OffWatchingActors_InAct()
{
	this->TargetSelectionComponent->OffWatchingActors();
	this->AnimationManagerComponent->bWatchingNow = this->TargetSelectionComponent->GetIsWatchingNow();
}

void APlayerCharacterMagicTrigger::Interact_InAct()
{
	if (!this->AnimationManagerComponent->bCanInteract)
	{
		return;
	}

	this->AnimationManagerComponent->StopAnimations();
	TSubclassOf<AActor> ClassFilter;
	TArray<AActor*> OverlappingActors;
	this->InteractCollision->GetOverlappingActors(OverlappingActors, ClassFilter);

	if (!OverlappingActors.Num())
	{
		return;
	}

	AActor* FirstActor = OverlappingActors[0];
	if (IsInterfaceImplementedBy<IInteractionInterface>(FirstActor))
	{
		IInteractionInterface::Execute_Interact_IF(FirstActor);
	}
	else
	{
		return;
	}

}

void APlayerCharacterMagicTrigger::AutoRunning()
{
	MoveForward_InAx(1.0);
}

void APlayerCharacterMagicTrigger::ShowOrHideInteractionText(bool bShow, AActor* InteractionActor)
{
	if (
		!IsInterfaceImplementedBy<IInteractionInterface>(InteractionActor)
		|| !IsInterfaceImplementedBy<IHUDInterface>(this->HUD)
		|| !this->PlayerController
		)
	{
		return;
	}

	if (bShow)
	{
		FText InteractionText = IInteractionInterface::Execute_GetInteractionText_IF(InteractionActor);
		IHUDInterface::Execute_ShowInteractionWidget_IF(this->HUD, InteractionText);
	}
	else
	{
		IHUDInterface::Execute_HideInteractionWidget_IF(this->HUD);
	}
}

void APlayerCharacterMagicTrigger::GetDamage(bool bGetDamage, float Damage, AController* EnemyController)
{
	this->AnimationManagerComponent->bGettingDamage = bGetDamage;

	if (!IsInterfaceImplementedBy<IPlayerStateInterface>(GetPlayerState()))
	{
		return;
	}

	if (!bGetDamage)
	{
		return;
	}

	float LifeBeforeDamage = GetLife();
	float CurrentDefence = GetDefence();
	float CurrentLife;
	if (CurrentDefence > 1)
	{
		CurrentLife = LifeBeforeDamage - (Damage / CurrentDefence);
	} 
	else
	{
		CurrentLife = LifeBeforeDamage - Damage;
	}


	if (CurrentLife > 0)
	{
		IPlayerStateInterface::Execute_SetLife_IF(GetPlayerState(), CurrentLife);
	}
	else
	{
		IPlayerStateInterface::Execute_SetLife_IF(GetPlayerState(), 0);

		if (IsInterfaceImplementedBy<IEnemyCharacterInterface>(EnemyController))
		{
			IEnemyCharacterInterface::Execute_StopFindPlayer_IF(EnemyController);
		}

		this->AnimationManagerComponent->bDying = true;

		this->GetCharacterMovement()->DisableMovement();
		SetLifeSpan(this->LifeSpan);
	}
}

void APlayerCharacterMagicTrigger::RotateToTarget()
{
	if (
		!this->bRotatingToTarget
		|| !this->TargetSelectionComponent->GetIsWatchingNow()
		|| !this->TargetSelectionComponent->GetObservedActor()
		)
	{
		return;
	}

	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), this->TargetSelectionComponent->GetObservedActor()->GetActorLocation()).Yaw;
	SetActorRotation(NewRotation);
}

float APlayerCharacterMagicTrigger::CalcScaleMovementInput(float AxisValue)
{
	if (!this->AnimationManagerComponent->bCanRun)
	{
		return 0;
	}

	float ScaleValue = this->AxisValueMovementCoeff * AxisValue;
	return ScaleValue;
}

void APlayerCharacterMagicTrigger::SpawnThrowableRock(AThrowableRock* ThrowableRock)
{
	if (!GetWorld())
	{
		return;
	}

	TSubclassOf<AThrowableRock> RockClass;
	FName AttachSocket = ThrowableRock->AttachSocket;
	FTransform SocketTransform = GetMesh()->GetSocketTransform(AttachSocket);
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketTransform.GetLocation());
	SpawnTransform.SetRotation(SocketTransform.GetRotation());
	SpawnTransform.SetScale3D(ThrowableRock->GetActorScale3D());
	FActorSpawnParameters ActorSpawnParameters;

	this->UpDownLiftingItemComponent->DestroyLiftingActor();

	AThrowableRock* NewRock = GetWorld()->SpawnActor<AThrowableRock>(RockClass, SpawnTransform, ActorSpawnParameters);

	NewRock->Box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	if (this->TargetSelectionComponent->GetObservedActor())
	{
		FVector LaunchVelocity;
		bool bCalcVelocitySuccessful = UGameplayStatics::SuggestProjectileVelocity_CustomArc(GetWorld(), LaunchVelocity, NewRock->GetActorLocation(), this->TargetSelectionComponent->GetObservedActor()->GetActorLocation(), 0, ThrowableRock->ArcParam);
		if (!bCalcVelocitySuccessful)
		{
			return;
		}

		NewRock->ProjectileMovementComponent->SetVelocityInLocalSpace(LaunchVelocity);

	} 
	else
	{
		FVector UnitRockVelocity = UKismetMathLibrary::VLerp(GetActorForwardVector(), GetActorUpVector(), ThrowableRock->ArcAlpha);
		FVector RockVelocity = UnitRockVelocity * ThrowableRock->Speed;
		FVector LaunchVelocity = RockVelocity + GetCharacterMovement()->Velocity;
		NewRock->ProjectileMovementComponent->SetVelocityInLocalSpace(LaunchVelocity);

	}

	NewRock->ProjectileMovementComponent->ProjectileGravityScale = 1;
}

UTextureRenderTarget2D* APlayerCharacterMagicTrigger::CreateScreenShot()
{
	if (!GetWorld())
	{
		return nullptr;
	}
	UTextureRenderTarget2D* TextureTarget = UKismetRenderingLibrary::CreateRenderTarget2D(GetWorld());
	this->ScreenShotComponent->TextureTarget = TextureTarget;
	this->ScreenShotComponent->CaptureScene();

	return this->ScreenShotComponent->TextureTarget;

}

void APlayerCharacterMagicTrigger::RemoveAndSwitchActors(AActor* RemovingActor)
{
	this->TargetSelectionComponent->RemoveAndSwitchActors(RemovingActor);
	this->AnimationManagerComponent->bWatchingNow = this->TargetSelectionComponent->GetIsWatchingNow();
}

float APlayerCharacterMagicTrigger::GetDamage() const
{
	float Damage = 0;
	if (IsInterfaceImplementedBy<IPlayerStateInterface>(GetPlayerState()))
	{
		Damage = IPlayerStateInterface::Execute_GetDamage_IF(GetPlayerState());
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

	return MultiplierOfDamage;
}

float APlayerCharacterMagicTrigger::GetDefence()
{
	float Defence = 0;
	if (IsInterfaceImplementedBy<IPlayerStateInterface>(GetPlayerState()))
	{
		Defence = IPlayerStateInterface::Execute_GetDefence_IF(GetPlayerState());
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

	return Life;
}

void APlayerCharacterMagicTrigger::TraceAttackRightFoot()
{
	TArray<AActor*> IgnoredActors;
	float BaseDamage = GetDamage() * GetMultiplierOfDamage();

	this->MeleeAttackComponent->DoAttack(
		GetMesh()->GetSocketLocation(this->ArrowRightFootSocketName),
		this->ArrowRightFoot->GetForwardVector(),
		IgnoredActors,
		BaseDamage,
		this->PlayerController,
		this,
		nullptr
	);
}

void APlayerCharacterMagicTrigger::TraceAttackLeftFoot()
{
	TArray<AActor*> IgnoredActors;
	float BaseDamage = GetDamage() * GetMultiplierOfDamage();

	this->MeleeAttackComponent->DoAttack(
		GetMesh()->GetSocketLocation(this->ArrowLeftFootSocketName),
		this->ArrowLeftFoot->GetForwardVector(),
		IgnoredActors,
		BaseDamage,
		this->PlayerController,
		this,
		nullptr
	);
}

void APlayerCharacterMagicTrigger::SetPlayingAnimationPutDown2Hand_IF_Implementation(bool bPlaying)
{
	this->AnimationManagerComponent->SetPlayingAnimationPutDown2Hands(bPlaying);
}

void APlayerCharacterMagicTrigger::SetPlayingAnimationLiftUp2Hand_IF_Implementation(bool bPlaying)
{
	this->AnimationManagerComponent->SetPlayingAnimationLiftUp2Hands(bPlaying);
}

void APlayerCharacterMagicTrigger::SetPlayingAnimationPutDown1Hand_IF_Implementation(bool bPlaying)
{
	this->AnimationManagerComponent->SetPlayingAnimationPutDown1Hand(bPlaying);
}

void APlayerCharacterMagicTrigger::SetPlayingAnimationLiftUp1Hand_IF_Implementation(bool bPlaying)
{
	this->AnimationManagerComponent->SetPlayingAnimationLiftUp1Hand(bPlaying);
}

UActorComponent* APlayerCharacterMagicTrigger::GetAnimationManagerComponent_IF_Implementation() const
{
	return this->AnimationManagerComponent;
}

void APlayerCharacterMagicTrigger::ReportNoise_IF_Implementation()
{
	if (!GetWorld())
	{
		return;
	}

	UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), 1, this);
}

void APlayerCharacterMagicTrigger::DetachLiftingActor_IF_Implementation()
{
	this->UpDownLiftingItemComponent->DetachLiftingActor();
}

void APlayerCharacterMagicTrigger::AttachLiftingActor_IF_Implementation()
{
	this->UpDownLiftingItemComponent->AttachLiftingActor();
}

void APlayerCharacterMagicTrigger::AttachThrowableActor_IF_Implementation()
{
	this->UpDownLiftingItemComponent->AttachLiftingActor();
}

void APlayerCharacterMagicTrigger::SpawnThrowableActor_IF_Implementation()
{
	AThrowableRock* Rock = Cast<AThrowableRock>(this->UpDownLiftingItemComponent->LiftUpObject);
	ASevenfoldShere* Sphere = Cast<ASevenfoldShere>(this->UpDownLiftingItemComponent->LiftUpObject);

	if (Rock)
	{
		SpawnThrowableRock(Rock);
	} 
	if(Sphere)
	{
		this->SevenfoldSphereComponent->UseSevenfoldSphereAbility();
	}
}

void APlayerCharacterMagicTrigger::StopTraceAttackLeftFoot_IF_Implementation()
{
	this->MeleeAttackComponent->StopAttackTimer();
}

void APlayerCharacterMagicTrigger::StartTraceAttackLeftFoot_IF_Implementation()
{
	if (!GetWorld())
	{
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(this->MeleeAttackComponent->AttackTimer, &APlayerCharacterMagicTrigger::TraceAttackLeftFoot, this->MeleeAttackComponent->AttackTimerDeltaTime, true);
}

void APlayerCharacterMagicTrigger::StopTraceAttackRightFoot_IF_Implementation()
{
	this->MeleeAttackComponent->StopAttackTimer();
}

void APlayerCharacterMagicTrigger::StartTraceAttackRightFoot_IF_Implementation()
{
	if (!GetWorld())
	{
		return;
	}

	GetWorld()->GetTimerManager().SetTimer(this->MeleeAttackComponent->AttackTimer, &APlayerCharacterMagicTrigger::TraceAttackRightFoot, this->MeleeAttackComponent->AttackTimerDeltaTime, true);
}

void APlayerCharacterMagicTrigger::OffWatchingActors_IF_Implementation()
{
	this->TargetSelectionComponent->OffWatchingActors();
	this->AnimationManagerComponent->bWatchingNow = this->TargetSelectionComponent->GetIsWatchingNow();
}

void APlayerCharacterMagicTrigger::RemoveAndSwitchActors_IF_Implementation(AActor* RemovingActor)
{
	RemoveAndSwitchActors(RemovingActor);
}

AActor* APlayerCharacterMagicTrigger::GetObservedActor_IF_Implementation() const
{
	return this->TargetSelectionComponent->GetObservedActor();
}

UTextureRenderTarget2D* APlayerCharacterMagicTrigger::CreateScreenShot_IF_Implementation()
{
	return CreateScreenShot();
}

void APlayerCharacterMagicTrigger::DestroyLiftUpObject_IF_Implementation()
{
	this->UpDownLiftingItemComponent->DestroyLiftingActor();
}

FTransform APlayerCharacterMagicTrigger::GetSocketTransform_IF_Implementation(FName& SocketName) const
{
	return GetMesh()->GetSocketTransform(SocketName);
}

UCapsuleComponent* APlayerCharacterMagicTrigger::GetInteractCollision_IF_Implementation() const
{
	return this->InteractCollision;
}

FVector APlayerCharacterMagicTrigger::GetUpDownLiftingArrowForwardVector_IF_Implementation() const
{
	return this->UpDownLiftingArrow->GetForwardVector();
}

FTransform APlayerCharacterMagicTrigger::GetPointPutDownTransform_IF_Implementation() const
{
	return this->PointPutDown->GetComponentTransform();
}

FTransform APlayerCharacterMagicTrigger::GetPointStartTraceToPutDownPointTransform_IF_Implementation() const
{
	return this->PointStartTraceToPutDownPoint->GetComponentTransform();
}

USkeletalMeshComponent* APlayerCharacterMagicTrigger::GetMesh_IF_Implementation() const
{
	return GetMesh();
}
