#pragma once

#include "CoreMinimal.h"
#include "CatRoleEnumLibrary.h"
#include "CatRoleAnimationStructLibrary.generated.h"

//用于anim instance的结构体
USTRUCT(BlueprintType)
struct FCatRoleAnimGraphGrounded
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CatRole|Anim Graph - Grounded")
	bool bShouldMove = false;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CatRole|Anim Graph - Grounded")
	float WalkRunBlend = 0.0f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CatRole|Anim Graph - Grounded")
	float StrideBlend = 0.0f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CatRole|Anim Graph - Grounded")
	float FYaw = 0.0f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CatRole|Anim Graph - Grounded")
	float BYaw = 0.0f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CatRole|Anim Graph - Grounded")
	float LYaw = 0.0f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CatRole|Anim Graph - Grounded")
	float RYaw = 0.0f;
};

//速度混合，用于六向运动
USTRUCT(BlueprintType)
struct FCatRoleVelocityBlend
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CatRole|Anim Graph - Grounded")
	float F = 0.0f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CatRole|Anim Graph - Grounded")
	float B = 0.0f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CatRole|Anim Graph - Grounded")
	float L = 0.0f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CatRole|Anim Graph - Grounded")
	float R = 0.0f;
};

USTRUCT(BlueprintType)
struct FCatRoleAnimConfiguration
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CatRole|Main Configuration")
	float VelocityBlendInterpSpeed = 12.0f;
};


USTRUCT(BlueprintType)
struct FCatRoleAnimCharacterInformation
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CatRole|Character Information")
	FRotator CharacterActorRotation = FRotator::ZeroRotator;

	//controller的旋转
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CatRole|Character Information")
	FRotator AimingRotation = FRotator::ZeroRotator;

	//角色速度方向
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CatRole|Character Information")
	FVector Velocity = FVector::ZeroVector;

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

	//加速度
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CatRole|Character Information")
	FVector Acceleration = FVector::ZeroVector;
};

USTRUCT(BlueprintType)
struct FCatRoleAnimGraphLayerBlending
{
	GENERATED_BODY()

	//混合站立和蹲伏的权重
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CatRole|Anim Graph - Layer Blending")
	float BasePose_N = 1.0f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CatRole|Anim Graph - Layer Blending")
	float BasePose_CLF = 0.0f;
};

USTRUCT(BlueprintType)
struct FCatRoleAnimGraphInAir
{
	GENERATED_BODY()

	//混合基础姿势中在空中的权重
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CatRole|Anim Graph - In Air")
	float LandPrediction = 1.0f;
};
