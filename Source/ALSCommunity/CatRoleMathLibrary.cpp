// Fill out your copyright notice in the Description page of Project Settings.


#include "CatRoleMathLibrary.h"


bool UCatRoleMathLibrary::AngleInRange(float Angle, float MinAngle, float MaxAngle, float Buffer, bool IncreaseBuffer)
{
	if (IncreaseBuffer)
	{
		return Angle >= MinAngle - Buffer && Angle <= MaxAngle + Buffer;
	}
	return Angle >= MinAngle + Buffer && Angle <= MaxAngle - Buffer;
}

ECatRoleMovementDirection UCatRoleMathLibrary::CalculateQuadrant(ECatRoleMovementDirection Current, float FRThreshold, float FLThreshold, float BRThreshold, float BLThreshold, float Buffer, float Angle)
{
	//[FLThreshold, FRThreshold]
	if (AngleInRange(Angle, FLThreshold, FRThreshold, Buffer,
		Current != ECatRoleMovementDirection::Forward && Current != ECatRoleMovementDirection::Backward))
	{
		return ECatRoleMovementDirection::Forward;
	}

	if (AngleInRange(Angle, FRThreshold, BRThreshold, Buffer,
		Current != ECatRoleMovementDirection::Right && Current != ECatRoleMovementDirection::Left))
	{
		return ECatRoleMovementDirection::Right;
	}

	if (AngleInRange(Angle, BLThreshold, FLThreshold, Buffer,
		Current != ECatRoleMovementDirection::Right && Current != ECatRoleMovementDirection::Left))
	{
		return ECatRoleMovementDirection::Left;
	}

	return ECatRoleMovementDirection::Backward;
}
