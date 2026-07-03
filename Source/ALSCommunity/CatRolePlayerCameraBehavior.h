// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CatRoleEnumLibrary.h"
#include "CatRolePlayerCameraBehavior.generated.h"

/**
 * 
 */
UCLASS()
class ALSCOMMUNITY_API UCatRolePlayerCameraBehavior : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	void SetRotationMode(ECatRoleRotationMode RotationMode);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Read Only Data|Character Information")
	ECatRoleMovementState MovementState;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Read Only Data|Character Information")
	bool bLookingDirection = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Read Only Data|Character Information")
	bool bVelocityDirection = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Read Only Data|Character Information")
	bool bAiming = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Read Only Data|Character Information")
	ECatRoleGait Gait;
};
