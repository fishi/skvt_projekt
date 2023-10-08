// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SkvtBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SKVTPROJEKT_API USkvtBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(WorldContext="WorldContextObject"))
	static void CalculateHangTime(const UObject* WorldContextObject, FVector InFirst, FVector InSecond, float Offset, float JumpDurationPerCentimeter, float& HangTime, FVector& Apex);
	
};
