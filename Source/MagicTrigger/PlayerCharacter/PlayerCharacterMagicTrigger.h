// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Персонаж игры.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MagicTrigger/Interfaces/AnimationManagerInterface.h"
#include "MagicTrigger\Interfaces\OwnerTargetSelectionInterface.h"
#include "MagicTrigger\Interfaces\PlayerCharacterInterface.h"
#include "MagicTrigger\Data\MovementStatusEnum.h"
#include "InputCoreTypes.h"
#include "PlayerCharacterMagicTrigger.generated.h"

class UActorComponent;
class UCapsuleComponent;
class UArrowComponent;
class UMeleeAttackComponent;
class USceneComponent;
class UUpDownLiftingItemComponent;
class UAnimationManagerComponent;
class USevenfoldSphereComponent;
class UTargetSelectionComponent;
class UAIPerceptionStimuliSourceComponent;
class USceneCaptureComponent2D;
class UCameraComponent;
class USpringArmComponent;
class AController;
class APlayerController;
class AThrowableRock;
class AHUD;
class AGameModeBase;

UCLASS()
class MAGICTRIGGER_API APlayerCharacterMagicTrigger : public ACharacter,
	public IAnimationManagerInterface,
	public IOwnerTargetSelectionInterface,
	public IPlayerCharacterInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacterMagicTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**
	 * Variables
	 */

public:

	/**
	 *
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger|Components")
		UMeleeAttackComponent* MeleeAttackComponent;

	/**
	* Для начальной точки трейса к точке установки поднимаемого актора.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger|Components")
		USceneComponent* PointStartTraceToPutDownPoint;

	/**
	*
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger|Components")
		UUpDownLiftingItemComponent* UpDownLiftingItemComponent;

	/**
	* Для трейса препятствия поставить поднимаемый актор.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger|Components")
		UArrowComponent* UpDownLiftingArrow;

	/**
	*
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger|Components")
		UAnimationManagerComponent* AnimationManagerComponent;

	/**
	*
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger|Components")
		UTargetSelectionComponent* TargetSelectionComponent;

	/**
	*
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger|Components")
		USevenfoldSphereComponent* SevenfoldSphereComponent;

	/**
	* Для генерации шума шагов.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger|Components")
		UAIPerceptionStimuliSourceComponent* AIPerceptionStimuliSourceComponent;

	/**
	* Для скриншота сохраненной игры.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger|Components")
		USceneCaptureComponent2D* ScreenShotComponent;

	/**
	* Для трейса атаки.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger|Components")
		UArrowComponent* ArrowRightFoot;

	/**
	* Для трейса атаки.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger|Components")
		UArrowComponent* ArrowLeftFoot;

	/**
	* Для точки аттача поднимаемого актора.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger|Components")
		USceneComponent* PointCarryUp;

	/**
	* Для трейса точки опускания поднятого актора.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger|Components")
		USceneComponent* PointPutDown;

	/**
	* Для разных взаимодействий с разными итемами, которые перед персом.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger|Components")
		UCapsuleComponent* InteractCollision;

	/**
	* Основная камера.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger|Components")
		UCameraComponent* Camera;

	/**
	* Для камеры.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger|Components")
		USpringArmComponent* SpringArm;

	/**
	* Вращать ли перса в сторону цели.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacterMagicTrigger|Settings")
		bool bRotatingToTarget;

	/**
	* Скорость зума камеры.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacterMagicTrigger|Settings")
		float ZoomIntencity;

	/**
	* Максимальная длина штатива камеры, которая соответ. минимальному зуму.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacterMagicTrigger|Settings")
		float SpringArmLengthMax;

	/**
	* Минимальная длина штатива камеры, которая соответ. максимальному зуму.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacterMagicTrigger|Settings")
		float SpringArmLengthMin;

	/**
	 * Умножается на AxisValue из InputAxis для изменения скорости передвижения.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacterMagicTrigger|Settings")
		float AxisValueRunningCoeff;
	/**
	 * Умножается на AxisValue из InputAxis для изменения скорости передвижения.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacterMagicTrigger|Settings")
		float AxisValueShortWalkingCoeff;
	/**
	 * Умножается на AxisValue из InputAxis для изменения скорости передвижения.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacterMagicTrigger|Settings")
		float AxisValueWalkingCoeff;
	/**
	 * Умножается на AxisValue из InputAxis для изменения скорости передвижения.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacterMagicTrigger|Settings")
		float AxisValueStopCoeff;


	/**
	 *
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacterMagicTrigger|Settings")
		FName ArrowLeftFootSocketName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacterMagicTrigger|Settings")
		FName ArrowRightFootSocketName;

	/**
	 *
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerCharacterMagicTrigger|Settings")
		float LifeSpan;

	/**
	 * Умножается на AxisValue из InputAxis для изменения скорости передвижения.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger")
		float AxisValueMovementCoeff;

	/**
	 * Режимы движения
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger")
		EMovementStatus MovementStatus;

	///**
	// * включен ли автобег
	// */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger")


