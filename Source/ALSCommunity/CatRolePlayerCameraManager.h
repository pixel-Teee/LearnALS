// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "CatRolePlayerCameraManager.generated.h"

class ACatRoleBaseCharacter;
class USkeletalMeshComponent;
/**
 * 
 */
UCLASS()
class ALSCOMMUNITY_API ACatRolePlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	ACatRolePlayerCameraManager();

	UFUNCTION(BlueprintCallable, Category = "CatRole|Camera")
	void OnPossess(ACatRoleBaseCharacter* NewCharacter);
	
protected:
	virtual void UpdateViewTargetInternal(FTViewTarget& OutVT, float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CatRole|Camera")
	TObjectPtr<ACatRoleBaseCharacter> ControlledCharacter = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CatRole|Camera")
	TObjectPtr<USkeletalMeshComponent> CameraBehavior = nullptr;
};
