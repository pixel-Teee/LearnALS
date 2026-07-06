// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CatRoleStructEnumLibrary.h"
#include "CatRoleStructLibrary.h"
#include "CatRoleBaseCharacter.generated.h"

class UCatRolePlayerCameraBehavior;
class UCatRoleMovementComponent;
UCLASS()
class ALSCOMMUNITY_API ACatRoleBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ACatRoleBaseCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void PostInitializeComponents() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//输入
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CatRole|Input")
	void ForwardMovementAction(float Value);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CatRole|Input")
	void CameraUpAction(float Value);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "CatRole|Input")
	void CameraRightAction(float Value);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ALS|Input")
	void RightMovementAction(float Value);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ALS|Input")
	void SprintAction(bool bValue);

	//摄像机系统
	UFUNCTION(BlueprintCallable, Category = "CatRole|Camera System")
	void SetCameraBehavior(UCatRolePlayerCameraBehavior* CamBeh) { CameraBehavior = CamBeh; }

	//状态变更
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode = 0) override;

	virtual void OnMovementStateChanged(ECatRoleMovementState PreviousState);
	
	void SetMovementState(const ECatRoleMovementState NewState, bool bForce = false);

	void UpdateCharacterMovement();

	//更新角色转向（移动摄像机的时候，让角色比如也朝向摄像机看向的位置）
	void UpdateGroundedRotation(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "CatRole|Movement System")
	ECatRoleGait GetAllowedGait() const;

	UFUNCTION(BlueprintCallable, Category = "CatRole|Movement System")
	ECatRoleGait GetActualGait(ECatRoleGait AllowedGait) const;

	UFUNCTION(BlueprintCallable, Category = "CatRole|Movement System")
	bool CanSprint() const;

	UFUNCTION(BlueprintGetter, Category = "CatRole|Character States")
	ECatRoleMovementState GetMovementState() const { return MovementState; }

	UFUNCTION(BlueprintCallable, Category = "CatRole|Character States")
	void SetGait(ECatRoleGait NewGait, bool bForce = false);

	UFUNCTION(BlueprintGetter, Category = "CatRole|Character States")
	ECatRoleGait GetGait() const { return Gait; }

	UFUNCTION(BlueprintCallable, Category = "CatRole|Character States")
	void SetDesiredGait(ECatRoleGait NewGait);

	UFUNCTION(BlueprintCallable, Category = "CatRole|Essential Information")
	FVector GetMovementInput() const;

	UFUNCTION(BlueprintGetter, Category = "CatRole|Essential Information")
	float GetSpeed() const { return Speed; }

	UFUNCTION(BlueprintGetter, Category = "CatRole|Essential Information")
	FVector GetAcceleration() const { return Acceleration; }

	UFUNCTION(BlueprintCallable, Category = "CatRole|Essential Information")
	FRotator GetAimingRotation() const { return AimingRotation; }

	UFUNCTION(BlueprintGetter, Category = "CatRole|Essential Information")
	bool IsMoving() const { return bIsMoving; }

	UFUNCTION(BlueprintGetter, Category = "CatRole|Essential Information")
	float GetAimYawRate() const { return AimYawRate; }

	//每帧获取一些重要信息，从CMC组件
	void SetEssentialValues(float DetalTime);

	UFUNCTION(BlueprintGetter, Category = "CatRole|Movement System")
	bool HasMovementInput() const { return bHasMovementInput; }

	UFUNCTION(BlueprintCallable, Category = "CatRole|Movement System")
	FCatRoleMovementSettings GetTargetMovementSettings() const;

	//工具
	float CalculateGroundedRotationRate() const;


	void SmoothCharacterRotation(FRotator Target, float TargetInterpSpeed, float ActorInterpSpeed, float DeltaTime);

	void LimitRotation(float AimYawMin, float AimYawMax, float InterpSpeed, float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = "CatRole|Utility")
	float GetAnimCurveValue(FName CurveName) const;

	void SetMovementModel();