private:
	/**
	 * Для автобега. Запускает метод AutoRunning().
	 */
	FTimerHandle AutoRunningTimer;
	APlayerController* PlayerController;
	AHUD* HUD;
	AGameModeBase* GameMode;

	/**
	 * Methods
	 */

public:

	/**
	 * Player inputs.
	 */

	void MoveForward_InAx(float AxisValue);
	void MoveRight_InAx(float AxisValue);
	void Turn_InAx(float AxisValue);
	void LookUp_InAx(float AxisValue);

	void StartMove_InAct();
	void StopMove_InAct();

	void StartRunning_InAct();
	void StopRunning_InAct();
	void StartShortWalking_InAct();
	void StopShortWalking_InAct();

	void StartJump_InAct();
	void StopJump_InAct();

	void ZoomUp_InAct();
	void ZoomDown_InAct();

	void Attack_InAct();
	void Throw_InAct();
	void ShowGameMenu_InAct();
	void UseSevenfoldSphereAbility_InAct();
	void AutoRunning_InAct();

	void LiftUpLiftingItem_InAct();
	void PutDownLiftingItem_InAct();

	void WatchEnemies_InAct(FKey InputKey);
	void WatchOtherActors_InAct(FKey InputKey);
	void OffWatchingActors_InAct();

	void Interact_InAct();

	/**
	 * Other
	 */

	void AutoRunning();
	void ShowOrHideInteractionText(bool bShow, AActor* InteractionActor);
	void GetDamage(bool bGetDamage, float Damage, AController* EnemyController);
	void RotateToTarget();

	/**
	 * Изменяет значение AxisValue для AddMovementInput() при контроле игроком скорости передвижения.
	 */
	float CalcScaleMovementInput(float AxisValue);

	void SpawnThrowableRock(AThrowableRock* ThrowableRock);
	UTextureRenderTarget2D* CreateScreenShot();

	/**
	 * TargetSelectionComponent
	 */

	void RemoveAndSwitchActors(AActor* RemovingActor);
	void TargetSelectionCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void TargetSelectionCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/**
	 * PlayerState
	 */

	float GetDamage() const;
	float GetMultiplierOfDamage() const;
	float GetDefence();
	float GetLife();

	/**
	 * Attack Tracing
	 */

	void TraceAttackRightFoot();
	void TraceAttackLeftFoot();


