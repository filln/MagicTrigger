// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 *Отвечает за работу абилки семикратной сферы.
 */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SevenfoldSphereComponent.generated.h"

class AAbilitySystemManager;
class AFirstCopiesOfSSphere;
class ALastCopyOfSSphere;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSevenfoldSphereFinish);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Category = "SevenfoldSphereComponent")
class MAGICTRIGGER_API USevenfoldSphereComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USevenfoldSphereComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/**
 * Variables
 */
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SevenfoldSphereComponent")
		FVector SpawnScale;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SevenfoldSphereComponent")
		FName AttachSocket;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SevenfoldSphereComponent")
		float MoveFirstSpheresToLastOverTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SevenfoldSphereComponent")
		float DeltaYawDegree;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SevenfoldSphereComponent")
		float MaxEmissiveFirstSpheres;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SevenfoldSphereComponent")
		float IncreaseMiddleScaleLastSphereTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SevenfoldSphereComponent")
		float IncreaseScaleAndEmissiveLastSphereTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SevenfoldSphereComponent")
		float MaxEmissiveLastSphere;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SevenfoldSphereComponent")
		float MaxMiddleScaleLastSphereMultiplier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SevenfoldSphereComponent")
		float MaxScaleLastSphereMultiplier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "SevenfoldSphereComponent")
		float Damage;
	UPROPERTY(BlueprintAssignable, Category = "SevenfoldSphereComponent")
		FOnSevenfoldSphereFinish OnSevenfoldSphereFinish;
	UPROPERTY()
		ALastCopyOfSSphere* LastSSphere;
	UPROPERTY()
		TArray<AFirstCopiesOfSSphere*> SpheresArray;
	UPROPERTY()
		FTimerHandle RotateAndOffsetFirstSpheresTimer;
	UPROPERTY()
		FTimerHandle IncreaseEmissiveFirstSpheresTimer;
	UPROPERTY()
		FTimerHandle LastSphereTimer;
private:
	bool bUsePossible;
	int CountOfSpheres;
	AAbilitySystemManager* AbilitySystemManager;
	float DeltaEmissiveFirstSpheres;
	float CurrentEmissiveFirstSpheres;
	float DeltaEmissiveLastSphere;
	float CurrentEmissiveLastSphere;
	float CurrentScaleLastSphereMultiplier;
	float DeltaMiddleScaleLastSphereMultiplier;
	float DeltaScaleLastSphereMultiplier;
	float CurrentOpacityLastSphere;
	float DeltaOpacityLastSphere;
	float TimersDeltaTime;

	//RotateFirstSpheresAroundLast()
	int CountTimerStep;
	int CurrentStep;

public:

	/**
	 *Вызывается после нажатия клавиши атаки. BlueprintCallable для тестирования, можно вызвать в BP_AbilitySystemManager.
	 */
	UFUNCTION(BlueprintCallable, Category = "SevenfoldSphereComponent")
		void Use();
	/**
	 * Вызывается из анимации AS_Player_SpawnSSphere с помощью AnimNotify
	 */
	void SpawnSSphere();
	int GetCountOfSpheres() const;

private:
	void IncreaseCountOfSpheres();
	void ResetCountOfSpheres();
	/**
	 * Начать работу абилки: визуальная часть, нанесение урона.
	 */
	void ActivateAbility();
	void RotateAndOffsetFirstSpheresAroundLast();
	void IncreaseEmissiveFirstSpheres();
	void IncreaseToMiddleScaleLastSphere();
	void ActivateLastSphere();
	void DestroyFirstSpheres();
	void IncreaseScaleAndEmissiveLastSphere();
	void DoDamage();
	void DecreaseEmissiveLastSphere();
	void DecreaseOpacityLastSphere();
	void Finish();
};
