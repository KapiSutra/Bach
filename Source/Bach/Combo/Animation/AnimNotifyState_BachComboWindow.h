// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifies/AnimNotify_PlayMontageNotify.h"
#include "AnimNotifyState_BachComboWindow.generated.h"

/**
 * 
 */
UCLASS(DisplayName = "Combo Window (Bach)")
class BACH_API UAnimNotifyState_BachComboWindow : public UAnimNotify_PlayMontageNotifyWindow
{
    GENERATED_BODY()

    UAnimNotifyState_BachComboWindow()
    {
        bIsNativeBranchingPoint = true;
        NotifyName = TEXT("Bach ComboWindow");
#if WITH_EDITOR
        bShouldFireInEditor = false;
#endif
    }
};
