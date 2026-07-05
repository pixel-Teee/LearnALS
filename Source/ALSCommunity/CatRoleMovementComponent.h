// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CatRoleStructLibrary.h"
#include "CatRoleMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class ALSCOMMUNITY_API UCatRoleMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "CatRole|Movement System")
	FCatRoleMovementSettings CurrentMovementSettings;
	
	
};
