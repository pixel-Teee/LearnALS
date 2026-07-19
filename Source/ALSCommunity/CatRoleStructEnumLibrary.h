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

USTRUCT(BlueprintType)
struct FCatRoleOverlayState
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Character States")
	ECatRoleOverlayState State = ECatRoleOverlayState::Default;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Character States")
	bool Default_ = true;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Character States")
	bool Masculine_ = false;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Character States")
	bool Feminine_ = false;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Character States")
	bool Injured_ = false;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Character States")
	bool HandsTied_ = false;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Character States")
	bool Rifle_ = false;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Character States")
	bool PistolOneHanded_ = false;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Character States")
	bool PistolTwoHanded_ = false;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Character States")
	bool Bow_ = false;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Character States")
	bool Torch_ = false;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Character States")
	bool Binoculars_ = false;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Character States")
	bool Box_ = false;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Character States")
	bool Barrel_ = false;

public:
	FCatRoleOverlayState()
	{
	}

	FCatRoleOverlayState(const ECatRoleOverlayState InitialState) { *this = InitialState; }

	const bool& Default() const { return Default_; }
	const bool& Masculine() const { return Masculine_; }
	const bool& Feminine() const { return Feminine_; }
	const bool& Injured() const { return Injured_; }
	const bool& HandsTied() const { return HandsTied_; }
	const bool& Rifle() const { return Rifle_; }
	const bool& PistolOneHanded() const { return PistolOneHanded_; }
	const bool& PistolTwoHanded() const { return PistolTwoHanded_; }
	const bool& Bow() const { return Bow_; }
	const bool& Torch() const { return Torch_; }
	const bool& Binoculars() const { return Binoculars_; }
	const bool& Box() const { return Box_; }
	const bool& Barrel() const { return Barrel_; }

	operator ECatRoleOverlayState() const { return State; }

	void operator=(const ECatRoleOverlayState NewAction)
	{
		State = NewAction;
		Default_ = State == ECatRoleOverlayState::Default;
		Masculine_ = State == ECatRoleOverlayState::Masculine;
		Feminine_ = State == ECatRoleOverlayState::Feminine;
		Injured_ = State == ECatRoleOverlayState::Injured;
		HandsTied_ = State == ECatRoleOverlayState::HandsTied;
		Rifle_ = State == ECatRoleOverlayState::Rifle;
		PistolOneHanded_ = State == ECatRoleOverlayState::PistolOneHanded;
		PistolTwoHanded_ = State == ECatRoleOverlayState::PistolTwoHanded;
		Bow_ = State == ECatRoleOverlayState::Bow;
		Torch_ = State == ECatRoleOverlayState::Torch;
		Binoculars_ = State == ECatRoleOverlayState::Binoculars;
		Box_ = State == ECatRoleOverlayState::Box;
		Barrel_ = State == ECatRoleOverlayState::Barrel;
	}
};

USTRUCT(BlueprintType)
struct FCatRoleMovementAction
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Movement System")
	ECatRoleMovementAction Action = ECatRoleMovementAction::None;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Movement System")
	bool None_ = true;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Movement System")
	bool LowMantle_ = false;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Movement System")
	bool HighMantle_ = false;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Movement System")
	bool Rolling_ = false;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Movement System")
	bool GettingUp_ = false;

public:
	FCatRoleMovementAction()
	{
	}

	FCatRoleMovementAction(const ECatRoleMovementAction InitialAction) { *this = InitialAction; }

	const bool& None() const { return None_; }
	const bool& LowMantle() const { return LowMantle_; }
	const bool& HighMantle() const { return HighMantle_; }
	const bool& Rolling() const { return Rolling_; }
	const bool& GettingUp() const { return GettingUp_; }

	operator ECatRoleMovementAction() const { return Action; }

	void operator=(const ECatRoleMovementAction NewAction)
	{
		Action = NewAction;
		None_ = Action == ECatRoleMovementAction::None;
		LowMantle_ = Action == ECatRoleMovementAction::LowMantle;
		HighMantle_ = Action == ECatRoleMovementAction::HighMantle;
		Rolling_ = Action == ECatRoleMovementAction::Rolling;
		GettingUp_ = Action == ECatRoleMovementAction::GettingUp;
	}
};

USTRUCT(BlueprintType)
struct FCatRoleStance
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Character States")
	ECatRoleStance Stance = ECatRoleStance::Standing;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Character States")
	bool Standing_ = true;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "CatRole|Character States")
	bool Crouching_ = false;

public:
	FCatRoleStance()
	{
	}

	FCatRoleStance(const ECatRoleStance InitialStance) { *this = InitialStance; }

	const bool& Standing() const { return Standing_; }
	const bool& Crouching() const { return Crouching_; }

	operator ECatRoleStance() const { return Stance; }

	void operator=(const ECatRoleStance NewStance)
	{
		Stance = NewStance;
		Standing_ = Stance == ECatRoleStance::Standing;
		Crouching_ = Stance == ECatRoleStance::Crouching;
	}
};