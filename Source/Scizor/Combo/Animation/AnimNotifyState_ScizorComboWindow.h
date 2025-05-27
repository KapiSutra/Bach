// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifies/AnimNotify_PlayMontageNotify.h"
#include "AnimNotifyState_ScizorComboWindow.generated.h"

/**
 * 
 */
UCLASS(DisplayName = "Combo Window (Scizor)")
class SCIZOR_API UAnimNotifyState_ScizorComboWindow : public UAnimNotify_PlayMontageNotifyWindow
{
	GENERATED_BODY()

	UAnimNotifyState_ScizorComboWindow()
	{
		bIsNativeBranchingPoint = true;
		NotifyName = TEXT("Combo Window (Scizor)");
#if WITH_EDITOR
		bShouldFireInEditor = false;
#endif
	}
};
