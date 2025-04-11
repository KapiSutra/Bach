// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeExecutionContext.h"
#include "Bach/Combo/BachTypes.h"
#include "Blueprint/StateTreeConditionBlueprintBase.h"
#include "BachComboInputCheck.generated.h"

class UInputAction;
/**
 * 
 */
UCLASS(DisplayName = "Combo Input Check (Bach)")
class BACH_API UBachComboInputCheck : public UStateTreeConditionBlueprintBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    TObjectPtr<UInputAction> MatchInput;

    UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
    bool Invert = false;

    virtual bool TestCondition(FStateTreeExecutionContext& Context) const override
    {
        const auto Events = Context.GetEventsToProcessView();

        for (auto&& Event : Events)
        {
            const auto& [InputAction] = Event.Get()->Payload.Get<FBachComboInputEventPayload>();
            const auto Result = InputAction == this->MatchInput;
            return Invert ? !Result : Result;
        }

        return Invert;
    };
};
