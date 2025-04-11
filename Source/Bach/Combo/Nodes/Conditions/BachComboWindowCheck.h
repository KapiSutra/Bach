// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Bach/Combo/Components/BachComboComponent.h"
#include "Blueprint/StateTreeConditionBlueprintBase.h"
#include "BachComboWindowCheck.generated.h"

/**
 * 
 */
UCLASS(DisplayName = "Combo Window Check (Bach)")
class BACH_API UBachComboWindowCheck : public UStateTreeConditionBlueprintBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    TObjectPtr<UBachComboComponent> Component;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(Bitmask, BitmaskEnum="/Script/Bach.EBachComboWindowState"))
    int32 MatchState;

protected:
    virtual bool TestCondition(FStateTreeExecutionContext& Context) const override
    {
        if (!Component)
        {
            return false;
        }

        const auto CurrentState = Component->GetComboInfoSummary().ComboWindowState;
        return (static_cast<int32>(CurrentState) & MatchState) == static_cast<int>(CurrentState);
    };
};
