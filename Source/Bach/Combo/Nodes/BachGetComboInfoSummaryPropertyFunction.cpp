// Copyright 2019-Present tarnishablec. All Rights Reserved.


#include "BachGetComboInfoSummaryPropertyFunction.h"

#include "StateTreeExecutionContext.h"
#include "Bach/Combo/Components/BachComboComponent.h"

void FBachGetComboInfoSummaryPropertyFunction::Execute(FStateTreeExecutionContext& Context) const
{
    auto& [ComboComponent, Summary] = Context.GetInstanceData(*this);
    if (!ComboComponent)
    {
        return;
    }
    Summary = ComboComponent->GetComboInfoSummary();
}
