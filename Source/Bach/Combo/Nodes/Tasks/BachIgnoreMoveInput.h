// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "BachIgnoreMoveInput.generated.h"

/**
 * 
 */
UCLASS(DisplayName = "Ignore Move Input (Bach)")
class BACH_API UBachIgnoreMoveInput : public UStateTreeTaskBlueprintBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    TObjectPtr<APawn> Pawn;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    bool bShouldIgnore = false;

    //

    virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
                                           const FStateTreeTransitionResult& Transition) override
    {
        const auto Result = Super::EnterState(Context, Transition);

        Controller = Pawn->GetController();

        if (Controller.IsValid())
        {
            bIsCurrentMoveInputIgnored = Controller->IsMoveInputIgnored();
            bLastTickShouldIgnore = bIsCurrentMoveInputIgnored;
        }

        return Result;
    }

    virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) override
    {
        const auto Result = Super::Tick(Context, DeltaTime);


        if (Controller.IsValid())
        {
            const auto IgnoreChanged = bShouldIgnore != bLastTickShouldIgnore;

            if (IgnoreChanged)
            {
                Controller->SetIgnoreMoveInput(bShouldIgnore);
            }

            bIsCurrentMoveInputIgnored = Controller->IsMoveInputIgnored();
            bLastTickShouldIgnore = bShouldIgnore;
        }

        return Result;
    }

protected:
    UPROPERTY()
    TWeakObjectPtr<AController> Controller;

    bool bIsCurrentMoveInputIgnored = false;
    bool bLastTickShouldIgnore = false;
};
