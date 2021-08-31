// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.

#pragma once

#include "MagicTrigger/UI/ParentUserWidgetMT.h"
#include "ObserveEnemyUserWidget.generated.h"

class UImage;
class UProgressBar;
class UTextBlock;

/**
 *
 */
UCLASS()
class MAGICTRIGGER_API UObserveEnemyUserWidget : public UParentUserWidgetMT
{
	GENERATED_BODY()
public:
	UObserveEnemyUserWidget();


public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "ObserveEnemyUserWidget")
		UImage* EnemyLifeImage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "ObserveEnemyUserWidget")
		UImage* IconImage;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "ObserveEnemyUserWidget")
		UProgressBar* EnemyLifeProgressBar;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "ObserveEnemyUserWidget")
		UTextBlock* NameTextBlock;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ObserveEnemyUserWidget")
		FSlateBrush IconBrush;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ObserveEnemyUserWidget")
		float GetLife();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ObserveEnemyUserWidget")
		FText GetTextLife();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ObserveEnemyUserWidget")
		FSlateBrush GetIcon();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ObserveEnemyUserWidget")
		FText GetTextName();
};
