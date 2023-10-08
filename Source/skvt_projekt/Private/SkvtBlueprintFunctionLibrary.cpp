// Fill out your copyright notice in the Description page of Project Settings.


#include "SkvtBlueprintFunctionLibrary.h"

#include "Kismet/KismetMathLibrary.h"

void USkvtBlueprintFunctionLibrary::CalculateHangTime(const UObject* WorldContextObject, FVector InFirst, FVector InSecond, float Offset, float JumpDurationPerCentimeter, float& HangTime, FVector& Apex)
{
	TArray<FVector> Points{
		InFirst,
		InFirst + Offset * FVector::UpVector,
		InSecond + Offset * FVector::UpVector,
		InSecond
	};

	
	TArray<FVector> SegmentPoints;
	FVector::EvaluateBezier(Points.GetData(), 8, SegmentPoints);

	for (int Index = 1; Index < SegmentPoints.Num(); Index++)
	{
		FVector Start = SegmentPoints[Index - 1];
		FVector End = SegmentPoints[Index];
		DrawDebugLine(GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull), Start, End, FColor::Emerald, false, 1.0f);
	}
	double Highest = DBL_MIN;
	for (const FVector Point : Points)
	{
		DrawDebugPoint(GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull), Point, 5.0f, FColor::Emerald, false, 1.0f);
		if (Point.Z > Highest)
		{
			Highest = Point.Z;
			Apex = Point;
		}
	}

	HangTime = (FMath::Abs(InFirst.Z - Highest) + FMath::Abs(InSecond.Z - Highest)) * JumpDurationPerCentimeter;
}
