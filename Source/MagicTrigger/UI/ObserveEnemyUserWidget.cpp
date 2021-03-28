// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "ObserveEnemyUserWidget.h"
#include "MagicTrigger\Interfaces\EnemyCharacterInterface.h"
#include "MagicTrigger\Data\DebugMessage.h"
#include "MagicTrigger\CoreClasses\HUDMagicTrigger.h"
#include "Kismet\KismetTextLibrary.h"

class UTexture2D;


UObserveEnemyUserWidget::UObserveEnemyUserWidget()
{
	IconBrush.ImageSize.X = 180;
	IconBrush.ImageSize.Y = 180;
	IconBrush.DrawAs = ESlateBrushDrawType::Image;
	IconBrush.Tiling = ESlateBrushTileType::NoTile;
	IconBrush.Mirroring = ESlateBrushMirrorType::NoMirror;
}

float UObserveEnemyUserWidget::GetLife()
{
	if (!IsInterfaceImplementedBy<IEnemyCharacterInterface>(this->HUDMagicTrigger->Enemy))
	{
		//DEBUGMESSAGE("!IsInterfaceImplementedBy<IEnemyCharacterInterface>(this->HUDMagicTrigger->Enemy)");
		return 0;
	}

	float Life = IEnemyCharacterInterface::Execute_GetLife_IF(this->HUDMagicTrigger->Enemy);
	float MaxLife = IEnemyCharacterInterface::Execute_GetMaxLife_IF(this->HUDMagicTrigger->Enemy);
	if (MaxLife <= 0 || Life <= 0)
	{
		return 0;
	}

	return Life / MaxLife;
}

FText UObserveEnemyUserWidget::GetTextLife()
{
	//if (!this->HUDMagicTrigger->Enemy)
	//{
	//	DEBUGMESSAGE("!this->HUDMagicTrigger->Enemy");
	//}
	if (!IsInterfaceImplementedBy<IEnemyCharacterInterface>(this->HUDMagicTrigger->Enemy))
	{
		//DEBUGMESSAGE("!IsInterfaceImplementedBy<IEnemyCharacterInterface>(this->HUDMagicTrigger->Enemy)");
		return FText();
	}

	float Life = IEnemyCharacterInterface::Execute_GetLife_IF(this->HUDMagicTrigger->Enemy);
	return UKismetTextLibrary::Conv_FloatToText(Life, ERoundingMode::HalfToEven, false, false, 1, 324, 0, 0);
}

FSlateBrush UObserveEnemyUserWidget::GetIcon()
{
	if (!IsInterfaceImplementedBy<IEnemyCharacterInterface>(this->HUDMagicTrigger->Enemy))
	{
		//DEBUGMESSAGE("!IsInterfaceImplementedBy<IEnemyCharacterInterface>(this->HUDMagicTrigger->Enemy)");
		return FSlateBrush();
	}

	UTexture2D* IconImageTmp = IEnemyCharacterInterface::Execute_GetIcon_IF(this->HUDMagicTrigger->Enemy);
	this->IconBrush.SetResourceObject(IconImageTmp);
	return this->IconBrush;

}

FText UObserveEnemyUserWidget::GetTextName()
{
	if (!IsInterfaceImplementedBy<IEnemyCharacterInterface>(this->HUDMagicTrigger->Enemy))
	{
		//DEBUGMESSAGE("!IsInterfaceImplementedBy<IEnemyCharacterInterface>(this->HUDMagicTrigger->Enemy)");
		return FText();
	}

	return IEnemyCharacterInterface::Execute_GetName_IF(this->HUDMagicTrigger->Enemy);
}
