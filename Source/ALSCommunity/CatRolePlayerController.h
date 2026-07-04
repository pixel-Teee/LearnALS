// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CatRolePlayerController.generated.h"

class ACatRoleBaseCharacter;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class ALSCOMMUNITY_API ACatRolePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void OnPossess(APawn* NewPawn) override;

	virtual void SetupInputComponent() override;

	virtual void BindActions(UInputMappingContext* Context);
protected:
	void SetupInputs();

	UFUNCTION()
	void ForwardMovementAction(const FInputActionValue& Value);

	UFUNCTION()
	void RightMovementAction(const FInputActionValue& Value);

	UFUNCTION()
	void CameraUpAction(const FInputActionValue& Value);

	UFUNCTION()
	void CameraRightAction(const FInputActionValue& Value);
public:
	/** Main character reference */
	UPROPERTY(BlueprintReadOnly, Category = "CatRole")
	TObjectPtr<ACatRoleBaseCharacter> PossessedCharacter = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CatRole|Input")
	TObjectPtr<UInputMappingContext> DefaultInputMappingContext = nullptr;
};
