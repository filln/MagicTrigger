// Copyright 2021 Anatoli Kucharau https://vk.com/ulvprog. All Rights Reserved. 
/**
 * Для передачи данных результата трейса из функции.
 */

#pragma once

#include "Engine/EngineTypes.h" //FHitResult
#include "TraceOutputStruct.generated.h"

USTRUCT(BlueprintType)
struct FTraceOutputStruct
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TraceOutputStruct")
        bool ReturnValue;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TraceOutputStruct")
        FHitResult OutHit;
};