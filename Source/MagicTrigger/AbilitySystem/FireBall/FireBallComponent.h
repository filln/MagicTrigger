// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Компонент атакующей абилки фаербола. Присоединяется к ACharater.
 */
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MagicTrigger\Data\AbilitySystem\FireBallStruct.h"
#include "MagicTrigger\Data\AbilitySystem\FireBallMoveToTargetInputsStruct.h"
#include "FireBallComponent.generated.h"

class USkeletalMeshComponent;
class UDamageType;
class AFireBall;
class AController;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MAGICTRIGGER_API UFireBallComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFireBallComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/**
	 * Variables
	 */
public:

	/**
	 *
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UFireBallComponent|Settings")
		FFireBallStruct FireBallStruct;
	/**
	 *
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UFireBallComponent|Settings")
		TSubclassOf<UDamageType> DamageTypeClass;
	/**
	 *
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UFireBallComponent|Settings")
		FName OwnersAttachSocket;
	/**
	 *
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UFireBallComponent|Settings")
		float ScaleAndEmissiveTimerTime;
	/**
	 *
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UFireBallComponent|Settings")
		FName TextureParameterName;
	/**
	 *
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UFireBallComponent|Settings")
		FName EmissiveColorParameterName;
	/**
	 *
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UFireBallComponent|Settings")
		FName EmissiveMultiplierParameterName;

private:
	/**
	 *
	 */
	UPROPERTY()
		AFireBall* FireBallInHands;
	/**
	 *
	 */
	UPROPERTY()
		AFireBall* FireBallInFly;
	/**
	 *
	 */
	UPROPERTY()
		USkeletalMeshComponent* OwnersMesh;
	/**
	 *
	 */
	UPROPERTY()
		AActor* Owner;
	/**
	 *
	 */
	UPROPERTY()
		UMaterialInstanceDynamic* FireBallInHandsMaterial;
	/**
	 *
	 */
	UPROPERTY()
		UMaterialInstanceDynamic* FireBallInFlyMaterial;
	/**
	 *
	 */
	UPROPERTY()
		FTimerHandle ScaleAndEmissiveTimer;
	/**
	 *
	 */
	float DeltaMultiplierOfScaleEveryTick;
	/**
	 *
	 */
	float DeltaMultiplierOfEmissiveEveryTick;
	/**
	 *
	 */
	float CountOfTimerStepsInHands;
	/**
	 *
	 */
	UPROPERTY()
		FFireBallMoveToTargetInputsStruct FireBallMoveToTargetInputsStruct;

	/**
	 * Methods
	 */
public:
	/**
	 *
	 */
	void CreateFireBall(USkeletalMeshComponent* InOwnersMesh);
	/**
	 *
	 */
	void MoveFireBallToTarget(AController* OwnersController, AActor* BallsTarget);

private:

	/**
	 *
	 */
	float CalcDeltaEveryTick(float MaxValue, float CurrentValue, float CountOfTicks);
	/**
	 *
	 */
	float CalcCountOfStepsInHands();
	/**
	 *
	 */
	UMaterialInstanceDynamic* CreateMaterialFireBall(AFireBall* FireBall);
	/**
	 *
	 */
	void ScaleAndEmissive();

};
