// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "BachTypes.generated.h"


UENUM(BlueprintType, meta=(Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EBachComboWindowState : uint8
{
    None = 0 UMETA(Hidden),
    NoCombo = 1 << 0 UMETA(DisplayName = "NoCombo"),
    BeforeComboWindow = 1 << 1 UMETA(DisplayName = "BeforeComboWindow"),
    InsideComboWindow = 1 << 2 UMETA(DisplayName = "InsideComboWindow"),
    AfterComboWindow = 1 << 3 UMETA(DisplayName = "AfterComboWindow"),
};

ENUM_CLASS_FLAGS(EBachComboWindowState);


USTRUCT(BlueprintType)
struct BACH_API FBachComboInfoSummary
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    EBachComboWindowState ComboWindowState = EBachComboWindowState::NoCombo;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    TObjectPtr<UAnimMontage> MontageAsset;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    FName CurrentSection;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    float CurrentPosition = -1.f;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    float CurrentComboWindowRemainTime = -1.f;

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
    float CurrentComboWindowDuration = -1.f;
};


USTRUCT(BlueprintType)
struct BACH_API FBachComboInputEventPayload
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    TObjectPtr<UInputAction> InputAction;
};
