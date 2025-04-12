// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeExecutionContext.h"
#include "StateTreeTaskBase.h"
#include "BachIgnoreMoveInput.generated.h"


USTRUCT()
struct FBachIgnoreMoveInputInstanceData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    TObjectPtr<APawn> Pawn;

    UPROPERTY(EditAnywhere)
    bool bShouldIgnore = false;

    //

    UPROPERTY()
    mutable TWeakObjectPtr<AController> Controller;
    mutable bool bIsCurrentMoveInputIgnored = false;
    mutable bool bLastTickShouldIgnore = false;
};

/**
 * 
 */
USTRUCT(DisplayName = "Ignore Move Input (Bach)")
struct BACH_API FBachIgnoreMoveInput : public FStateTreeTaskCommonBase
{
    GENERATED_BODY()

    using FInstanceDataType = FBachIgnoreMoveInputInstanceData;

    virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); };

    virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
                                           const FStateTreeTransitionResult& Transition) const override
    {
        const auto& InstanceData = Context.GetInstanceData(*this);

        const auto Result = Super::EnterState(Context, Transition);

        InstanceData.Controller = InstanceData.Pawn->GetController();

        if (InstanceData.Controller.IsValid())
        {
            InstanceData.bIsCurrentMoveInputIgnored = InstanceData.Controller->IsMoveInputIgnored();
            InstanceData.bLastTickShouldIgnore = InstanceData.bIsCurrentMoveInputIgnored;
        }

        return Result;
    }

    virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override
    {
        const auto Result = Super::Tick(Context, DeltaTime);
        const auto& InstanceData = Context.GetInstanceData(*this);

        if (InstanceData.Controller.IsValid())
        {
            const auto IgnoreChanged = InstanceData.bShouldIgnore != InstanceData.bLastTickShouldIgnore;

            if (IgnoreChanged)
            {
                InstanceData.Controller->SetIgnoreMoveInput(InstanceData.bShouldIgnore);
            }

            InstanceData.bIsCurrentMoveInputIgnored = InstanceData.Controller->IsMoveInputIgnored();
            InstanceData.bLastTickShouldIgnore = InstanceData.bShouldIgnore;
        }

        return Result;
    }
};