public:
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 * InterfaceMethods
		 */
		 /**
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 * AnimationManagerInterface methods.
		 */
		 /**
		  * Setters
		  */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Setters")
		void SetPlayingAnimationPutDown2Hand_IF(bool bPlaying);
	virtual void SetPlayingAnimationPutDown2Hand_IF_Implementation(bool bPlaying) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Setters")
		void SetPlayingAnimationLiftUp2Hand_IF(bool bPlaying);
	virtual void SetPlayingAnimationLiftUp2Hand_IF_Implementation(bool bPlaying) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Setters")
		void SetPlayingAnimationPutDown1Hand_IF(bool bPlaying);
	virtual void SetPlayingAnimationPutDown1Hand_IF_Implementation(bool bPlaying) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Setters")
		void SetPlayingAnimationLiftUp1Hand_IF(bool bPlaying);
	virtual void SetPlayingAnimationLiftUp1Hand_IF_Implementation(bool bPlaying) override;

	/**
	  * Getters
	  */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface|Getters")
		UActorComponent* GetAnimationManagerComponent_IF() const;
	virtual UActorComponent* GetAnimationManagerComponent_IF_Implementation() const override;

	/**
	 * Other
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface")
		void ReportNoise_IF();
	virtual void ReportNoise_IF_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface")
		void DetachLiftingActor_IF();
	virtual void DetachLiftingActor_IF_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface")
		void AttachLiftingActor_IF();
	virtual void AttachLiftingActor_IF_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface")
		void AttachThrowableActor_IF();
	virtual void AttachThrowableActor_IF_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface")
		void SpawnThrowableActor_IF();
	virtual void SpawnThrowableActor_IF_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface")
		void StopTraceAttackLeftFoot_IF();
	virtual void StopTraceAttackLeftFoot_IF_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface")
		void StartTraceAttackLeftFoot_IF();
	virtual void StartTraceAttackLeftFoot_IF_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface")
		void StopTraceAttackRightFoot_IF();
	virtual void StopTraceAttackRightFoot_IF_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "AnimationManagerInterface")
		void StartTraceAttackRightFoot_IF();
	virtual void StartTraceAttackRightFoot_IF_Implementation() override;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 * OwnerTargetSelectionInterface
		 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "OwnerTargetSelectionInterface")
		void OffWatchingActors_IF();
	virtual void OffWatchingActors_IF_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "OwnerTargetSelectionInterface")
		void RemoveAndSwitchActors_IF(AActor* RemovingActor);
	virtual void RemoveAndSwitchActors_IF_Implementation(AActor* RemovingActor) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "OwnerTargetSelectionInterface")
		AActor* GetObservedActor_IF() const;
	virtual AActor* GetObservedActor_IF_Implementation() const override;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	* PlayerCharacterInterface
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerCharacterInterface")
		UTextureRenderTarget2D* CreateScreenShot_IF();
	virtual UTextureRenderTarget2D* CreateScreenShot_IF_Implementation() override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerCharacterInterface")
		void DestroyLiftUpObject_IF();
	virtual void DestroyLiftUpObject_IF_Implementation() override;

	/**
	 * Getters
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerCharacterInterface|Getters")
		FTransform GetSocketTransform_IF(FName& SocketName) const;
	virtual FTransform GetSocketTransform_IF_Implementation(FName& SocketName) const override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerCharacterInterface|Getters")
		UCapsuleComponent* GetInteractCollision_IF() const;
	virtual UCapsuleComponent* GetInteractCollision_IF_Implementation() const override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerCharacterInterface|Getters")
		FVector GetUpDownLiftingArrowForwardVector_IF() const;
	virtual FVector GetUpDownLiftingArrowForwardVector_IF_Implementation() const override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerCharacterInterface|Getters")
		FTransform GetPointPutDownTransform_IF() const;
	virtual FTransform GetPointPutDownTransform_IF_Implementation() const override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerCharacterInterface|Getters")
		FTransform GetPointStartTraceToPutDownPointTransform_IF() const;
	virtual FTransform GetPointStartTraceToPutDownPointTransform_IF_Implementation() const override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerCharacterInterface|Getters")
		USkeletalMeshComponent* GetMesh_IF() const;
	virtual USkeletalMeshComponent* GetMesh_IF_Implementation() const override;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


};
