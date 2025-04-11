// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeExecutionContext.h"
#include "StateTreePropertyFunctionBase.h"
#include "Bach/Combo/BachTypes.h"
#include "Bach/Combo/Components/BachComboComponent.h"
#include "BachGetComboInfoSummary.generated.h"

class UBachComboComponent;

USTRUCT()
struct BACH_API FBachGetComboInfoSummaryInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, Category = Parameter)
    TObjectPtr<UBachComboComponent> ComboComponent;

    UPROPERTY(EditAnywhere, Category = Output)
    FBachComboInfoSummary Summary;
};

/**
 * 
 */
USTRUCT(DisplayName = "Combo Info Summary")
struct BACH_API FBachGetComboInfoSummary : public FStateTreePropertyFunctionCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FBachGetComboInfoSummaryInstanceData;

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
