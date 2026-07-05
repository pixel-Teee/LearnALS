// Fill out your copyright notice in the Description page of Project Settings.


#include "CatRoleBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CatRoleMovementComponent.h"

const FName NAME_YawOffset(TEXT("YawOffset"));
const FName NAME_RotationAmount(TEXT("RotationAmount"));
// Sets default values
ACatRoleBaseCharacter::ACatRoleBaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCatRoleMovementComponent>(CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = 0;

}

void ACatRoleBaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	MyCharacterMovementComponent = Cast<UCatRoleMovementComponent>(Super::GetMovementComponent());
}

// Called when the game starts or when spawned
void ACatRoleBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//设置默认的旋转值
	TargetRotation = GetActorRotation();
	LastVelocityRotation = TargetRotation;
	LastMovementInputRotation = TargetRotation;
}

// Called every frame
void ACatRoleBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetEssentialValues(DeltaTime);

	if (MovementState == ECatRoleMovementState::Grounded)
	{
		UpdateCharacterMovement();
		UpdateGroundedRotation(DeltaTime);
	}
}

// Called to bind functionality to input
void ACatRoleBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACatRoleBaseCharacter::ForwardMovementAction_Implementation(float Value)
{
	if (MovementState == ECatRoleMovementState::Grounded)
	{
		const FRotator DirRotator(0.0f, AimingRotation.Yaw, 0.0f);
		AddMovementInput(UKismetMathLibrary::GetForwardVector(DirRotator), Value);
	}
}


void ACatRoleBaseCharacter::CameraUpAction_Implementation(float Value)
{
	AddControllerPitchInput(LookUpDownRate * Value);
}

void ACatRoleBaseCharacter::CameraRightAction_Implementation(float Value)
{
	AddControllerYawInput(LookLeftRightRate * Value);
}

void ACatRoleBaseCharacter::RightMovementAction_Implementation(float Value)
{
	if (MovementState == ECatRoleMovementState::Grounded || MovementState == ECatRoleMovementState::InAir)
	{
		// Default camera relative movement behavior
		const FRotator DirRotator(0.0f, AimingRotation.Yaw, 0.0f);
		AddMovementInput(UKismetMathLibrary::GetRightVector(DirRotator), Value);
	}
}

void ACatRoleBaseCharacter::SprintAction_Implementation(bool bValue)
{
	if (bValue)
	{
		SetDesiredGait(ECatRoleGait::Sprinting);
	}
	else
	{
		SetDesiredGait(ECatRoleGait::Running);
	}
}

void ACatRoleBaseCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode /*= 0*/)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);

	if (GetCharacterMovement()->MovementMode == MOVE_Walking ||
		GetCharacterMovement()->MovementMode == MOVE_NavWalking)
	{
		SetMovementState(ECatRoleMovementState::Grounded);
	}
}


void ACatRoleBaseCharacter::OnMovementStateChanged(ECatRoleMovementState PreviousState)
{
	
}

void ACatRoleBaseCharacter::SetMovementState(const ECatRoleMovementState NewState, bool bForce)
{
	if (bForce || MovementState != NewState)
	{
		PrevMovementState = MovementState;
		MovementState = NewState;
		OnMovementStateChanged(PrevMovementState);
	}
}

void ACatRoleBaseCharacter::UpdateCharacterMovement()
{
	const ECatRoleGait AllowedGait = GetAllowedGait();

	const ECatRoleGait ActualGait = GetActualGait(AllowedGait);

	if (ActualGait != Gait)
	{
		SetGait(ActualGait);
	}


}

