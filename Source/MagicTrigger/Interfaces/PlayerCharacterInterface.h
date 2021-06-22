// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Интерфейс для класса PlayerCharacterMagicTrigger. Используется для вызова методов класса, получения и определения переменных.
 */

#pragma once

#include "CoreMinimal.h"
#include "MagicTrigger/Interfaces/InterfaceCheck.h"
#include "PlayerCharacterInterface.generated.h"

class UTextureRenderTarget2D;
class UCapsuleComponent;
class USkeletalMeshComponent;

// This class does not need to be modified.
UINTERFACE(Blueprintable, Category = "PlayerCharacterInterface")
class UPlayerCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MAGICTRIGGER_API IPlayerCharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerCharacterInterface")
		UTextureRenderTarget2D* CreateScreenShot_IF();
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerCharacterInterface")
	//	void DestroyLiftUpObject_IF();

	/**
	 * Getters
	 */

	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerCharacterInterface|Getters")
	//	FTransform GetSocketTransform_IF(FName& SocketName) const;
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerCharacterInterface|Getters")
	//	UCapsuleComponent* GetInteractCollision_IF() const;
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerCharacterInterface|Getters")
	//	FVector GetUpDownLiftingArrowForwardVector_IF() const;
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerCharacterInterface|Getters")
	//	FTransform GetPointPutDownTransform_IF() const;
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerCharacterInterface|Getters")
	//	FTransform GetPointStartTraceToPutDownPointTransform_IF() const;
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerCharacterInterface|Getters")
	//	USkeletalMeshComponent* GetMesh_IF() const;

};
