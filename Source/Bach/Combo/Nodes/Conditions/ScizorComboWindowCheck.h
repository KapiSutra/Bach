// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeConditionBase.h"
#include "StateTreeExecutionContext.h"
#include "Bach/Combo/Components/ScizorComboComponent.h"
#include "ScizorComboWindowCheck.generated.h"

USTRUCT()
struct FBachComboWindowCheckInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    TObjectPtr<UScizorComboComponent> Component;

    UPROPERTY(EditAnywhere, meta=(Bitmask, BitmaskEnum="/Script/Bach.EBachComboWindowState"))
    int32 MatchState = 0;
};


/**
 * 
 */
USTRUCT(DisplayName = "Combo Window Check (Scizor)")
struct BACH_API FScizorComboWindowCheck : public FStateTreeConditionCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FBachComboWindowCheckInstanceData;
    virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); };

protected:
    virtual bool TestCondition(FStateTreeExecutionContext& Context) const override
    {
        const auto& [Component,MatchState] = Context.GetInstanceData(*this);

        if (!Component)
        {
            return false;
        }

        const auto CurrentState = Component->GetComboInfoSummary().ComboWindowState;
        return (static_cast<int32>(CurrentState) & MatchState) == static_cast<int>(CurrentState);
    };
};
