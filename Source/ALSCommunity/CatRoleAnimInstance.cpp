// Fill out your copyright notice in the Description page of Project Settings.


#include "CatRoleAnimInstance.h"
#include "CatRoleBaseCharacter.h"
#include "Math/UnrealMathUtility.h"

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
	//移动输入(从CMC获取的)
	CharacterInformation.MovementInput = Character->GetMovementInput();
	CharacterInformation.Speed = Character->GetSpeed();
	CharacterInformation.bHasMovementInput = Character->HasMovementInput();
	CharacterInformation.bIsMoving = Character->IsMoving();
	if (MovementState.Grounded())
	{
		const bool bPrevShouldMove = Grounded.bShouldMove;
		Grounded.bShouldMove = ShouldMoveCheck();

		if (Grounded.bShouldMove)
		{
			//更新移动动画2D混合空间所需要的参数
			UpdateMovementValues(DeltaSeconds);
		}
	}
}


void UCatRoleAnimInstance::UpdateMovementValues(float DeltaSeconds)
{
	//计算 walk/run 混合
	Grounded.WalkRunBlend = CalculateWalkRunBlend();

	//计算步长混合
	Grounded.StrideBlend = CalculateStrideBlend();
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

	//在走和奔跑的曲线之间进行插值
	const float LerpedStrideBlend = 
	FMath::Lerp(StrideBlend_N_Walk->GetFloatValue(CurveTime), StrideBlend_N_Run->GetFloatValue(CurveTime),
	ClampedGait);

	return FMath::Lerp(LerpedStrideBlend, StrideBlend_C_Walk->GetFloatValue(CharacterInformation.Speed),
		GetCurveValue(NAME_BasePose_CLF));
}


float UCatRoleAnimInstance::GetAnimCurveClamped(const FName& Name, float Bias, float ClampMin, float ClampMax) const
{
	return FMath::Clamp(GetCurveValue(Name) + Bias, ClampMin, ClampMax);
}

bool UCatRoleAnimInstance::ShouldMoveCheck() const
{
	return (CharacterInformation.bIsMoving && CharacterInformation.bHasMovementInput) ||
		CharacterInformation.Speed > 150.0f;
}
