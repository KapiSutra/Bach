// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "Bach/Combo/BachTypes.h"
#include "Morzat/Component/MorzatStateTreeComponent.h"
#include "BachComboComponent.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_StateTreeEvent_BachComboInput);

namespace Bach
{
    const FGameplayTag DefaultComboEventTag = Tag_StateTreeEvent_BachComboInput;
}

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBachCrossComboWindowDelegate, bool, bWindowOpen);

UCLASS(ClassGroup=(Bach), meta=(BlueprintSpawnableComponent))
class BACH_API UBachComboComponent : public UMorzatStateTreeComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UBachComboComponent();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;
    virtual bool SetContextRequirements(FStateTreeExecutionContext& Context, bool bLogErrors = false) override;

    virtual TSubclassOf<UStateTreeSchema> GetSchema() const override;
    ////
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<UAnimNotifyState> ComboWindowNotifyState;

    UPROPERTY(BlueprintAssignable)
    FBachCrossComboWindowDelegate OnCrossComboWindow;

    UFUNCTION(BlueprintPure)
    FBachComboInfoSummary GetComboInfoSummary() const;

    UFUNCTION(BlueprintCallable)
    void SendComboInputEvent(const FGameplayTag Tag,
                             const FBachComboInputEventPayload& Payload);

protected:
    UFUNCTION()
    void HandleAvatarMontageNotify(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
};