void ACatRoleBaseCharacter::UpdateGroundedRotation(float DeltaTime)
{
	if (MovementAction == ECatRoleMovementAction::None)
	{
		const bool bCanUpdateMovingRot = ((bIsMoving && bHasMovementInput) || Speed > 150.f);
		if(bCanUpdateMovingRot)
		{
			const float GroundedRotationRate = CalculateGroundedRotationRate();
			if (RotationMode == ECatRoleRotationMode::VelocityDirection)
			{

			}
			else if (RotationMode == ECatRoleRotationMode::LookingDirection)
			{
				//looking direction rotation
				float YawValue;
				if (Gait == ECatRoleGait::Sprinting)
				{
					YawValue = LastVelocityRotation.Yaw;
				}
				else
				{
					//walking or running
					const float YawOffsetCurveVal = GetAnimCurveValue(NAME_YawOffset);
					UE_LOG(LogTemp, Log, TEXT("walking or running yaw offset value:%f"), YawOffsetCurveVal);
					YawValue = AimingRotation.Yaw + YawOffsetCurveVal;
				}
				//设置角色的旋转
				SmoothCharacterRotation({ 0.0f, YawValue, 0.0f }, 500.f, GroundedRotationRate, DeltaTime);
			}
			else if (RotationMode == ECatRoleRotationMode::Aiming)
			{
				const float ControlYaw = AimingRotation.Yaw;
				//设置角色的旋转
				SmoothCharacterRotation({ 0.0f, ControlYaw, 0.0f }, 1000.0f, 20.0f, DeltaTime);
			}
		}
		else
		{
			//不移动
			if ((ViewMode == ECatRoleViewMode::ThirdPerson && RotationMode == ECatRoleRotationMode::Aiming) ||
				ViewMode == ECatRoleViewMode::FirstPerson)
			{
				//限制旋转
				LimitRotation(-100.0f, 100.0f, 20.0f, DeltaTime);
			}

			//从 turn in place 动画应用 rotation amount
			//旋转程度曲线定义了多少旋转应当被应用于每一帧
			//并且在以每秒30帧进行动画处理的动画上计算

			const float RotAmountCurve = GetAnimCurveValue(NAME_RotationAmount);
			
			if (FMath::Abs(RotAmountCurve) > 0.001f)
			{
				if (GetLocalRole() == ROLE_AutonomousProxy)
				{
					TargetRotation.Yaw = UKismetMathLibrary::NormalizeAxis(
						TargetRotation.Yaw + (RotAmountCurve * (DeltaTime / (1.0f / 30.0f))));
					SetActorRotation(TargetRotation);
				}
				else
				{
					AddActorWorldRotation({ 0, RotAmountCurve * (DeltaTime / (1.0f / 30.0f)), 0 });
				}
				TargetRotation = GetActorRotation();
			}
		}
	}
}

ECatRoleGait ACatRoleBaseCharacter::GetAllowedGait() const
{
	if (Stance == ECatRoleStance::Standing)
	{
		if (RotationMode != ECatRoleRotationMode::Aiming)
		{
			if (DesiredGait == ECatRoleGait::Sprinting)
			{
				return CanSprint() ? ECatRoleGait::Sprinting : ECatRoleGait::Running;
			}
			return DesiredGait;
		}
	}

	if (DesiredGait == ECatRoleGait::Sprinting)
	{
		return ECatRoleGait::Running;
	}

	return DesiredGait;
}

ECatRoleGait ACatRoleBaseCharacter::GetActualGait(ECatRoleGait AllowedGait) const
{
	const float LocWalkSpeed = MyCharacterMovementComponent->CurrentMovementSettings.WalkSpeed;
	const float LocRunSpeed = MyCharacterMovementComponent->CurrentMovementSettings.RunSpeed;

	if (Speed > LocRunSpeed + 10.0f)
	{
		if (AllowedGait == ECatRoleGait::Sprinting)
		{
			return ECatRoleGait::Sprinting;
		}
		return ECatRoleGait::Running;
	}

	if (Speed >= LocWalkSpeed + 10.0f)
	{
		return ECatRoleGait::Running;
	}

	return ECatRoleGait::Walking;
}

