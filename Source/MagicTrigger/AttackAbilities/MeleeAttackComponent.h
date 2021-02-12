// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Для атаки ближнего боя. Основной метод - DoAttack, который выполняется в таймере, трейсит цель и наносит ей повреждения.
 */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MeleeAttackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Category = "MeleeAttackComponent" )
class MAGICTRIGGER_API UMeleeAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMeleeAttackComponent();


	/**
	 * Variables
	 */

public:

	/**
	 * Длина трейса.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeleeAttackComponent")
		float AttackLengthTrace; 

	/**
	 * Радиус трейс-сферы.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeleeAttackComponent")
		float TraceSphereRadius;

	/**
	 * Канал коллизии трейса.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeleeAttackComponent")
		TEnumAsByte<ECollisionChannel> TraceCollisionChannel;

	/**
	 * Комплексный или простой трейс.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeleeAttackComponent")
		bool TraceComplex;

	/**
	 * Показывать ли дебаг-линию трейса.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeleeAttackComponent")
		bool bDrawDebugTrace;

	/**
	 *  Таймер, по которому выполняется DoAttack() для трейса цели.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeleeAttackComponent")
		FTimerHandle AttackTimer;


	/**
	 * Methods
	 */

public:

	/**
	 * Ищет трейсом цель и если найдена, то наносит повреждения цели. Выполняется по таймеру для поиска цели в процессе движения источника трейса.
	 */
	UFUNCTION(BlueprintCallable, Category = "MeleeAttackComponent")
		void DoAttack
		(
			const FVector& StartTrace, 
			const FVector& EndTraceUnit, 
			const TArray<AActor*>& IgnoredActors, 
			float BaseDamage, 
			AController* EventInstigator, 
			AActor* DamageCauser, 
			TSubclassOf<UDamageType> DamageTypeClass
		);

private:
	/**
	 * Вычисляет данные для трейса и делает трейс.
	 */
	bool TraceAttack
	(
		FHitResult& OutHit, 
		const FVector& StartTrace, 
		const FVector& EndTraceUnit, 
		const TArray<AActor*>& IgnoredActors
	);

};
