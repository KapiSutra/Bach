// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StateTreePropertyFunctionBase.h"
#include "Bach/Combo/BachTypes.h"
#include "BachGetComboInfoSummaryPropertyFunction.generated.h"

class UBachComboComponent;

USTRUCT()
struct BACH_API FBachGetComboInfoSummaryPropertyFunctionInstanceData
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
USTRUCT(DisplayName = "ComboInfoSummary")
struct BACH_API FBachGetComboInfoSummaryPropertyFunction : public FStateTreePropertyFunctionCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FBachGetComboInfoSummaryPropertyFunctionInstanceData;

    virtual const UStruct* GetInstanceDataType() const override
    {
        return FInstanceDataType::StaticStruct();
    };

    virtual void Execute(FStateTreeExecutionContext& Context) const override;
};
