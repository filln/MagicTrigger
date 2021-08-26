// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Для атаки ближнего боя. Основной метод - DoAttack, который выполняется в таймере, трейсит цель и наносит ей повреждения.
 */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
 #include "Kismet\KismetSystemLibrary.h"
#include "MeleeAttackComponent.generated.h"

class UDamageType;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Category = "MeleeAttackComponent")
class MAGICTRIGGER_API UMeleeAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMeleeAttackComponent();
protected:
	virtual void BeginPlay() override;

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
		TEnumAsByte<ETraceTypeQuery> TraceCollisionChannel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeleeAttackComponent")
		bool bTraceComplex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeleeAttackComponent")
		bool bIgnoreSelf;

	/**
	 * Тип дебаг-линии трейса.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeleeAttackComponent")
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeleeAttackComponent")
		FLinearColor TraceColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeleeAttackComponent")
		FLinearColor TraceHitColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeleeAttackComponent")
		float DrawTime;
	/**
	 * Период таймера.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeleeAttackComponent")
		float AttackTimerDeltaTime;
	/**
	 * Задержка таймера, который проверяет остановку таймера атаки, т.к. при смешивании анимаций
	 в RandomSequencePlayer иногда проигрывается кусок анимации, который запускает таймер атаки.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeleeAttackComponent")
		float CheckAttackTimerTimerDeltaTime;

	/**
	 *
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MeleeAttackComponent")
		TSubclassOf<UDamageType> DamageTypeClass;

	/**
	 *  Таймер, по которому выполняется DoAttack() для трейса цели.
	 */
	UPROPERTY()
		FTimerHandle AttackTimer;
	UPROPERTY()
		TArray<AActor*> IgnoredActors;

private:
	FTimerHandle CheckAttackTimerTimer;
	/**
	 * Methods
	 */

public:

	/**
	 * Ищет трейсом цель и если найдена, то наносит повреждения цели. Выполняется по таймеру для поиска цели в процессе движения источника трейса.
	 */
	UFUNCTION()
		void DoAttack (
			FVector StartTrace,
			FVector EndTraceUnit,
			float BaseDamage,
			AController* EventInstigator,
			AActor* DamageCauser
		);
	/**
	 * Запустить таймер.
	 */
	UFUNCTION()
		void StartAttackTimer (
			FVector StartTrace,
			FVector EndTraceUnit,
			float BaseDamage,
			AController* EventInstigator,
			AActor* DamageCauser
		);
	/**
	 * Остановить таймер.
	 */
	UFUNCTION()
		void StopAttackTimer();
	/**
	 * Вычисляет данные для трейса и делает трейс.
	 */
	UFUNCTION()
	bool TraceAttack (
		FHitResult& OutHit,
		FVector StartTrace,
		FVector EndTraceUnit
	);

	private:
		void CheckAttackTimer();

};
