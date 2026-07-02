#pragma once

#include "CoreMinimal.h"

#include "CatRoleEnumLibrary.generated.h"

//角色移动模式状态
UENUM(BlueprintType, meta = (ScriptName = "CatRoleMovementState"))
enum class ECatRoleMovementState : uint8
{
	None,
	Grounded
};

//角色步态，用于动画中行走和奔跑
UENUM(BlueprintType, meta = (ScriptName = "CatRole_Gait"))
enum class ECatRoleGait : uint8
{
	Walking, //行走
	Running, //奔跑
	Sprinting //加速
};

USTRUCT(BlueprintType)
struct FCatRoleAnimCharacterInformation
{
	GENERATED_BODY()

	//移动输入
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CatRole|Character Information")
	FVector MovementInput = FVector::ZeroVector;

	//是否处于移动
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CatRole|Character Information")
	bool bIsMoving = false;

	//是否有输入移动
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CatRole|Character Information")
	bool bHasMovementInput = false;

	//速度
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CatRole|Character Information")
	float Speed = 0.0f;
};