// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Treecko/Schema/TreeckoStateSchema.h"
#include "ScizorComboSchema.generated.h"

/**
 * 
 */
UCLASS()
class SCIZOR_API UScizorComboSchema : public UTreeckoStateSchema
{
    GENERATED_BODY()

    UScizorComboSchema()
    {
        StateTreeComponentType = UScizorComboComponent::StaticClass();
        ContextDataDescs[2].Struct = StateTreeComponentType.Get();
    };
};
