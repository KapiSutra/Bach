// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeExecutionContext.h"
#include "StateTreePropertyFunctionBase.h"
#include "Scizor/Combo/Components/ScizorComboComponent.h"
#include "ScizorCheckComboWindowMatch.generated.h"

USTRUCT()
struct SCIZOR_API FBachCheckComboWindowMatchInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = Parameter)
    TObjectPtr<UScizorComboComponent> ComboComponent;

    UPROPERTY(EditAnywhere, Category = Parameter,
        meta=(Bitmask, BitmaskEnum="/Script/Scizor.EScizorComboWindowState"))

    int32 MatchState = 0;

    UPROPERTY(EditAnywhere, Category = Output)
    bool bMatched = false;
};


/**
 * 
 */
USTRUCT(DisplayName = "Match Combo Window")
struct SCIZOR_API FScizorCheckComboWindowMatch : public FStateTreePropertyFunctionCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FBachCheckComboWindowMatchInstanceData;

    virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

    virtual void Execute(FStateTreeExecutionContext& Context) const override
    {
        auto& [ComboComponent,MatchState,bMatched] = Context.GetInstanceData(*this);
        if (!ComboComponent)
        {
            return;
        }
        const auto CurrentState = ComboComponent->GetComboInfoSummary().ComboWindowState;
        bMatched = (static_cast<int32>(CurrentState) & MatchState) == static_cast<int>(CurrentState);
    };
};
