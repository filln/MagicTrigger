// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Для атаки ближнего боя.
 */


#include "MeleeAttackComponent.h"
#include "Kismet/GameplayStatics.h"
//#include "Kismet\KismetSystemLibrary.h"
#include "MagicTrigger\Data\CollisionChannelsMagicTrigger.h"
#include "MagicTrigger\Data\DebugMessage.h"

 // Sets default values for this component's properties
UMeleeAttackComponent::UMeleeAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	AttackLengthTrace = 100;
	TraceSphereRadius = 100;
	TraceCollisionChannel = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Attack);
	bTraceComplex = false;
	bIgnoreSelf = true;
	DrawDebugType = EDrawDebugTrace::Type::None;
	TraceColor = FLinearColor(1, 0, 0);
	TraceHitColor = FLinearColor(0, 1, 0);
	DrawTime = 1;
	AttackTimerDeltaTime = 0.017;
	CheckAttackTimerTimerDeltaTime = 1;
	DamageTypeClass = nullptr;

}


void UMeleeAttackComponent::BeginPlay()
{

}

void UMeleeAttackComponent::DoAttack(FVector StartTrace, FVector EndTraceUnit, float BaseDamage, AController* EventInstigator, AActor* DamageCauser)
{
	FHitResult TraceAttackHitResult;
	bool bTraceResult = TraceAttack(TraceAttackHitResult, StartTrace, EndTraceUnit);

	if (bTraceResult)
	{
		//DEBUGMESSAGE("bTraceResult");
		//DEBUGSTRING(TraceAttackHitResult.GetActor()->GetName());

		StopAttackTimer();

		UGameplayStatics::ApplyDamage(TraceAttackHitResult.GetActor(), BaseDamage, EventInstigator, DamageCauser, DamageTypeClass);
	}
}

void UMeleeAttackComponent::StartAttackTimer(FVector StartTrace, FVector EndTraceUnit, float BaseDamage, AController* EventInstigator, AActor* DamageCauser)
{
	//DEBUGMESSAGE("StartAttackTimer");
	//AttackTimerDelegate.BindUFunction(this, FName("DoAttack"), StartTrace, EndTraceUnit, BaseDamage, EventInstigator, DamageCauser);
	FTimerDelegate AttackTimerDelegate = FTimerDelegate::CreateUObject(this, &UMeleeAttackComponent::DoAttack, StartTrace, EndTraceUnit, BaseDamage, EventInstigator, DamageCauser);
	GetWorld()->GetTimerManager().SetTimer(AttackTimer, AttackTimerDelegate, AttackTimerDeltaTime, true);
	GetWorld()->GetTimerManager().SetTimer(CheckAttackTimerTimer, this, &UMeleeAttackComponent::CheckAttackTimer, CheckAttackTimerTimerDeltaTime);
}

void UMeleeAttackComponent::StopAttackTimer()
{
	//DEBUGMESSAGE("StopAttackTimer");
	GetWorld()->GetTimerManager().ClearTimer(AttackTimer);
	GetWorld()->GetTimerManager().ClearTimer(CheckAttackTimerTimer);
}

bool UMeleeAttackComponent::TraceAttack(FHitResult& OutHit, FVector StartTrace, FVector EndTraceUnit)
{
	if (!GetWorld())
	{
		DEBUGMESSAGE("!GetWorld()");
		return false;
	}
	//DEBUGMESSAGE("TraceAttack");
	FVector EndTrace = StartTrace + EndTraceUnit * AttackLengthTrace;

	bool bTraceResult = UKismetSystemLibrary::SphereTraceSingle(
		GetWorld(),
		StartTrace,
		EndTrace,
		TraceSphereRadius,
		TraceCollisionChannel,
		bTraceComplex,
		IgnoredActors,
		DrawDebugType,
		OutHit,
		bIgnoreSelf,
		TraceColor,
		TraceHitColor,
		DrawTime
	);
	return bTraceResult;
}

void UMeleeAttackComponent::CheckAttackTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(AttackTimer);
}






