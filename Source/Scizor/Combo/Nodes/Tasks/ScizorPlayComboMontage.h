// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "ScizorPlayComboMontage.generated.h"

// USTRUCT(BlueprintType)
// struct SCIZOR_API FScizorComboMontageSetting
// {
//     GENERATED_BODY()
//
//     UPROPERTY(BlueprintReadOnly, EditAnywhere)
//     TObjectPtr<UAnimMontage> Montage;
//
//     UPROPERTY(BlueprintReadOnly, EditAnywhere)
//     FName Section;
// };

/**
 * 
 */
UCLASS()
class SCIZOR_API UScizorPlayComboMontage : public UStateTreeTaskBlueprintBase
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    TObjectPtr<UAnimMontage> Montage;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(GetOptions = GetSections))
    FName Section;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    float Rate = 1.f;

    

#if WITH_EDITOR
    UFUNCTION()
    TArray<FString> GetSections() const;
#endif
};
