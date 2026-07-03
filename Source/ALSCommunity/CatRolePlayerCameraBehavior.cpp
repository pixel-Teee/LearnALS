// Fill out your copyright notice in the Description page of Project Settings.


#include "CatRolePlayerCameraBehavior.h"

void UCatRolePlayerCameraBehavior::SetRotationMode(ECatRoleRotationMode RotationMode)
{
	bVelocityDirection = (RotationMode == ECatRoleRotationMode::VelocityDirection);
	bLookingDirection = (RotationMode == ECatRoleRotationMode::LookingDirection);
	bAiming = (RotationMode == ECatRoleRotationMode::Aiming);
}
