// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeConditionBase.h"
#include "StateTreeExecutionContext.h"
#include "Scizor/Combo/ComboTypes.h"
#include "ScizorStateTreeCondition_ComboInputCheck.generated.h"

class UInputAction;

USTRUCT()
struct FScizorStateTreeCondition_ComboInputCheck_InstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    TObjectPtr<UInputAction> MatchInput;

    UPROPERTY(EditInstanceOnly)
    bool Invert = false;
};

/**
 * 
 */
USTRUCT(DisplayName = "Combo Input Check (Scizor)")
struct SCIZOR_API FScizorStateTreeCondition_ComboInputCheck : public FStateTreeConditionCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FScizorStateTreeCondition_ComboInputCheck_InstanceData;
    virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); };

    virtual bool TestCondition(FStateTreeExecutionContext& Context) const override
    {
        const auto Events = Context.GetEventsToProcessView();
        const auto& [MatchInput, Invert] = Context.GetInstanceData(*this);

        for (auto&& Event : Events)
        {
            if (Event.IsValid())
            {
                const auto* Payload = Event->Payload.GetPtr<FScizorComboInputEventPayload>();
                if (Payload)
                {
                    const auto Result = Payload->InputAction == MatchInput;
                    return Invert ? !Result : Result;
                }
            }
        }

        return Invert;
    };
};
