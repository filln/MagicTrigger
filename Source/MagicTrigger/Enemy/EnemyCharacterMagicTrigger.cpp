// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Родительский класс врагов.
 */

#include "EnemyCharacterMagicTrigger.h"
#include "MagicTrigger\Data\CollisionChannelsMagicTrigger.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "MagicTrigger\AI\Enemy\EnemyAIController.h"
#include "MagicTrigger\Interfaces\OwnerTargetSelectionInterface.h"
#include "MagicTrigger\Interfaces\HUDInterface.h"
#include "Kismet/GameplayStatics.h"
#include "NavAreas\NavArea_Obstacle.h"
#include "Components/CapsuleComponent.h"
#include "Components\SphereComponent.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "GameFramework\HUD.h"

 // Sets default values
AEnemyCharacterMagicTrigger::AEnemyCharacterMagicTrigger()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AEnemyAIController::StaticClass();

	GetCapsuleComponent()->AreaClass = UNavArea_Obstacle::StaticClass();
	GetCapsuleComponent()->bVisibleInReflectionCaptures = 0;
	GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionObjectType(ECC_Pawn);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_ThrowableObject, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_AttackAbility, ECollisionResponse::ECR_Overlap);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Observe, ECollisionResponse::ECR_Overlap);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_InteractNPC, ECollisionResponse::ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_InteractPlayerCharacter, ECollisionResponse::ECR_Ignore);

	FHitResult HitResultTmp = FHitResult();
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0), false, &HitResultTmp, ETeleportType::None);
	GetMesh()->SetNotifyRigidBodyCollision(false);
	GetMesh()->SetGenerateOverlapEvents(false);
	GetMesh()->SetCollisionObjectType(ECC_Pawn);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_PhysicsBody, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Destructible, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_ThrowableObject, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetCollisionResponseToChannel(ECC_AttackAbility, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetCollisionResponseToChannel(ECC_InteractNPC, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetCollisionResponseToChannel(ECC_InteractPlayerCharacter, ECollisionResponse::ECR_Overlap);

	GetCharacterMovement()->MaxWalkSpeed = 450;
	GetCharacterMovement()->JumpZVelocity = 500;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	RunAISphere = CreateDefaultSubobject<USphereComponent>(TEXT("RunAISphere"));
	RunAISphere->SetupAttachment(GetRootComponent());
	RunAISphere->AreaClass = UNavArea_Obstacle::StaticClass();
	RunAISphere->SetNotifyRigidBodyCollision(false);
	RunAISphere->SetGenerateOverlapEvents(true);
	RunAISphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	RunAISphere->SetCollisionObjectType(ECC_WorldDynamic);
	RunAISphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	RunAISphere->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
	RunAISphere->SetSphereRadius(5000, false);

	bGetDamage = false;
	bAttack = false;
	bObserved = false;
	bDying = false;
	bStunning = false;
	bStunningAfterGetDamage = false;
	EnemyToBehaviorTreeStruct = FEnemyToBehaviorTreeStruct();
	Name = FText::FromString(TEXT("NoSpecifiedEnemyName"));
	Icon = nullptr;
	MaxLife = 100;
	MaxDefence = 100;
	MaxDamage = 100;
	Life = MaxLife;
	Defence = MaxDefence;
	Damage = MaxDamage;
	LifeSpan = 120;
	InitialMovementMode = EMovementMode::MOVE_Walking;
}

// Called when the game starts or when spawned
void AEnemyCharacterMagicTrigger::BeginPlay()
{
	Super::BeginPlay();

	this->RunAISphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacterMagicTrigger::OnRunAI);
	this->RunAISphere->OnComponentEndOverlap.AddDynamic(this, &AEnemyCharacterMagicTrigger::OnStopAI);
}

void AEnemyCharacterMagicTrigger::StartAttack()
{
	if (!this->bAttack)
	{
		this->bAttack = true;
	}
}

void AEnemyCharacterMagicTrigger::StopAttack()
{
	if (this->bAttack)
	{
		this->bAttack = false;
	}
}

void AEnemyCharacterMagicTrigger::OnRunAI(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//DEBUGMESSAGE("RunAISphere overlap something.");
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!PlayerCharacter)
	{
		DEBUGMESSAGE("!PlayerCharacter");
		return;
	}
	ACharacter* OverlapPlayerCharacter = Cast<ACharacter>(OtherActor);
	if (!OverlapPlayerCharacter)
	{
		return;
	}
	if (OverlapPlayerCharacter != PlayerCharacter)
	{
		return;
	}

	//DEBUGMESSAGE("RunAISphere begin overlap PlayerCharacter.")

	if (!GetController())
	{
		DEBUGMESSAGE("!GetController()");
		return;
	}
	AEnemyAIController* EnemyController = Cast<AEnemyAIController>(GetController());
	if (!EnemyController)
	{
		DEBUGMESSAGE("!EnemyController");
		return;
	}
	
	EnemyController->OnRunAI();
}

void AEnemyCharacterMagicTrigger::OnStopAI(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!PlayerCharacter)
	{
		DEBUGMESSAGE("!PlayerCharacter");
		return;
	}
	ACharacter* OverlapPlayerCharacter = Cast<ACharacter>(OtherActor);
	if (!OverlapPlayerCharacter)
	{
		return;
	}
	if (OverlapPlayerCharacter != PlayerCharacter)
	{
		return;
	}

	//DEBUGMESSAGE("RunAISphere end overlap PlayerCharacter.")

	if (!GetController())
	{
		DEBUGMESSAGE("!GetController()");
		return;
	}
	AEnemyAIController* EnemyController = Cast<AEnemyAIController>(GetController());
	if (!EnemyController)
	{
		DEBUGMESSAGE("!EnemyController");
		return;
	}

	EnemyController->OnStopAI();
}

