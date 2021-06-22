// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Статуя здоровья, восполняет здоровье персу.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagicTrigger\Interfaces\InteractionInterface.h"
#include "TargetSelectionPlugin\Public\TargetSelectionInterface.h"
#include "Components\TimelineComponent.h"
#include "LifeStatue.generated.h"

class APlayerCharacterMagicTrigger;
class UStaticMeshComponent;
class UPointLightComponent;
class USpotLightComponent;
class UBoxComponent;
class UCapsuleComponent;
class UCurveFloat;

UCLASS()
class MAGICTRIGGER_API ALifeStatue : public AActor,
	public IInteractionInterface,
	public ITargetSelectionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALifeStatue();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * Variables
	 */
public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "LifeStatue|Components")
		UCapsuleComponent* CapsuleCollision;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "LifeStatue|Components")
		UBoxComponent* InteractCollision;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "LifeStatue|Components")
		UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "LifeStatue|Components")
		UPointLightComponent* PointLight;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "LifeStatue|Components")
		USpotLightComponent* SpotLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LifeStatue")
		FVector InitialLocationCharacter;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LifeStatue")
		float CurrentIntensityPointLight;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LifeStatue")
		float CurrentLife;
	//Максимум жизни, до которого может отхилить статуя. На данный момент MaxLife = GetMaxLife();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LifeStatue")
		float MaxLife;

	//Скорость лечения в единицах в секунду.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LifeStatue|Settings")
		float SpeedHealing;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LifeStatue|Settings")
		float MaxIntensitySpotLight;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LifeStatue|Settings")
		float MaxIntensityPointLight;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LifeStatue|Settings")
		float MaxAttenuationRadiusPointLight;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LifeStatue|Settings")
		FText InteractionText;

	//Timeline
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LifeStatue|Settings")
		UCurveFloat* BeginInteractCurve;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LifeStatue|Settings")
		UCurveFloat* AddLifeCurve;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LifeStatue|Settings")
		UCurveFloat* AddLifePointLightCurve;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LifeStatue|Settings")
		UCurveFloat* ReverseIntensityLightCurve;


private:
	FTimerHandle BeginPlayTimer;
	APlayerCharacterMagicTrigger* PlayerCharacter;
	UActorComponent* AnimationManager;

	UTimelineComponent* BeginInteractTimeline;
	UTimelineComponent* AddLifeTimeline;
	UTimelineComponent* ReverseIntensityLightTimeline;

	FOnTimelineFloat BeginInteractDelegate;
	FOnTimelineFloat AddLifeDelegate;
	FOnTimelineFloat ReverseIntensityLightDelegate;

	FOnTimelineEvent BeginInteractFinishedDelegate;
	FOnTimelineEvent AddLifeFinishedDelegate;
	FOnTimelineEvent ReverseIntensityLightFinishedDelegate;


	/**
	 * Methods
	 */

public:
	UFUNCTION()
		void BeginInteractTimelineFunction(float InAlphaIntensity);
	UFUNCTION()
		void AddLifeTimelineFunction(float InAlphaLife);
	UFUNCTION()
		void ReverseIntensityLightTimelineFunction(float InAlphaIntensity);
	UFUNCTION()
		void SetCanInteractTrue();
	void SetCanInteractFalse();

private:
	float GetLife() const;
	float GetMaxLife() const;
	UFUNCTION()
		void AddLife();
	UFUNCTION()
		void ReverseIntensityLight();
	void StopAddingLife();

public:
	/**
	 * Interfaces methods
	 */

	/**
	 * InteractionInterface
	 */
	virtual FText GetInteractionText_IF_Implementation() const override;
	virtual void Interact_IF_Implementation(APlayerCharacterMagicTrigger* InPlayerCharacter) override;

	/**
	 * TargetSelectionInterface
	 */
	virtual void IsObserved_Implementation() override;
	virtual void IsNotObserved_Implementation() override;

};

/**
 *
 After trying this before I thought I give this timeline in c++ another shot. There are still some old answers here on answerhub which show how to use timelines in c++ with the actor's own tick function. But actually it also works withouth using the tick of the actor. I had to use AddInterpFloat() at runtime to get this to run.

This answer should work for you!

//.h

 UPROPERTY()
 UTimelineComponent* ScoreTimeline;

 UPROPERTY()
 UCurveFloat* fCurve;

 FOnTimelineFloat InterpFunction{};

//.cpp

//Constructor:

 static ConstructorHelpers::FObjectFinder<UCurveFloat> Curvy(TEXT("CurveFloat'/Game/Blueprints/NotSoImportant/CurveFloatBP.CurveFloatBP'"));
 if (Curvy.Object) {
	 fCurve = Curvy.Object;
 }

 ScoreTimeline = ObjectInitializer.CreateDefaultSubobject<UTimelineComponent>(this, TEXT("TimelineScore"));

 InterpFunction.BindUFunction(this, FName{ TEXT("TimelineFloatReturn") });


//Then inside BeginPlay for example:

 ScoreTimeline->AddInterpFloat(fCurve, InterpFunction, FName{ TEXT("Floaty") });
 ScoreTimeline->Play(); // or PlayFromStart() etc, can be called anywhere in this class

//And Finally your callback function:

 void AYourClass::TimelineFloatReturn(float val)
 {
  //Your float val from curve returns here
 }
 */

 ///////////////////////////////////////////////////////////////////////////////
 /**
  *
  Effect.h:

 FTimeline TimeLine;

 /** Deltatime(stepsize) for the timer calling the timeline tick
 static const float DELTATIME;

 /** Function which gets called from the Timer to call EffectProgress
 void TickTimeline();

 /** Function which gets called from the Timeline on a Tick
 UFUNCTION()
 void EffectProgress(float Value);

 Effect.cpp:
 Constructor:

 const ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("CurveFloat'/Game/OwnStuff/EffectCurve.EffectCurve'"));
 TimeLine = FTimeline{};
 FOnTimelineFloat progressFunction{};
 progressFunction.BindUFunction(this, "EffectProgress"); // The function EffectProgress gets called
 TimeLine.AddInterpFloat(Curve.Object, progressFunction, FName{ TEXT("EFFECTFADE") });

 BeginPlay:

 TimeLine.PlayFromStart();
 FTimerHandle TimerHandle;
 GetWorldTimerManager().SetTimer(TimerHandle, this, &AEffectBallSpeed::TickTimeline, DELTATIME, true, 0.0f);

 Called Function from Timeline

 /** The function which gets called from the timeline tick
 void AEffectBallSpeed::EffectProgress(float Value)
 {
	 GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("EffectProgress: timeline: %f value:%f"), TimeLine.GetPlaybackPosition(), Value)); // do something
 }

	 Called Function from Timer

		 /** Function which gets called from the Timer to call EffectProgress
		 void AEffectBallSpeed::TickTimeline()
	 {
		 if (TimeLine.IsPlaying())
		 {
			 TimeLine.TickTimeline(DELTATIME);
		 }
		 else
		 {
			 GetWorldTimerManager().ClearTimer(this, &AEffectBallSpeed::TickTimeline); SetLifeSpan(0);
		 }
	 }

  */