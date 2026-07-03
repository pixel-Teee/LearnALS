// Fill out your copyright notice in the Description page of Project Settings.


#include "CatRoleBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values
ACatRoleBaseCharacter::ACatRoleBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACatRoleBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACatRoleBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetEssentialValues(DeltaTime);
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

void ACatRoleBaseCharacter::SetGait(ECatRoleGait NewGait, bool bForce /*= false*/)
{
	if (bForce || Gait != NewGait)
	{
		const ECatRoleGait Prev = Gait;
		Gait = NewGait;
	}
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
	Speed = CurrentVel.Size2D();
	bIsMoving = Speed > 1.0f;

	MovementInputAmount = ReplicatedCurrentAcceleration.Size() / EasedMaxAcceleration;
	bHasMovementInput = MovementInputAmount > 0.0f;
	if (bHasMovementInput)
	{
		//TODO:Implement This
	}

}