protected:
	//输入
	UPROPERTY(EditDefaultsOnly, Category = "CatRole|Input", BlueprintReadOnly)
	float LookUpDownRate = 1.25f;

	UPROPERTY(EditDefaultsOnly, Category = "CatRole|Input", BlueprintReadOnly)
	float LookLeftRightRate = 1.25f;

	//状态值
	UPROPERTY(BlueprintReadOnly, Category = "CatRole|State Values")
	ECatRoleMovementState MovementState = ECatRoleMovementState::None;

	UPROPERTY(BlueprintReadOnly, Category = "CatRole|State Values")
	ECatRoleMovementState PrevMovementState = ECatRoleMovementState::None;

	UPROPERTY(BlueprintReadOnly, Category = "CatRole|State Values")
	ECatRoleMovementAction MovementAction = ECatRoleMovementAction::None;

	UPROPERTY(BlueprintReadOnly, Category = "CatRole|State Values")
	ECatRoleRotationMode RotationMode = ECatRoleRotationMode::LookingDirection;

	//第三人称还是第一人称
	UPROPERTY(BlueprintReadOnly, Category = "CatRole|State Values")
	ECatRoleViewMode ViewMode = ECatRoleViewMode::ThirdPerson;

	//这个aiming rotation是controller的rotation
	FRotator AimingRotation = FRotator::ZeroRotator;

	//步态，慢走，奔跑，冲刺
	UPROPERTY(BlueprintReadOnly, Category = "CatRole|State Values")
	ECatRoleGait Gait = ECatRoleGait::Walking;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CatRole|State Values")
	ECatRoleStance Stance = ECatRoleStance::Standing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CatRole|Input")
	ECatRoleGait DesiredGait = ECatRoleGait::Running;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CatRole|Input")
	ECatRoleStance DesiredStance = ECatRoleStance::Standing;

	UPROPERTY(BlueprintReadOnly, Category = "CatRole|Rotation System")
	FRotator TargetRotation = FRotator::ZeroRotator;

	UPROPERTY(BlueprintReadOnly, Category = "CatRole|Essential Information")
	FRotator LastVelocityRotation;

	UPROPERTY(BlueprintReadOnly, Category = "CatRole|Essential Information")
	FRotator LastMovementInputRotation;

	UPROPERTY(BlueprintReadOnly, Category = "CatRole|Essential Information")
	bool bIsMoving = false;

	UPROPERTY(BlueprintReadOnly, Category = "CatRole|Essential Information")
	bool bHasMovementInput = false;

	UPROPERTY(BlueprintReadOnly, Category = "CatRole|Essential Information")
	float Speed = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "CatRole|Essential Information")
	float MovementInputAmount = 0.0f; //加速度的单位向量

	UPROPERTY(BlueprintReadOnly, Category = "CatRole|Essential Information")
	float AimYawRate = 0.0f;

	//复制的重要信息(TODO:加上复制的必要标记)
	UPROPERTY(BlueprintReadOnly, Category = "CatRole|Essential Information")
	FVector ReplicatedCurrentAcceleration = FVector::ZeroVector;

	UPROPERTY(BlueprintReadOnly, Category = "CatRole|Essential Information")
	FRotator ReplicatedControlRotation = FRotator::ZeroRotator;

	UPROPERTY(BlueprintReadOnly, Category = "CatRole|Essential Information")
	float EasedMaxAcceleration = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "CatRole|Essential Information")
	FVector Acceleration = FVector::ZeroVector;

	//camera的anim instance，去驱动更新camera manager
	UPROPERTY(BlueprintReadOnly, Category = "CatRole|Camera")
	TObjectPtr<UCatRolePlayerCameraBehavior> CameraBehavior;

	FVector PreviousVelocity = FVector::ZeroVector;

	float PreviousAimYaw = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CatRole|Movement System")
	FDataTableRowHandle MovementModel;

	UPROPERTY(BlueprintReadOnly, Category = "CatRole|Movement System")
	FCatRoleMovementStateSettings MovementData;

	//custom movement component
	UPROPERTY()
	TObjectPtr<UCatRoleMovementComponent> MyCharacterMovementComponent;
};
