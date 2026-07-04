// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CatRoleStructEnumLibrary.h"
#include "CatRoleAnimationStructLibrary.h"
#include "CatRoleAnimInstance.generated.h"

class ACatRoleBaseCharacter;
class UCurveVector;
/**
 * 
 */
UCLASS()
class ALSCOMMUNITY_API UCatRoleAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


private:
	//更新移动动画所需要的参数
	void UpdateMovementValues(float DeltaSeconds);

	//更新朝向
	void UpdateRotationValues();

	//计算行走跑步混合
	float CalculateWalkRunBlend() const;

	//计算步长混合
	float CalculateStrideBlend() const;

	//计算移动朝向
	ECatRoleMovementDirection CalculateMovementDirection() const;

	//工具
	float GetAnimCurveClamped(const FName& Name, float Bias, float ClampMin, float ClampMax) const;
public:
	//开启移动动画，如果IsMoving并且HasMovementInput，或者速度如果大于150
	UFUNCTION(BlueprintCallable, Category = "CatRole|Grounded")
	bool ShouldMoveCheck() const;
	
	UPROPERTY(BlueprintReadOnly, Category = "Read Only Data|Character Information")
	TObjectPtr<ACatRoleBaseCharacter> Character = nullptr;

	//角色信息
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Read Only Data|Character Information", Meta = (
		ShowOnlyInnerProperties))
	FCatRoleAnimCharacterInformation CharacterInformation;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Read Only Data|Character Information")
	FCatRoleMovementState MovementState = ECatRoleMovementState::None;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Read Only Data|Character Information")
	FCatRoleGait Gait = ECatRoleGait::Walking;

	//anim ground处于地上的时候，所需要的参数
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Read Only Data|Anim Graph - Grounded", Meta = (
		ShowOnlyInnerProperties))
	FCatRoleAnimGraphGrounded Grounded;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Read Only Data|Anim Graph - Grounded")
	FCatRoleMovementDirection MovementDirection = ECatRoleMovementDirection::Forward;

	//混合曲线
	//用于步态姿势的混合，行走和奔跑的步长距离
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration|Blend Curves")
	TObjectPtr<UCurveFloat> StrideBlend_N_Walk = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration|Blend Curves")
	TObjectPtr<UCurveFloat> StrideBlend_N_Run = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration|Blend Curves")
	TObjectPtr<UCurveFloat> StrideBlend_C_Walk = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration|Blend Curves")
	TObjectPtr<UCurveVector> YawOffset_FB = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Configuration|Blend Curves")
	TObjectPtr<UCurveVector> YawOffset_LR = nullptr;
};
