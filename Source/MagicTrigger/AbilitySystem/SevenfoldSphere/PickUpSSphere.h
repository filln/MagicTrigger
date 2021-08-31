// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved.
/**
 * Служит для визуализации
приобретения абилки.
При оверлапе персом
включается и двигается
 к нему
 */
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "PickUpSSphere.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class URotatingMovementComponent;
class APlayerCharacterMagicTrigger;
class UMaterialInstanceDynamic;
class UCurveFloat;
class UBillboardComponent;
class USpotLightComponent;

UCLASS()
class MAGICTRIGGER_API APickUpSSphere : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickUpSSphere();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	/**
	 * Variables
	 */
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Components")
		UBoxComponent* SwitchOnCollision;
	/**
	 * Для оверлапа перса, когда включаются фонарики.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Components")
		UBoxComponent* LittleSphereCentralPointCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Components")
		UStaticMeshComponent* BigSphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Components")
		UBillboardComponent* LittleSpheresCentralPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Components")
		UStaticMeshComponent* LittleSphere1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Components")
		UStaticMeshComponent* LittleSphere2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Components")
		UStaticMeshComponent* LittleSphere3;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Components")
		UStaticMeshComponent* LittleSphere4;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Components")
		UStaticMeshComponent* LittleSphere5;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Components")
		UStaticMeshComponent* LittleSphere6;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Components")
		UStaticMeshComponent* LittleSphere7;

	/**
	 * Точки, в которые будут двигаться маленькие сферы.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Components")
		UBillboardComponent* LittleSpherePoint1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Components")
		UBillboardComponent* LittleSpherePoint2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Components")
		UBillboardComponent* LittleSpherePoint3;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Components")
		UBillboardComponent* LittleSpherePoint4;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Components")
		UBillboardComponent* LittleSpherePoint5;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Components")
		UBillboardComponent* LittleSpherePoint6;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Components")
		UBillboardComponent* LittleSpherePoint7;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Components")
		USpotLightComponent* SpotLight1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Components")
		USpotLightComponent* SpotLight2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Components")
		USpotLightComponent* SpotLight3;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Components")
		USpotLightComponent* SpotLight4;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Components")
		USpotLightComponent* SpotLight5;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Components")
		USpotLightComponent* SpotLight6;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Components")
		USpotLightComponent* SpotLight7;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Components")
		URotatingMovementComponent* RotatingMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Settings")
		float MoveUpOverTime;
	//Высота подъема сферы относительно высоты перса.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Settings")
		float MoveUpHeigh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Settings")
		float MoveToCharacterOverTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Settings")
		float FirstMaxEmissive;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Settings")
		float SecondMaxEmissive;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Settings")
		float MaxScale;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Settings")
		float MinOpacity;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Settings")
		float MoveLittleSpheresHorizontalOverTime;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Settings|SpotLight")
		float SpotLightIntensity;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Settings|SpotLight")
		float SpotLightAttenuationRadius;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Settings|SpotLight")
		float SpotLightInnerConeAngle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Settings|SpotLight")
		float SpotLightOuterConeAngle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Settings|SpotLight")
		FLinearColor SpotLightColor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Settings")
		float LittleSpheresDownLocationZ;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Settings")
		float IncreaseEmissiveCurveLength;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Settings")
		float IncreaseScaleAndEmissiveCurveLength;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PickUpSSphere|Settings")
		float DecreaseOpacityCurveLength;

	//Timeline
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUpSSphere|Settings")
		UCurveFloat* IncreaseEmissiveCurve;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUpSSphere|Settings")
		UCurveFloat* IncreaseScaleAndEmissiveCurve;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUpSSphere|Settings")
		UCurveFloat* DecreaseOpacityCurve;

	//Material
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUpSSphere|Settings")
		FName EmissiveMultiplierName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUpSSphere|Settings")
		FName OpacityName;
	UPROPERTY()
		UMaterialInstanceDynamic* BigSphereMaterial;
	UPROPERTY()
		UMaterialInstanceDynamic* LittleSpheresMaterial;
	UPROPERTY()
		UMaterialInterface* SourceMaterialOpaque;
	UPROPERTY()
		UMaterialInterface* SourceMaterialTranslucent;

private:
	APlayerCharacterMagicTrigger* PlayerCharacter;
	FVector InitialScale;
	bool bWasOverlapLittleSphereCentralPointCollision;
	TArray<USpotLightComponent*> SpotLightArray;
	TArray<UStaticMeshComponent*> LittleSpheresArray;
	//Timeline
	UTimelineComponent* IncreaseEmissiveTimeline;
	UTimelineComponent* IncreaseScaleAndEmissiveTimeline;
	UTimelineComponent* IncreaseEmissiveLittleSpheresTimeline;
	UTimelineComponent* DecreaseEmissiveLittleSpheresTimeline;
	UTimelineComponent* DecreaseOpacityTimeline;
	UTimelineComponent* DecreaseScaleAndOpacityTimeline;

	int MoveComponentToCounter;

	/**
	 * Methods
	 */
private:
	void SetupLittleSpherePoints(UBillboardComponent* InLittleSpherePoint, FVector InLocation);
	void SetupSpotLights(USpotLightComponent* InSpotLight, UBillboardComponent* InParentComponent, FRotator InRotation);
	void SetupLittleSpheres(UStaticMeshComponent* InLittleSphere);
public:
	//LittleSphereCentralPointCollision->OnComponentBeginOverlap
	UFUNCTION()
		void SwitchOnSpotLight(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//LittleSphereCentralPointCollision->OnComponentEndOverlap
	UFUNCTION()
		void SwitchOffSpotLight(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	//SwitchOnCollision->OnComponentBeginOverlap
	UFUNCTION()
		void SwitchOn(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
	void SetEnableCharacterMovement(bool bInEnable);
	void IncreaseEmissive();
public:
	UFUNCTION()
		void IncreaseEmissiveTimelineUpdate(float InAlpha);
	UFUNCTION()
		void MoveUp();
	UFUNCTION()
		void MoveToCharacter();
	UFUNCTION()
		void IncreaseScaleAndEmissive();
	UFUNCTION()
		void IncreaseScaleAndEmissiveTimelineUpdate(float InAlpha);
	UFUNCTION()
		void MoveLittleSpheresOutside();
	UFUNCTION()
		void IncreaseEmissiveLittleSpheres();
	UFUNCTION()
		void IncreaseEmissiveLittleSpheresTimelineUpdate(float InAlpha);
	UFUNCTION()
		void MoveLittleSpheresVertical();
	UFUNCTION()
		void DecreaseEmissiveLittleSpheres();
	UFUNCTION()
		void MoveLittleSpheresInside();
	UFUNCTION()
		void DecreaseOpacity();
	UFUNCTION()
		void DecreaseOpacityTimelineUpdate(float InAlpha);
	UFUNCTION()
		void MoveBigSphereDown();
	UFUNCTION()
		void DecreaseScaleAndOpacity();
	UFUNCTION()
		void DecreaseScaleAndOpacityTimelineUpdate(float InAlpha);
	UFUNCTION()
		void Finish();
private:
	void SwitchOnSSphereAbility();



};
