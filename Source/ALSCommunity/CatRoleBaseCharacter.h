// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CatRoleStructEnumLibrary.h"
#include "CatRoleBaseCharacter.generated.h"

class UCatRolePlayerCameraBehavior;
UCLASS()
class ALSCOMMUNITY_API ACatRoleBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACatRoleBaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//输入
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ALS|Input")
	void ForwardMovementAction(float Value);

	//摄像机系统
	UFUNCTION(BlueprintCallable, Category = "CatRole|Camera System")
	void SetCameraBehavior(UCatRolePlayerCameraBehavior* CamBeh) { CameraBehavior = CamBeh; }

	//状态变更
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode = 0) override;

	virtual void OnMovementStateChanged(ECatRoleMovementState PreviousState);
	
	void SetMovementState(const ECatRoleMovementState NewState, bool bForce = false);

	UFUNCTION(BlueprintGetter, Category = "CatRole|Character States")
	ECatRoleMovementState GetMovementState() const { return MovementState; }

	UFUNCTION(BlueprintCallable, Category = "CatRole|Character States")
	void SetGait(ECatRoleGait NewGait, bool bForce = false);

	UFUNCTION(BlueprintGetter, Category = "CatRole|Character States")
	ECatRoleGait GetGait() const { return Gait; }

	UFUNCTION(BlueprintCallable, Category = "CatRole|Essential Information")
	FVector GetMovementInput() const;

	UFUNCTION(BlueprintGetter, Category = "CatRole|Essential Information")
	float GetSpeed() const { return Speed; }

	UFUNCTION(BlueprintGetter, Category = "CatRole|Essential Information")
	bool IsMoving() const { return bIsMoving; }

	//每帧获取一些重要信息，从CMC组件
	void SetEssentialValues(float DetalTime);

	UFUNCTION(BlueprintGetter, Category = "CatRole|Movement System")
	bool HasMovementInput() const { return bHasMovementInput; }
protected:
	UPROPERTY(BlueprintReadOnly, Category = "CatRole|State Values")
	ECatRoleMovementState MovementState = ECatRoleMovementState::None;

	UPROPERTY(BlueprintReadOnly, Category = "CatRole|State Values")
	ECatRoleMovementState PrevMovementState = ECatRoleMovementState::None;

	FRotator AimingRotation = FRotator::ZeroRotator;

	//步态，慢走，奔跑，冲刺
	UPROPERTY(BlueprintReadOnly, Category = "CatRole|State Values")
	ECatRoleGait Gait = ECatRoleGait::Walking;

	UPROPERTY(BlueprintReadOnly, Category = "CatRole|Essential Information")
	bool bIsMoving = false;

	UPROPERTY(BlueprintReadOnly, Category = "CatRole|Essential Information")
	bool bHasMovementInput = false;

	UPROPERTY(BlueprintReadOnly, Category = "CatRole|Essential Information")
	float Speed = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "CatRole|Essential Information")
	float MovementInputAmount = 0.0f; //加速度的单位向量

	//复制的重要信息(TODO:加上复制的必要标记)
	UPROPERTY(BlueprintReadOnly, Category = "CatRole|Essential Information")
	FVector ReplicatedCurrentAcceleration = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly, Category = "CatRole|Essential Information")
	FRotator ReplicatedControlRotation = FRotator::ZeroRotator;

	UPROPERTY(BlueprintReadOnly, Category = "CatRole|Essential Information")
	float EasedMaxAcceleration = 0.0f;

	//camera的anim instance，去驱动更新camera manager
	UPROPERTY(BlueprintReadOnly, Category = "CatRole|Camera")
	TObjectPtr<UCatRolePlayerCameraBehavior> CameraBehavior;
};
