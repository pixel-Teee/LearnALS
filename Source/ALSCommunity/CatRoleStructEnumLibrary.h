#pragma once

#include "CatRoleEnumLibrary.h"
#include "CatRoleStructEnumLibrary.generated.h"

USTRUCT(BlueprintType)
struct FCatRoleMovementState
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Movement System")
	ECatRoleMovementState State = ECatRoleMovementState::None;

	//是否在地上
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Movement System")
	bool Grounded_ = false;
public:
	FCatRoleMovementState()
	{}

	//从一个枚举值初始化
	FCatRoleMovementState(const ECatRoleMovementState InitialState) { *this = InitialState; }

	const bool& Grounded() const { return Grounded_; }

	operator ECatRoleMovementState() const { return State; }

	void operator=(const ECatRoleMovementState NewState)
	{
		State = NewState;
		Grounded_ = (State == ECatRoleMovementState::Grounded);
	}
};

//步态
USTRUCT(BlueprintType)
struct FCatRoleGait
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Movement System")
	ECatRoleGait Gait = ECatRoleGait::Walking;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Movement System")
	bool Walking_ = true;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Movement System")
	bool Running_ = false;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Movement System")
	bool Sprinting_ = false;

public:
	FCatRoleGait()
	{
	}

	FCatRoleGait(const ECatRoleGait InitialGait) { *this = InitialGait; }

	const bool& Walking() const { return Walking_; }
	const bool& Running() const { return Running_; }
	const bool& Sprinting() const { return Sprinting_; }

	operator ECatRoleGait() const { return Gait; }

	void operator=(const ECatRoleGait NewGait)
	{
		Gait = NewGait;
		Walking_ = Gait == ECatRoleGait::Walking;
		Running_ = Gait == ECatRoleGait::Running;
		Sprinting_ = Gait == ECatRoleGait::Sprinting;
	}
};

USTRUCT(BlueprintType)
struct FCatRoleMovementDirection
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Movement System")
	ECatRoleMovementDirection MovementDirection = ECatRoleMovementDirection::Forward;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Movement System")
	bool Forward_ = true;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Movement System")
	bool Right_ = false;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Movement System")
	bool Left_ = false;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Movement System")
	bool Backward_ = false;

public:
	FCatRoleMovementDirection()
	{
	}

	FCatRoleMovementDirection(const ECatRoleMovementDirection InitialMovementDirection)
	{
		*this = InitialMovementDirection;
	}

	const bool& Forward() const { return Forward_; }
	const bool& Right() const { return Right_; }
	const bool& Left() const { return Left_; }
	const bool& Backward() const { return Backward_; }

	operator ECatRoleMovementDirection() const { return MovementDirection; }

	void operator=(const ECatRoleMovementDirection NewMovementDirection)
	{
		MovementDirection = NewMovementDirection;
		Forward_ = MovementDirection == ECatRoleMovementDirection::Forward;
		Right_ = MovementDirection == ECatRoleMovementDirection::Right;
		Left_ = MovementDirection == ECatRoleMovementDirection::Left;
		Backward_ = MovementDirection == ECatRoleMovementDirection::Backward;
	}
};