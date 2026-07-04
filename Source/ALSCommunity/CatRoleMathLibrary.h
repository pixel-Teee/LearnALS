// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CatRoleEnumLibrary.h"
#include "CatRoleMathLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ALSCOMMUNITY_API UCatRoleMathLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	//计算角度是否在[MinAngle + Buffer, MaxAngle + Buffer]或者在[MinAngle - Buffer, MaxAngle - Buffer]里面
	UFUNCTION(BlueprintCallable, Category = "CatRole|Math Utils")
	static bool AngleInRange(float Angle, float MinAngle, float MaxAngle, float Buffer, bool IncreaseBuffer);

	UFUNCTION(BlueprintCallable, Category = "CatRole|Math Utils")
	static ECatRoleMovementDirection CalculateQuadrant(ECatRoleMovementDirection Current, float FRThreshold, float FLThreshold,
		float BRThreshold,
		float BLThreshold, float Buffer, float Angle);
	
};
