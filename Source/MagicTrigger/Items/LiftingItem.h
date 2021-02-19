// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Родительский класс поднимаемых и таскаемых предметов.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagicTrigger\Interfaces\LiftingItemInterface.h"
#include "LiftingItem.generated.h"

class UBoxComponent;

UCLASS()
class MAGICTRIGGER_API ALiftingItem : public AActor, public ILiftingItemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALiftingItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	/**
	 *
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiftingItem")
		FName AttachSocket;

	/**
	 *
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LiftingItem")
		UBoxComponent* Box;

	/**
	 * Interface methods.
	 */
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "LiftingItem|LiftingItemInterface")
		FName GetAttachSocket_IF() const;
	virtual FName GetAttachSocket_IF_Implementation() const override;

};
