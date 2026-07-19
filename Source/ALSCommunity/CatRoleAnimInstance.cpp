// Fill out your copyright notice in the Description page of Project Settings.


#include "CatRoleAnimInstance.h"
#include "CatRoleBaseCharacter.h"
#include "Math/UnrealMathUtility.h"
#include "CatRoleMathLibrary.h"
#include "Curves/CurveVector.h"
#include "GameFramework/CharacterMovementComponent.h"

static const FName NAME_BasePose_N(TEXT("BasePose_N"));
static const FName NAME_BasePose_CLF(TEXT("BasePose_CLF"));
static const FName NAME_W_Gait(TEXT("W_Gait"));

void UCatRoleAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = Cast<ACatRoleBaseCharacter>(TryGetPawnOwner());
}

void UCatRoleAnimInstance::NativeBeginPlay()
{

}

void UCatRoleAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!Character || DeltaSeconds == 0.0f)
	{
		return;
	}

	//更新运动状态
	MovementState = Character->GetMovementState();
	//步态走姿
	Gait = Character->GetGait();

	//站立还是蹲伏，用于在站立和蹲伏之间进行切换
	Stance = Character->GetStance();

	//移动行为
	MovementAction = Character->GetMovementAction();
	
	//移动输入(从CMC获取的)
	CharacterInformation.MovementInput = Character->GetMovementInput();
	CharacterInformation.Speed = Character->GetSpeed();
	CharacterInformation.bHasMovementInput = Character->HasMovementInput();
	CharacterInformation.bIsMoving = Character->IsMoving();
	CharacterInformation.Speed = Character->GetSpeed();
	CharacterInformation.Velocity = Character->GetCharacterMovement()->Velocity;
	CharacterInformation.CharacterActorRotation = Character->GetActorRotation();
	CharacterInformation.Acceleration = Character->GetAcceleration();

	//controller的旋转，视角的旋转
	CharacterInformation.AimingRotation = Character->GetAimingRotation();

	//角色各种状态，比如搬箱子
	OverlayState = Character->GetOverlayState();
	//更新层混合权重，用于层混合
	UpdateLayerValues();
	if (MovementState.Grounded())
	{
		const bool bPrevShouldMove = Grounded.bShouldMove;
		Grounded.bShouldMove = ShouldMoveCheck();

		if (Grounded.bShouldMove)
		{
			//更新移动动画2D混合空间所需要的参数
			UpdateMovementValues(DeltaSeconds);
			//更新朝向
			UpdateRotationValues();
		}
	}
}


void UCatRoleAnimInstance::UpdateMovementValues(float DeltaSeconds)
{
	const FCatRoleVelocityBlend& TargetBlend = CalculateVelocityBlend();
	VelocityBlend.F = FMath::FInterpTo(VelocityBlend.F, TargetBlend.F, DeltaSeconds, Config.VelocityBlendInterpSpeed);
	VelocityBlend.B = FMath::FInterpTo(VelocityBlend.B, TargetBlend.B, DeltaSeconds, Config.VelocityBlendInterpSpeed);
	VelocityBlend.L = FMath::FInterpTo(VelocityBlend.L, TargetBlend.L, DeltaSeconds, Config.VelocityBlendInterpSpeed);
	VelocityBlend.R = FMath::FInterpTo(VelocityBlend.R, TargetBlend.R, DeltaSeconds, Config.VelocityBlendInterpSpeed);

	RelativeAccelerationAmount = CalculateRelativeAccelerationAmount();
	//计算奔跑的时候倾斜程度
	LeanAmount.LR = FMath::FInterpTo(LeanAmount.LR, RelativeAccelerationAmount.Y, DeltaSeconds,
		Config.GroundedLeanInterpSpeed);
	LeanAmount.FB = FMath::FInterpTo(LeanAmount.FB, RelativeAccelerationAmount.X, DeltaSeconds,
		Config.GroundedLeanInterpSpeed);

	//计算 walk/run 混合
	Grounded.WalkRunBlend = CalculateWalkRunBlend();

	//计算步长混合
	Grounded.StrideBlend = CalculateStrideBlend();
}


void UCatRoleAnimInstance::UpdateRotationValues()
{
	//设置移动方向
	MovementDirection = CalculateMovementDirection();

	FRotator Delta = CharacterInformation.Velocity.ToOrientationRotator() - CharacterInformation.AimingRotation;
	Delta.Normalize();
	//以偏航角为输入，获取一个向量，ACatRoleBaseCharacter::UpdateGroundedRotation使用
	const FVector& FBOffset = YawOffset_FB->GetVectorValue(Delta.Yaw);
	Grounded.FYaw = FBOffset.X;
	Grounded.BYaw = FBOffset.Y;
	const FVector& LROffset = YawOffset_LR->GetVectorValue(Delta.Yaw);
	Grounded.LYaw = LROffset.X;
	Grounded.RYaw = LROffset.Y;
}

