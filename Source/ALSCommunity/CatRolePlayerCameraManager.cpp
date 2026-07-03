// Fill out your copyright notice in the Description page of Project Settings.


#include "CatRolePlayerCameraManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "CatRolePlayerCameraBehavior.h"
#include "CatRoleBaseCharacter.h"

const FName NAME_CameraBehavior(TEXT("CameraBehavior"));

ACatRolePlayerCameraManager::ACatRolePlayerCameraManager()
{
	CameraBehavior = CreateDefaultSubobject<USkeletalMeshComponent>(NAME_CameraBehavior);
	CameraBehavior->SetupAttachment(GetRootComponent());
	CameraBehavior->bHiddenInGame = true;
}

void ACatRolePlayerCameraManager::OnPossess(ACatRoleBaseCharacter* NewCharacter)
{
	ControlledCharacter = NewCharacter;

	UCatRolePlayerCameraBehavior* CastedBehv = Cast<UCatRolePlayerCameraBehavior>(CameraBehavior->GetAnimInstance());
	if (CastedBehv)
	{
		NewCharacter->SetCameraBehavior(CastedBehv);
	}
}

void ACatRolePlayerCameraManager::UpdateViewTargetInternal(FTViewTarget& OutVT, float DeltaTime)
{

}