bool ACatRoleBaseCharacter::CanSprint() const
{
	if (!bHasMovementInput || RotationMode == ECatRoleRotationMode::Aiming)
	{
		return false;
	}

	const bool bValidInputAmount = MovementInputAmount > 0.9f;

	if (RotationMode == ECatRoleRotationMode::VelocityDirection)
	{
		return bValidInputAmount;
	}

	if (RotationMode == ECatRoleRotationMode::LookingDirection)
	{
		const FRotator AccRot = ReplicatedCurrentAcceleration.ToOrientationRotator();
		FRotator Delta = AccRot - AimingRotation;
		Delta.Normalize();

		return bValidInputAmount && FMath::Abs(Delta.Yaw) < 50.0f;
	}

	return false;
}

void ACatRoleBaseCharacter::SetGait(ECatRoleGait NewGait, bool bForce /*= false*/)
{
	if (bForce || Gait != NewGait)
	{
		const ECatRoleGait Prev = Gait;
		Gait = NewGait;
	}
}

void ACatRoleBaseCharacter::SetDesiredGait(ECatRoleGait NewGait)
{
	DesiredGait = NewGait;
}

FVector ACatRoleBaseCharacter::GetMovementInput() const
{
	return ReplicatedCurrentAcceleration;
}

void ACatRoleBaseCharacter::SetEssentialValues(float DeltaTime)
{
	if (GetLocalRole() != ROLE_SimulatedProxy)
	{
		//加速度和最大加速度
		ReplicatedCurrentAcceleration = GetCharacterMovement()->GetCurrentAcceleration();
		//获取controller的rotation
		ReplicatedControlRotation = GetControlRotation();
		EasedMaxAcceleration = GetCharacterMovement()->GetMaxAcceleration();
	}

	AimingRotation = FMath::RInterpTo(AimingRotation, ReplicatedControlRotation, DeltaTime, 30);

	//由速度判断是否处于移动
	const FVector CurrentVel = GetVelocity();

	//获取加速度
	const FVector NewAcceleration = (CurrentVel - PreviousVelocity) / DeltaTime;
	Acceleration = NewAcceleration.IsNearlyZero() || IsLocallyControlled() ? NewAcceleration : Acceleration / 2;

	Speed = CurrentVel.Size2D();
	bIsMoving = Speed > 1.0f;
	if (bIsMoving)
	{
		LastVelocityRotation = CurrentVel.ToOrientationRotator();
	}

	MovementInputAmount = ReplicatedCurrentAcceleration.Size() / EasedMaxAcceleration;
	bHasMovementInput = MovementInputAmount > 0.0f;
	if (bHasMovementInput)
	{
		//TODO:Implement This
	}

}

float ACatRoleBaseCharacter::CalculateGroundedRotationRate() const
{
	//获取在不同速度下的旋转速率
	return 0;
}

void ACatRoleBaseCharacter::SmoothCharacterRotation(FRotator Target, float TargetInterpSpeed, float ActorInterpSpeed, float DeltaTime)
{
	//插值目标旋转，对于额外的平滑的旋转行为
	TargetRotation =
		FMath::RInterpConstantTo(TargetRotation, Target, DeltaTime, TargetInterpSpeed);
	SetActorRotation(
		FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, ActorInterpSpeed));
}

void ACatRoleBaseCharacter::LimitRotation(float AimYawMin, float AimYawMax, float InterpSpeed, float DeltaTime)
{
	FRotator Delta = AimingRotation - GetActorRotation();
	Delta.Normalize();
	const float RangeVal = Delta.Yaw;

	if (RangeVal < AimYawMin || RangeVal > AimYawMax)
	{
		const float ControlRotYaw = AimingRotation.Yaw;
		const float TargetYaw = ControlRotYaw + (RangeVal > 0.0f ? AimYawMin : AimYawMax);
		SmoothCharacterRotation({ 0.0f, TargetYaw, 0.0f }, 0.0f, InterpSpeed, DeltaTime);
	}
}

float ACatRoleBaseCharacter::GetAnimCurveValue(FName CurveName) const
{
	if (GetMesh()->GetAnimInstance())
	{
		return GetMesh()->GetAnimInstance()->GetCurveValue(CurveName);
	}

	return 0.0f;
}

