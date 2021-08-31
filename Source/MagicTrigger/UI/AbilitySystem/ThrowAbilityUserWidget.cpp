// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "ThrowAbilityUserWidget.h"
#include "Components/TextBlock.h"

UThrowAbilityUserWidget::UThrowAbilityUserWidget()
{

}

void UThrowAbilityUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CountText->SetText(FText::FromString(FString("0")));
}