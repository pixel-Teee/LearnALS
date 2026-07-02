#pragma once

#include "CoreMinimal.h"
#include "CatRoleEnumLibrary.h"
#include "CatRoleAnimationStructLibrary.generated.h"

//用于anim instance的结构体
USTRUCT(BlueprintType)
struct FCatRoleAnimGraphGrounded
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CatRole|Anim Graph - Grounded")
	bool bShouldMove = false;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CatRole|Anim Graph - Grounded")
	float WalkRunBlend = 0.0f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "CatRole|Anim Graph - Grounded")
	float StrideBlend = 0.0f;
};
