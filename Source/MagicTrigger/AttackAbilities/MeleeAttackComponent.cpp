// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Для атаки ближнего боя.
 */


#include "MeleeAttackComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMeleeAttackComponent::UMeleeAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	AttackLengthTrace = 100;
	TraceSphereRadius = 50;
	TraceCollisionChannel = ECC_GameTraceChannel1;
	TraceComplex = false;
	bDrawDebugTrace = false;

}


void UMeleeAttackComponent::DoAttack(const FVector& StartTrace, const FVector& EndTraceUnit, const TArray<AActor*>& IgnoredActors, const float BaseDamage, AController* EventInstigator, AActor* DamageCauser, TSubclassOf<UDamageType> DamageTypeClass)
{
	FHitResult TraceAttackHitResult;
	bool bTraceResult = TraceAttack(TraceAttackHitResult, StartTrace, EndTraceUnit, IgnoredActors);

	if (bTraceResult)
	{
		GetWorld()->GetTimerManager().ClearTimer(this->AttackTimer);

		UGameplayStatics::ApplyDamage(TraceAttackHitResult.GetActor(), BaseDamage, EventInstigator, DamageCauser, DamageTypeClass);
	}
}

bool UMeleeAttackComponent::TraceAttack(FHitResult& OutHit, const FVector& StartTrace, const FVector& EndTraceUnit, const TArray<AActor*>& IgnoredActors)
{
	FVector EndTrace = StartTrace + EndTraceUnit * this->AttackLengthTrace;


	FName TraceTag = FName(TEXT("TraceAttack"));
	FCollisionQueryParams CollisionQueryParams = FCollisionQueryParams(TraceTag, FCollisionQueryParams::GetUnknownStatId());

	CollisionQueryParams.AddIgnoredActors(IgnoredActors);

	FCollisionResponseParams CollisionResponseParams;


	if (this->bDrawDebugTrace)
	{
		GetWorld()->DebugDrawTraceTag = TraceTag;
	}
	else
	{
		GetWorld()->DebugDrawTraceTag = FName();
	}

	FHitResult HitResultTmp;
	FQuat QuatTmp = FQuat();
	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(this->TraceSphereRadius);
	bool bTraceResult = GetWorld()->SweepSingleByChannel(HitResultTmp, StartTrace, EndTrace, QuatTmp, this->TraceCollisionChannel, CollisionShape, CollisionQueryParams, CollisionResponseParams);

	return bTraceResult;
}







