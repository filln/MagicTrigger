// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "SFSphereAbilityUserWidget.h"
#include "Components/TextBlock.h"

USFSphereAbilityUserWidget::USFSphereAbilityUserWidget()
{

	Count = 0;
}

void USFSphereAbilityUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CountText->SetText(FText::FromString(FString("0")));
}
