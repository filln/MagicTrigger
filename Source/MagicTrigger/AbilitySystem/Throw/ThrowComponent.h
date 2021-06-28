// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.
/**
 * Для метания предметов.
 */
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ThrowComponent.generated.h"

class AThrowableItem;
class AAbilitySystemManager;
class USkeletalMeshComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MAGICTRIGGER_API UThrowComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UThrowComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/**
	 * Variables
	 */
private:
	AAbilitySystemManager* AbilitySystemManager;
	USkeletalMeshComponent* PlayerCharacterMesh;
	int CountOfThrowableItem;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ThrowComponent")
		TSubclassOf<AThrowableItem> ThrowableItemClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ThrowComponent")
		FName AttachSocket;
	UPROPERTY()
		AThrowableItem* ThrowableItemInHand;
	UPROPERTY()
		AThrowableItem* ThrowableItemInFly;

	/**
	 * Methods
	 */
public:
	int GetCountOfThrowableItem() const;
	void SetCountOfThrowableItem(int InCount);
	void IncreaseCountOfThrowableItem();
	void DecreaseCountOfThrowableItem();

	void SpawnThrowableItem();
	void Throw();

private:
	AThrowableItem* SpawnThrowableItem_Internal();
};
