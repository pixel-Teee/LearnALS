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
	GENERATED_UCLASS_BODY()
	
public:
	virtual void OnMovementUpdated(float DeltaTime, const FVector& OldLocation, const FVector& OldVelocity) override;

	UPROPERTY(BlueprintReadOnly, Category = "CatRole|Movement System")
	FCatRoleMovementSettings CurrentMovementSettings;

	UPROPERTY()
	ECatRoleGait AllowedGait = ECatRoleGait::Walking;

	// Movement Settings Variables
	UPROPERTY()
	uint8 bRequestMovementSettingsChange = 1;
	
	// Set Max Walking Speed (Called from the owning client)
	UFUNCTION(BlueprintCallable, Category = "Movement Settings")
	void SetAllowedGait(ECatRoleGait NewAllowedGait);

	// Set Movement Curve (Called in every instance)
	float GetMappedSpeed() const;

	UFUNCTION(BlueprintCallable, Category = "Movement Settings")
	void SetMovementSettings(FCatRoleMovementSettings NewMovementSettings);
};