float AEnemyCharacterMagicTrigger::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{

	if (this->Defence > 1)
	{
		this->Life = this->Life - (DamageAmount / this->Defence);
	}
	else
	{
		this->Life = this->Life - DamageAmount;
	}


	if (this->Life > 0)
	{
		if (GetCharacterMovement()->GetGroundMovementMode() == EMovementMode::MOVE_None)
		{
			this->InitialMovementMode = EMovementMode::MOVE_Walking;
		}
		else
		{
			this->InitialMovementMode = GetCharacterMovement()->GetGroundMovementMode();
		}

		GetCharacterMovement()->DisableMovement();
	}
	else
	{
		Die();
	}
	return DamageAmount;
}

void AEnemyCharacterMagicTrigger::DoAfterEndAnimationTakeDamage()
{
	GetCharacterMovement()->SetGroundMovementMode(this->InitialMovementMode);

	if (bStunningAfterGetDamage)
	{
		Stunning(bStunningAfterGetDamage);
	}
}

void AEnemyCharacterMagicTrigger::Stunning(bool bInStunning)
{
	if (bInStunning)
	{
		if (GetCharacterMovement()->GetGroundMovementMode() == EMovementMode::MOVE_None)
		{
			this->InitialMovementMode = EMovementMode::MOVE_Walking;
		}
		else
		{
			this->InitialMovementMode = GetCharacterMovement()->GetGroundMovementMode();
		}

		GetCharacterMovement()->DisableMovement();
	}
	else
	{
		GetCharacterMovement()->SetGroundMovementMode(this->InitialMovementMode);
		this->bStunningAfterGetDamage = false;
	}

	this->bStunning = bInStunning;
}

void AEnemyCharacterMagicTrigger::Die()
{
	if (!GetController())
	{
		DEBUGMESSAGE("!GetController()");
		return;
	}

	AEnemyAIController* EnemyController = Cast<AEnemyAIController>(GetController());
	if (!EnemyController)
	{
		DEBUGMESSAGE("!EnemyController");
		return;
	}

	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!PlayerCharacter)
	{
		DEBUGMESSAGE("!PlayerCharacter");
		return;
	}
	if (!IsInterfaceImplementedBy<IOwnerTargetSelectionInterface>(PlayerCharacter))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IOwnerTargetSelectionInterface>(PlayerCharacter)");
		return;
	}

	IOwnerTargetSelectionInterface::Execute_RemoveAndSwitchActors_IF(PlayerCharacter, this);
	EnemyController->OnStopAI();
	this->Life = 0;
	bDying = true;
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(this->LifeSpan);
}

void AEnemyCharacterMagicTrigger::IsObserved_Implementation()
{
	if (this->bDying)
	{
		ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (!PlayerCharacter)
		{
			DEBUGMESSAGE("!PlayerCharacter");
			return;
		}
		if (!IsInterfaceImplementedBy<IOwnerTargetSelectionInterface>(PlayerCharacter))
		{
			DEBUGMESSAGE("!IsInterfaceImplementedBy<IOwnerTargetSelectionInterface>(PlayerCharacter)");
			return;
		}

		IOwnerTargetSelectionInterface::Execute_RemoveAndSwitchActors_IF(PlayerCharacter, this);
	} 
	else
	{
		//APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		APlayerController* PlayerController = GetController<APlayerController>();
		if (!PlayerController)
		{
			DEBUGMESSAGE("!PlayerController");
			return;
		}
		AHUD* HUD = PlayerController->GetHUD();
		if (!HUD)
		{
			DEBUGMESSAGE("!HUD");
			return;
		}
		if (!IsInterfaceImplementedBy<IHUDInterface>(HUD))
		{
			DEBUGMESSAGE("!IsInterfaceImplementedBy<IHUDInterface>(HUD)");
			return;
		}
		IHUDInterface::Execute_SetEnemy_IF(HUD, this);
		IHUDInterface::Execute_ShowObserveEnemyWidget_IF(HUD);
		this->bObserved = true;
		GetMesh()->SetRenderCustomDepth(this->bObserved);
	}
}

void AEnemyCharacterMagicTrigger::IsNotObserved_Implementation()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController)
	{
		DEBUGMESSAGE("!PlayerController");
		return;
	}
	AHUD* HUD = PlayerController->GetHUD();
	if (!HUD)
	{
		DEBUGMESSAGE("!HUD");
		return;
	}
	if (!IsInterfaceImplementedBy<IHUDInterface>(HUD))
	{
		DEBUGMESSAGE("!IsInterfaceImplementedBy<IHUDInterface>(HUD)");
		return;
	}
	IHUDInterface::Execute_HideObserveEnemyWidget_IF(HUD);
	this->bObserved = false;
	GetMesh()->SetRenderCustomDepth(this->bObserved);
}

AActor* AEnemyCharacterMagicTrigger::GetEnemy_IF_Implementation() 
{
	return this;
}

float AEnemyCharacterMagicTrigger::GetLife_IF_Implementation() const
{
	return this->Life;
}

float AEnemyCharacterMagicTrigger::GetMaxLife_IF_Implementation() const
{
	return this->MaxLife;
}

UTexture2D* AEnemyCharacterMagicTrigger::GetIcon_IF_Implementation() const
{
	return this->Icon;
}

FText AEnemyCharacterMagicTrigger::GetName_IF_Implementation() const
{
	return this->Name;
}

bool AEnemyCharacterMagicTrigger::GetDying_IF_Implementation() const
{
	return this->bDying;
}

