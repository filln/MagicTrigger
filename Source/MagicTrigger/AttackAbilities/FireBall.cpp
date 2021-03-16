// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Фаербол, используется для атаки. Работает в связке с UFireBallComponent.
 */

#include "FireBall.h"
#include "MagicTrigger\Data\CollisionChannelsMagicTrigger.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "Components\SphereComponent.h"
#include "Components\StaticMeshComponent.h"
#include "Particles\ParticleSystem.h"
#include "Kismet\KismetSystemLibrary.h"
#include "Kismet\GameplayStatics.h"

// Sets default values
AFireBall::AFireBall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SetRootComponent(SphereCollision);
	SphereCollision->SetSphereRadius(8);
	SphereCollision->SetEnableGravity(false);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionObjectType(ECC_AttackAbility);
	SphereCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObject(TEXT("/Game/MagicTrigger/Meshes/AttackAbilities/SM_AttackAbilitySphere"));
	if (MeshObject.Succeeded())
	{
		Mesh->SetStaticMesh(MeshObject.Object);
	}
	else
	{
		DEBUGMESSAGE("!MeshObject.Succeeded()");
	}
	Mesh->SetEnableGravity(false);
	Mesh->SetGenerateOverlapEvents(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CurrentMultiplierOfScale = 1;
	CurrentMultiplierOfEmissive = 1;
	InitialScale = FVector(1);

	static ConstructorHelpers::FObjectFinder<UTexture> TextureObject(TEXT("/Game/MagicTrigger/Textures/T_FireBall_D"));
	if (TextureObject.Succeeded())
	{
		Texture = TextureObject.Object;
	}
	else
	{
		DEBUGMESSAGE("!TextureObject.Succeeded()");
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> SourceMaterialObject(TEXT("/Game/MagicTrigger/Materials/M_AttackAbility"));
	if (SourceMaterialObject.Succeeded())
	{
		SourceMaterial = SourceMaterialObject.Object;
	} 
	else
	{
		DEBUGMESSAGE("!SourceMaterialObject.Succeeded()");
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> EmitterTemplateObject(TEXT("/Game/MagicTrigger/Particles/P_Explosion"));
	if (EmitterTemplateObject.Succeeded())
	{
		EmitterTemplate = EmitterTemplateObject.Object;
	}
	else
	{
		DEBUGMESSAGE("!EmitterTemplateObject.Succeeded()");
	}


	EmissiveColor = FLinearColor(FVector(0.529412, 0, 0));

}

void AFireBall::SaveInitialScale()
{
	this->InitialScale = GetActorScale3D();
}

void AFireBall::MoveToTarget(FFireBallMoveToTargetInputsStruct FireBallMoveToTargetInputsStruct)
{
	SetActorEnableCollision(true);

	FVector TargetRelativeLocation = FireBallMoveToTargetInputsStruct.Target->GetActorLocation();
	FRotator TargetRelativeRotation = GetRootComponent()->GetRelativeRotation();
	float OverTime = CalcTimeOfMoveToTarget(FireBallMoveToTargetInputsStruct.Target, FireBallMoveToTargetInputsStruct.SpeedOfMoveToTarget);

	FLatentActionInfo LatentInfo = FLatentActionInfo();
	LatentInfo.CallbackTarget = this;
	//LatentInfo.ExecutionFunction = "DoAfterMoveToTarget";
	//LatentInfo.Linkage = 0;
	//LatentInfo.UUID = 0;
	UKismetSystemLibrary::MoveComponentTo
	(
		GetRootComponent(),
		TargetRelativeLocation,
		TargetRelativeRotation,
		false,
		false,
		OverTime,
		false,
		EMoveComponentAction::Move,
		LatentInfo
	);

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &AFireBall::DoAfterMoveToTarget, FireBallMoveToTargetInputsStruct);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, OverTime, false);
}

void AFireBall::DoAfterMoveToTarget(FFireBallMoveToTargetInputsStruct FireBallMoveToTargetInputsStruct)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), this->EmitterTemplate, GetActorLocation(), FRotator(0), FVector(1), true, EPSCPoolMethod::None, true);
	DoDamage(FireBallMoveToTargetInputsStruct);
	Destroy();
}

void AFireBall::DoDamage(FFireBallMoveToTargetInputsStruct FireBallMoveToTargetInputsStruct)
{
	if (!IsOverlappingActor(FireBallMoveToTargetInputsStruct.Target))
	{
		return;
	}

	UGameplayStatics::ApplyDamage
	(
		FireBallMoveToTargetInputsStruct.Target, 
		FireBallMoveToTargetInputsStruct.Damage, 
		FireBallMoveToTargetInputsStruct.OwnersController, 
		FireBallMoveToTargetInputsStruct.Owner, 
		FireBallMoveToTargetInputsStruct.DamageTypeClass
	);


}

float AFireBall::CalcTimeOfMoveToTarget(AActor* Target, float Speed)
{
	float Time = GetDistanceTo(Target) / Speed;
	return Time;
}

