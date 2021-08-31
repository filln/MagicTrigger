// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.


#include "LastCopyOfSSphere.h"
#include "Components/BoxComponent.h"
#include "MagicTrigger/Data/CollisionChannelsMagicTrigger.h"
#include "MagicTrigger/AbilitySystem/SevenfoldSphere/FirstCopiesOfSSphere.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "MagicTrigger/Data/DebugMessage.h"

ALastCopyOfSSphere::ALastCopyOfSSphere()
{
	bOverlapPossible = true;
	Box->OnComponentBeginOverlap.AddDynamic(this, &ALastCopyOfSSphere::Rotate);

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
	RotatingMovementComponent->RotationRate.Yaw = 0;
	Number = 7;
	OpacityName = FName(TEXT("Opacity"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> SourceMaterialTranslucentInterfaceObj(TEXT("/Game/MagicTrigger/Materials/AbilitySystem/M_AttackAbility_Translucent"));
	if (SourceMaterialTranslucentInterfaceObj.Succeeded())
	{
		SourceMaterialTranslucent = SourceMaterialTranslucentInterfaceObj.Object;
	}
	else
	{
		DEBUGMESSAGE("!SourceMaterialTranslucentInterfaceObj.Succeeded()");
	}
}

void ALastCopyOfSSphere::Rotate(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bOverlapPossible)
	{
		return;
	}
	AFirstCopiesOfSSphere* Sphere = Cast<AFirstCopiesOfSSphere>(OtherActor);
	if (!Sphere)
	{
		return;
	}
	RotatingMovementComponent->RotationRate.Yaw = 180;
	bOverlapPossible = false;
}
