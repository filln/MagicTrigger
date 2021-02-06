// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Для передачи данных между FireBallComponent->MoveFireBallToTarget() и FireBall->MoveToTarget()
 * Сделана для удобства и компактности.
 */

#pragma once


#include "FireBallMoveToTargetInputsStruct.generated.h"

class AActor;
class AController;
class UDamageType;

USTRUCT(BlueprintType)
struct FFireBallMoveToTargetInputsStruct
{
    GENERATED_BODY()

    //Владелец компонента FireBallComponent.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBallMoveToTargetInputsStruct")
        AActor* Owner;
    //Контроллер владельца компонента FireBallComponent.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBallMoveToTargetInputsStruct")
        AController* OwnersController;
    //Цель абилки (враг).
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBallMoveToTargetInputsStruct")
        AActor* Target;
    //Используется в ApplyDamage()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBallMoveToTargetInputsStruct")
        UDamageType* DamageTypeClass;
    //Повреждение, которое наносит абилка FireBall.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBallMoveToTargetInputsStruct")
        float Damage;
    //Скорость движения FireBall к Target.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireBallMoveToTargetInputsStruct")
        float SpeedOfMoveToTarget;

};