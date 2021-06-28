// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.
/**
 * Последняя, 7я копия сферы
 */
#pragma once

#include "CoreMinimal.h"
#include "MagicTrigger/AbilitySystem/SevenfoldShere/SevenfoldShere.h"
#include "LastCopyOfSSphere.generated.h"

class URotatingMovementComponent;

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API ALastCopyOfSSphere : public ASevenfoldShere
{
	GENERATED_BODY()

public:
	ALastCopyOfSSphere();

public:
	UPROPERTY()
		UMaterialInterface* SourceMaterialTranslucent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LastCopyOfSSphere|Settings")
		FName OpacityName;

private:
	URotatingMovementComponent* RotatingMovementComponent;
	bool bOverlapPossible;

public:
	//Box->OnComponentBeginOverlap
	UFUNCTION()
		void Rotate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
