// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Для поднимания или опускания поднимаемых предметов (акторов). Подключается к персу.
 */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UpDownLiftingItemComponent.generated.h"

class UCapsuleComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Category = "UpDownLiftingItemComponent")
class MAGICTRIGGER_API UUpDownLiftingItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UUpDownLiftingItemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/**
	 * Variables
	 */
public:

protected:
	/**
	 * Класс поднимаемого актора. Используется для фильтра в методе GetOverlappingActors().
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UpDownLiftingItemComponent")
		TSubclassOf<AActor> LiftUpClass;
	/**
	 * Длина горизонтального трейса для обнаружения препятствия (когда нельзя поставить актор). Зависит от размера актора.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UpDownLiftingItemComponent")
		float DistanceOfTraceObstacle;
	/**
	 * Увеличение луча трейса ниже точки PointPutDown, чтобы трейсить неровности ландшафта. При положительном значении увеличивает длину трейса.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UpDownLiftingItemComponent")
		float DeltaVerticalTraceZ;

	/**
	 * Время движения актора от рук перса до точки установки в методе UKismetSystemLibrary::MoveComponentTo()
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UpDownLiftingItemComponent")
		float DetachOverTime;
	/**
	* Время движения актора от точки положения до сокета на персе в методе UKismetSystemLibrary::MoveComponentTo()
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UpDownLiftingItemComponent")
		float AttachOverTime;
	///**
	// * Тип дебаг-линии трейса.
	// */
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UpDownLiftingItemComponent")
	//	TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType;

	/**
	 * Показывать ли дебаг-линию трейса.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UpDownLiftingItemComponent")
		bool bDrawDebugTrace;

	/**
	 * Канал коллизии трейса.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UpDownLiftingItemComponent")
		TEnumAsByte<ECollisionChannel> TraceCollisionChannel;

	/**
	 * Название сокета, из которого будет выпускаться трейс определения препятствия. Можно использовать 
	 * какой-нибудь сокет в центре скелетона перса. 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UpDownLiftingItemComponent")
		FName StartTraceObstacleSocketName;

private:

	UPROPERTY()
		AActor* Owner;
	USkeletalMeshComponent* OwnersMesh;
	FName AttachSocket;
	UPROPERTY()
		AActor* LiftUpObject;
	FVector InstallationLocation;
	FHitResult DetachLiftingActorTraceOut;
	UCapsuleComponent* InterractCollision;


/**
 * Methods
 */

public:

	/**
	 * Отсоединяет актор от перса, учитывая перпятствия, с плавным перемещением.
	 */
	UFUNCTION(BlueprintCallable, Category = "UpDownLiftingItemComponent")
		void DetachLiftingActor();

	/**
	 * Присоединяет актор к персу, с плавным перемещением.
	 */
	UFUNCTION(BlueprintCallable, Category = "UpDownLiftingItemComponent")
		void AttachLiftingActor();
	/**
	 * Начинает подъем актора, делая трейсы и включая анимацию.
	 */
	UFUNCTION(BlueprintCallable, Category = "UpDownLiftingItemComponent")
		void LiftUp();
	/**
	 * Начинает опускание актора, делая трейсы и включая анимацию.
	 */
	UFUNCTION(BlueprintCallable, Category = "UpDownLiftingItemComponent")
		void PutDown();
	/**
	 * Уничтожает объект поднимаемого актора и обнуляет ссылку на него.
	 */
	UFUNCTION(BlueprintCallable, Category = "UpDownLiftingItemComponent")
		void DestroyLiftingActor();

private:

	/**
	 * Находит на карте актор, который можно поднять, по оверлапу с коллизией. Учитывает наблюдаемые акторы системы наблюдения.
	 */
	AActor* FindLifUpObject();

	/**
	 * Находит с помощью трейса точку, в которую можно поставить актор. Т.е. делает вертикальный трейс.
	 */
	bool TracePutDownPoint();

	/**
	 * Находит препятствие перед персом, которое мешает поставить актор. Т.е. делает горизонтальный трейс.
	 */
	bool TraceObstacle();

	/**
	* Выполнить логику после перемещения актора в DetachLiftingActor() с помощью UKismetSystemLibrary::MoveComponentTo()
	*/
	void DoAfterMoveComponentInDetachLiftingActor();
	/**
	* Выполнить логику после перемещения актора в DetachLiftingActor() с помощью UKismetSystemLibrary::MoveComponentTo()
	*/
	void DoAfterMoveComponentInAttachLiftingActor();




};