float UCatRoleAnimInstance::CalculateWalkRunBlend() const
{
	//用于混合空间中行走和奔跑的混合
	return Gait.Walking() ? 0.0f : 1.0f;
}


float UCatRoleAnimInstance::CalculateStrideBlend() const
{
	//混合空间，两脚之间的间距

	//获取速度
	const float CurveTime = CharacterInformation.Speed / GetOwningComponent()->GetComponentScale().Z;

	//获取当前播放的动画中，所包含的动画曲线的某一个时刻的值
	const float ClampedGait = GetAnimCurveClamped(NAME_W_Gait, -1.0, 0.0f, 1.0f);

	//在走和奔跑的曲线之间进行插值，通过速度获取曲线中[0, 1]的采样值，然后通过Gait去插值，得到步长
	const float LerpedStrideBlend = 
	FMath::Lerp(StrideBlend_N_Walk->GetFloatValue(CurveTime), StrideBlend_N_Run->GetFloatValue(CurveTime),
	ClampedGait);

	return FMath::Lerp(LerpedStrideBlend, StrideBlend_C_Walk->GetFloatValue(CharacterInformation.Speed),
		GetCurveValue(NAME_BasePose_CLF));
}


ECatRoleMovementDirection UCatRoleAnimInstance::CalculateMovementDirection() const
{
	if (Gait.Sprinting())
	{
		return ECatRoleMovementDirection::Forward;
	}
	//获取角色移动方向和角色朝向方向的差值，然后判断移动方向
	FRotator Delta = CharacterInformation.Velocity.ToOrientationRotator() - CharacterInformation.AimingRotation;
	Delta.Normalize();
	//判断角度是否在某个区间里面，然后计算出不同朝向
	return UCatRoleMathLibrary::CalculateQuadrant(MovementDirection, 70.0f, -70.0f, 110.0f, -110.0f, 5.0f, Delta.Yaw);
}

FCatRoleVelocityBlend UCatRoleAnimInstance::CalculateVelocityBlend() const
{
	//将速度向量转换到角色局部空间，返回单位向量
	const FVector LocRelativeVelocityDir =
		CharacterInformation.CharacterActorRotation.UnrotateVector(CharacterInformation.Velocity.GetSafeNormal(0.1f));
	const float Sum = FMath::Abs(LocRelativeVelocityDir.X) + FMath::Abs(LocRelativeVelocityDir.Y) +
		FMath::Abs(LocRelativeVelocityDir.Z);
	//获取权重总和1.0
	const FVector RelativeDir = LocRelativeVelocityDir / Sum;
	//计算权重分量
	FCatRoleVelocityBlend Result;
	Result.F = FMath::Clamp(RelativeDir.X, 0.0f, 1.0f);
	Result.B = FMath::Abs(FMath::Clamp(RelativeDir.X, -1.0f, 0.0f));
	Result.L = FMath::Abs(FMath::Clamp(RelativeDir.Y, -1.0f, 0.0f));
	Result.R = FMath::Clamp(RelativeDir.Y, 0.0f, 1.0f);
	return Result;
}

FVector UCatRoleAnimInstance::CalculateRelativeAccelerationAmount() const
{
	if (FVector::DotProduct(CharacterInformation.Acceleration, CharacterInformation.Velocity) > 0.0f)
	{
		const float MaxAcc = Character->GetCharacterMovement()->GetMaxAcceleration();
		return CharacterInformation.CharacterActorRotation.UnrotateVector(
			CharacterInformation.Acceleration.GetClampedToMaxSize(MaxAcc) / MaxAcc);
	}
	//制动力
	const float MaxBrakingDec = Character->GetCharacterMovement()->GetMaxBrakingDeceleration();
	return
		CharacterInformation.CharacterActorRotation.UnrotateVector(
			CharacterInformation.Acceleration.GetClampedToMaxSize(MaxBrakingDec) / MaxBrakingDec);
}

float UCatRoleAnimInstance::GetAnimCurveClamped(const FName& Name, float Bias, float ClampMin, float ClampMax) const
{
	return FMath::Clamp(GetCurveValue(Name) + Bias, ClampMin, ClampMax);
}

void UCatRoleAnimInstance::UpdateLayerValues()
{
	//基础姿势权重
	//LayerBlendingValues.BasePose_N = GetCurveValue(NAME_BasePose_N);
	//LayerBlendingValues.BasePose_CLF = GetCurveValue(NAME_BasePose_CLF);

	//TODO:fix this
	LayerBlendingValues.BasePose_N = 1.0;
	LayerBlendingValues.BasePose_CLF = 0.0;

	//空中预测
	//TODO:fix this
	InAir.LandPrediction = 1.0;
}

bool UCatRoleAnimInstance::ShouldMoveCheck() const
{
	return (CharacterInformation.bIsMoving && CharacterInformation.bHasMovementInput) ||
		CharacterInformation.Speed > 150.0f;
}
