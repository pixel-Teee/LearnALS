#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CatRoleEnumLibrary.h"
#include "CatRoleStructLibrary.generated.h"

class UCurveVector;
class UCurveFloat;
USTRUCT(BlueprintType)
struct FCatRoleMovementSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Movement Settings")
	float WalkSpeed = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Movement Settings")
	float RunSpeed = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Movement Settings")
	float SprintSpeed = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Movement Settings")
	TObjectPtr<UCurveVector> MovementCurve = nullptr;

	UPROPERTY(EditAnywhere, Category = "Movement Settings")
	TObjectPtr<UCurveFloat> RotationRateCurve = nullptr;

	float GetSpeedForGait(const ECatRoleGait Gait) const
	{
		switch (Gait)
		{
		case ECatRoleGait::Running:
			return RunSpeed;
		case ECatRoleGait::Sprinting:
			return SprintSpeed;
		case ECatRoleGait::Walking:
			return WalkSpeed;
		default:
			return RunSpeed;
		}
	}
};