#pragma once

#include "CoreMinimal.h"

#include "CatRoleEnumLibrary.generated.h"

//角色移动模式状态
UENUM(BlueprintType, meta = (ScriptName = "CatRoleMovementState"))
enum class ECatRoleMovementState : uint8
{
	None,
	Grounded,
	InAir,
	Mantling, //爬墙
	Ragdoll
};

//角色步态，用于动画中行走和奔跑
UENUM(BlueprintType, meta = (ScriptName = "CatRole_Gait"))
enum class ECatRoleGait : uint8
{
	Walking, //行走
	Running, //奔跑
	Sprinting //加速
};

//角色移动动作状态
UENUM(BlueprintType, meta = (ScriptName = "CatRole_MovementAction"))
enum class ECatRoleMovementAction : uint8
{
	None,
	LowMantle,
	HighMantle,
	Rolling,
	GettingUp
};

//角色视角模式
UENUM(BlueprintType, meta = (ScriptName = "CatRole_ViewMode"))
enum class ECatRoleViewMode : uint8
{
	ThirdPerson,
	FirstPerson
};

//角色旋转模式
UENUM(BlueprintType, meta = (ScriptName = "CatRole_RotationMode"))
enum class ECatRoleRotationMode : uint8
{
	VelocityDirection,
	LookingDirection,
	Aiming
};

UENUM(BlueprintType, meta = (ScriptName = "CatRole_MovementDirection"))
enum class ECatRoleMovementDirection : uint8
{
	Forward,
	Right,
	Left,
	Backward
};