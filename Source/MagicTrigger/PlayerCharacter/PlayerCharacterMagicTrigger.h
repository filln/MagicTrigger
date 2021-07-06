// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Персонаж игры.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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
class UUpDownLiftUpItemComponent;
class UAnimationManagerComponent;
class USevenfoldSphereComponent;
class UTargetSelectionComponent;
class UAIPerceptionStimuliSourceComponent;
class USceneCaptureComponent2D;
class UCameraComponent;
class USpringArmComponent;
class APlayerController;
class AHUD;
class AGameModeBase;
class AAbilitySystemManager;

UCLASS()
class MAGICTRIGGER_API APlayerCharacterMagicTrigger : public ACharacter,
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
	* Для начальной точки трейса к точке установки поднимаемого актора.
	*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger|Components")
		USceneComponent* PointStartTraceToPutDownPoint;
	/**
	*
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger|Components")
		UUpDownLiftUpItemComponent* UpDownLiftUpItemComponent;
	/**
	* Для трейса препятствия поставить поднимаемый актор.
	*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger|Components")
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
	* Для генерации шума шагов.
	*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger|Components")
		UAIPerceptionStimuliSourceComponent* AIPerceptionStimuliSourceComponent;
	/**
	* Для скриншота сохраненной игры.
	*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger|Components")
		USceneCaptureComponent2D* ScreenShotComponent;
	/**
	* Для трейса атаки.
	*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger|Components")
		UArrowComponent* ArrowRightFoot;
	/**
	* Для трейса атаки.
	*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger|Components")
		UArrowComponent* ArrowLeftFoot;
	/**
	* Для точки аттача поднимаемого актора.
	*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger|Components")
		USceneComponent* PointCarryUp;
	/**
	* Для трейса точки опускания поднятого актора.
	*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger|Components")
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
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger|Components")
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger|Settings")
		TSubclassOf<AAbilitySystemManager> AbilitySystemManagerClass;
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
	APlayerController* PlayerController;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PlayerCharacterMagicTrigger")
		AAbilitySystemManager* AbilitySystemManager;

private:
	/**
	 * Для автобега. Запускает метод AutoRunning().
	 */
	FTimerHandle AutoRunningTimer;
	AHUD* HUD;
	AGameModeBase* GameMode;
	//Регулирует какое-либо движение: ходьба, бег, прыжок, атаку и пр.
	bool bMoveEnable;

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
	void ShowGameMenu_InAct();
	void AutoRunning_InAct();

	void WatchEnemies_InAct(FKey InputKey);
	void WatchOtherActors_InAct(FKey InputKey);
	void OffWatchingActors_InAct();

	void Interact_InAct();

	void MeleeAbility_InAct();
	void ThrowAbility_InAct();
	void SSphereAbility_InAct();

	/**
	 * Other
	 */

	void AutoRunning();
	void ShowOrHideInteractionText(bool bShow, AActor* InteractionActor);
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser);
	void RotateToTarget();
	UFUNCTION()
		void InteractCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void InteractCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	bool IsFalling();
	void SpawnThrowableItem();
	void ReportNoise();
	FTransform GetPointPutDownTransform() const;
	FTransform GetPointStartTraceToPutDownPointTransform() const;
	FTransform GetSocketTransform(FName& SocketName) const;
	FVector GetUpDownLiftingArrowForwardVector() const;
	APlayerController* GetPlayerController() const;

	/**
	 * AnimationManagerComponent
	 */
	void SetPlayingAnimationLiftUp2Hands(bool InbPlaying);
	void SetPlayingAnimationLiftUp1Hand(bool InbPlaying);
	void SetPlayingAnimationPutDown2Hands(bool InbPlaying);
	void SetCanInteract(bool InbCanInteract);

	FVector GetForwardVectorArrowLeftFoot();
	FVector GetForwardVectorArrowRightFoot();
	FVector GetArrowLeftFootSocketLocation();
	FVector GetArrowRightFootSocketLocation();

	/**
	 * UpDownLiftUpItemComponent
	 */
	void LiftUpLiftUpItem();
	void DetachLiftUpItem();
	void AttachLiftUpItem();
	void PickUpPickUpItem();

	/**
	 * AbilitySystemManager
	 */
	void SpawnAbilitySystemManager();
	void StartTraceAttackLeftFoot();
	void StopTraceAttackLeftFoot();
	void StartTraceAttackRightFoot();
	void StopTraceAttackRightFoot();
	void PickUpThrowableItem();
	FVector GetVelocity() const;
	void ThrowThrowableItem();
	void SwitchOnSSphereAbility();
	void SpawnSSphere();
	UFUNCTION(BlueprintCallable, Category = "PlayerCharacterMagicTrigger")
		USevenfoldSphereComponent* GetSevenfoldSphereComponent() const;

	/**
	 * Изменяет значение AxisValue для AddMovementInput() при контроле игроком скорости передвижения.
	 */
	float CalcScaleMovementInput(float AxisValue);
	void SetEnableMovement(bool bInEnable);

	UTextureRenderTarget2D* CreateScreenShot();

	/**
	 * TargetSelectionComponent
	 */

	void RemoveAndSwitchActors(AActor* RemovingActor);
	UFUNCTION()
		void TargetSelectionCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void TargetSelectionCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	AActor* GetObservedActor() const;
	void OffWatchingActors();
	/**
	 * PlayerState
	 */

	float GetDamage() const;
	float GetMultiplierOfDamage() const;
	float GetAllDamage() const;
	float GetDefence();
	float GetLife();


public:
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 * InterfaceMethods
		 */
		 /**

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 * OwnerTargetSelectionInterface
		 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "OwnerTargetSelectionInterface")
		void RemoveAndSwitchActors_IF(AActor* RemovingActor);
	virtual void RemoveAndSwitchActors_IF_Implementation(AActor* RemovingActor) override;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	* PlayerCharacterInterface
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PlayerCharacterInterface")
		UTextureRenderTarget2D* CreateScreenShot_IF();
	virtual UTextureRenderTarget2D* CreateScreenShot_IF_Implementation() override;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


};
