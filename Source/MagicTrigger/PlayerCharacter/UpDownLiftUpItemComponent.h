// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Для поднимания или опускания поднимаемых предметов (акторов). Подключается к персу.
 */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UpDownLiftUpItemComponent.generated.h"

class UCapsuleComponent;
class APlayerCharacterMagicTrigger;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Category = "UpDownLiftUpItemComponent")
class MAGICTRIGGER_API UUpDownLiftUpItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UUpDownLiftUpItemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/**
	 * Variables
	 */
public:

	/**
	 * Класс поднимаемого актора. Используется для фильтра в методе GetOverlappingActors().
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UpDownLiftUpItemComponent")
		TSubclassOf<AActor> LiftUpClass;
	/**
	 * Длина горизонтального трейса для обнаружения препятствия (когда нельзя поставить актор). Зависит от размера актора.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UpDownLiftUpItemComponent")
		float DistanceOfTraceObstacle;
	/**
	 * Увеличение луча трейса ниже точки PointPutDown, чтобы трейсить неровности ландшафта. При положительном значении увеличивает длину трейса.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UpDownLiftUpItemComponent")
		float DeltaVerticalTraceZ;

	/**
	 * Время движения актора от рук перса до точки установки в методе UKismetSystemLibrary::MoveComponentTo()
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UpDownLiftUpItemComponent")
		float DetachOverTime;
	/**
	* Время движения актора от точки положения до сокета на персе в методе UKismetSystemLibrary::MoveComponentTo()
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UpDownLiftUpItemComponent")
		float AttachOverTime;

	/**
	 * Показывать ли дебаг-линию трейса.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UpDownLiftUpItemComponent")
		bool bDrawDebugTrace;

	/**
	 * Канал коллизии трейса.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UpDownLiftUpItemComponent")
		TEnumAsByte<ECollisionChannel> TraceCollisionChannel;

	/**
	 * Название сокета, из которого будет выпускаться трейс определения препятствия. Можно использовать 
	 * какой-нибудь сокет в центре скелетона перса. 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UpDownLiftUpItemComponent")
		FName StartTraceObstacleSocketName;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UpDownLiftUpItemComponent")
		AActor* LiftUpItem;

	UPROPERTY()
		AActor* Owner;
private:
	USkeletalMeshComponent* OwnersMesh;
	FName AttachSocket;
	FVector InstallationLocation;
	FHitResult DetachLiftUpItemTraceOut;
	UCapsuleComponent* InterractCollision;
	APlayerCharacterMagicTrigger* PlayerCharacter;


/**
 * Methods
 */

public:

	/**
	 * Отсоединяет актор от перса, учитывая перпятствия, с плавным перемещением.
	 */
	UFUNCTION(BlueprintCallable, Category = "UpDownLiftUpItemComponent")
		void DetachLiftUpItem();

	/**
	 * Присоединяет актор к персу, с плавным перемещением.
	 */
	UFUNCTION(BlueprintCallable, Category = "UpDownLiftUpItemComponent")
		void AttachLiftUpItem();
	/**
	 * Начинает подъем актора, делая трейсы и включая анимацию.
	 */
	UFUNCTION(BlueprintCallable, Category = "UpDownLiftUpItemComponent")
		void LiftUp();
	/**
	 * Подобрать подбираемый предмет (в инвентарь, в абилку)
	 */
	UFUNCTION(BlueprintCallable, Category = "UpDownLiftUpItemComponent")
	void PickUpPickUpItem();

	/**
	 * Начинает опускание актора, делая трейсы и включая анимацию.
	 */
	UFUNCTION(BlueprintCallable, Category = "UpDownLiftUpItemComponent")
		void PutDown();
	/**
	 * Уничтожает объект поднимаемого актора и обнуляет ссылку на него.
	 */
	UFUNCTION(BlueprintCallable, Category = "UpDownLiftUpItemComponent")
		void DestroyLiftUpItem();

private:

	/**
	 * Находит на карте актор, который можно поднять, по оверлапу с коллизией. Учитывает наблюдаемые акторы системы наблюдения.
	 */
	AActor* FindLiftUpItem();

	/**
	 * Находит с помощью трейса точку, в которую можно поставить актор. Т.е. делает вертикальный трейс.
	 */
	bool TracePutDownPoint();

	/**
	 * Находит препятствие перед персом, которое мешает поставить актор. Т.е. делает горизонтальный трейс.
	 */
	bool TraceObstacle();

};
