// Copyright 2019-Present tarnishablec. All Rights Reserved.


#include "ScizorPlayComboMontage.h"

#if  WITH_EDITOR
TArray<FString> UScizorPlayComboMontage::GetSections() const
{
    TArray<FString> Result{};
    if (Montage)
    {
        for (auto&& CompositeSection : Montage->CompositeSections)
        {
            Result.AddUnique(CompositeSection.SectionName.ToString());
        }
    }

    return Result;
}
#endif
