// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeExecutionContext.h"
#include "StateTreePropertyFunctionBase.h"
#include "Bach/Combo/ComboTypes.h"
#include "Bach/Combo/Components/ScizorComboComponent.h"
#include "ScizorGetComboInfoSummary.generated.h"

class UScizorComboComponent;

USTRUCT()
struct BACH_API FScizorGetComboInfoSummaryInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = Parameter)
    TObjectPtr<UScizorComboComponent> ComboComponent;

    UPROPERTY(EditAnywhere, Category = Output)
    FScizorComboInfoSummary Summary;
};

/**
 * 
 */
USTRUCT(DisplayName = "Combo Info Summary")
struct BACH_API FScizorGetComboInfoSummary : public FStateTreePropertyFunctionCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FScizorGetComboInfoSummaryInstanceData;

    virtual const UStruct* GetInstanceDataType() const override
    {
        return FInstanceDataType::StaticStruct();
    };

    virtual void Execute(FStateTreeExecutionContext& Context) const override
    {
        auto& [ComboComponent, Summary] = Context.GetInstanceData(*this);
        if (!ComboComponent)
        {
            return;
        }
        Summary = ComboComponent->GetComboInfoSummary();
    };
};
