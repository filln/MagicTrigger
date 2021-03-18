// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

/**
 * Анимации Демона.
 */

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "DemonAnimInstance.generated.h"

class ADemonCharacter;

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API UDemonAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UDemonAnimInstance();

	/**
	 * Variables
	 */
public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "DemonAnimInstance")
		ADemonCharacter* Demon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DemonAnimInstance")
		float Speed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "DemonAnimInstance")
		bool bAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DemonAnimInstance")
		bool bDying;


	/**
	 * Methods
	 */

private:
	// Executed when begin play is called on the owning component
	virtual void NativeBeginPlay() override;
	/** Executed when the Animation is updated */
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	/**
	 * Получить и проверить ссылки.
	 */
	bool GetAndCheckReferences();

public:
	/**
	 * Methods for AnimNotifies.
	 */

	UFUNCTION(BlueprintCallable, Category = "DemonAnimInstance|AnimNotifies")
		void CreateFireBall();
	UFUNCTION(BlueprintCallable, Category = "DemonAnimInstance|AnimNotifies")
		void MoveFireBallToTarget();


};
