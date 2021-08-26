// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Враг перса Демон.
 */

#include "DemonCharacter.h"
#include "MagicTrigger\AbilitySystem\FireBall\FireBallComponent.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "Components/CapsuleComponent.h"
#include "Components\SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

class UAnimInstance;
class UAnimationAsset;

ADemonCharacter::ADemonCharacter()
{
	GetCapsuleComponent()->SetWorldScale3D(FVector(2));
	GetCapsuleComponent()->SetCapsuleHalfHeight(100, false);
	GetCapsuleComponent()->SetCapsuleRadius(50, false);

	FHitResult HitResultTmp = FHitResult();

	GetMesh()->SetRelativeLocation(FVector(0, 0, -99.5), false, &HitResultTmp, ETeleportType::None);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshObj(TEXT("/Game/MagicTrigger/Meshes/Enemy/SK_Demon"));
	if (MeshObj.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshObj.Object);
	}
	else
	{
		DEBUGMESSAGE("!MeshObj.Succeeded()")
	}
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimationClass(TEXT("/Game/MagicTrigger/Animations/Enemy/Demon/ABP_Demon"));
	if (AnimationClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimationClass.Class);
	}
	else
	{
		DEBUGMESSAGE("!AnimationClass.Succeeded()")
	}

	GetCharacterMovement()->MaxAcceleration = 500;
	GetCharacterMovement()->MaxCustomMovementSpeed = 450;

	FireBallComponent = CreateDefaultSubobject<UFireBallComponent>(TEXT("FireBallComponent"));

	Name = FText::FromStringTable("/Game/MagicTrigger/Data/ST_EnemyName.ST_EnemyName", "Demon");
	if (Name.IsEmpty())
	{
		DEBUGMESSAGE("Name.IsEmpty()");

	}

	static ConstructorHelpers::FObjectFinder<UTexture2D> IconObj(TEXT("/Game/MagicTrigger/Textures/Enemy/Demon/T_DemonIcon_D"));
	if (IconObj.Succeeded())
	{
		Icon = IconObj.Object;
	}
	else
	{
		DEBUGMESSAGE("!IconObj.Succeeded()")
	}

	RunAISphere->SetSphereRadius(5000, false);

	EnemyToBehaviorTreeStruct.WaitTimeOfAnimationRoaring = 2.83;
	EnemyToBehaviorTreeStruct.FindPlayerRadius = 4000;
	EnemyToBehaviorTreeStruct.SightRadius = 3700; //Примерная диагональ замка.
	EnemyToBehaviorTreeStruct.LoseSightRadius = 4000;
	EnemyToBehaviorTreeStruct.HearingRange = 1300;
	EnemyToBehaviorTreeStruct.MoveAndAttackRadius = 1300;
	EnemyToBehaviorTreeStruct.AttackRadius = 1100;	
	EnemyToBehaviorTreeStruct.PatrolingRadius = 1400; //Примерная половина длины или ширины замка.
	EnemyToBehaviorTreeStruct.PatrolingWaitMaxTime = 10;

	static ConstructorHelpers::FObjectFinder<UAnimationAsset> AnimationRoaringObj(TEXT("/Game/MagicTrigger/Animations/Enemy/Demon/AS_Demon_Standing_Taunt_Battlecry"));
	if (AnimationRoaringObj.Succeeded())
	{
		EnemyToBehaviorTreeStruct.AnimationRoaring = AnimationRoaringObj.Object;
	}
	else
	{
		DEBUGMESSAGE("!AnimationRoaringObj.Succeeded()")
	}
}

void ADemonCharacter::BeginPlay()
{
	Super::BeginPlay();

	Name = FText::FromStringTable("/Game/MagicTrigger/Data/ST_EnemyName.ST_EnemyName", "Demon");
	if (Name.IsEmpty())
	{
		DEBUGMESSAGE("Name.IsEmpty()");

	}
}

float ADemonCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	if (Defence > 1)
	{
		Life = Life - (DamageAmount / Defence);
	}
	else
	{
		Life = Life - DamageAmount;
	}

	if (Life <= 0)
	{
		FireBallComponent->DestroyAllFireBalls();
		Die();
	}

	return DamageAmount;
}

void ADemonCharacter::CreateFireBall()
{
	FireBallComponent->CreateFireBall(GetMesh());
}

void ADemonCharacter::MoveFireBallToTarget()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!PlayerCharacter)
	{
		DEBUGMESSAGE("!PlayerCharacter");
		return;
	}
	if (!GetController())
	{
		DEBUGMESSAGE("!GetController()");
		return;
	}
	//if (!FireBallComponent)
	//{
	//	DEBUGMESSAGE("!FireBallComponent");
	//	return;
	//}
	FireBallComponent->MoveFireBallToTarget(GetController(), PlayerCharacter);
}
