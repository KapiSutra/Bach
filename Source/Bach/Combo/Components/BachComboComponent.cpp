// Copyright 2019-Present tarnishablec. All Rights Reserved.


#include "BachComboComponent.h"

#include "StateTree.h"
#include "Bach/Combo/Animation/AnimNotifyState_BachComboWindow.h"
#include "Bach/Combo/Schema/BachComboSchema.h"

UE_DEFINE_GAMEPLAY_TAG(Tag_StateTreeEvent_BachComboInput, "StateTreeEvent.Bach.Combo.ComboInput");

// Sets default values for this component's properties
UBachComboComponent::UBachComboComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...

    ComboWindowNotifyState = UAnimNotifyState_BachComboWindow::StaticClass();
}

bool UBachComboComponent::SetContextRequirements(FStateTreeExecutionContext& Context, bool bLogErrors)
{
    return Super::SetContextRequirements(Context, bLogErrors);
}

TSubclassOf<UStateTreeSchema> UBachComboComponent::GetSchema() const
{
    return UBachComboSchema::StaticClass();
}


// Called when the game starts
void UBachComboComponent::BeginPlay()
{
    Super::BeginPlay();

    // ...

    if (!ActorContext.MeshComponent)
    {
        return;
    }

    const auto AnimInstance = ActorContext.MeshComponent->GetAnimInstance();

    if (!AnimInstance)
    {
        return;
    }

    AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &ThisClass::HandleAvatarMontageNotify);
    AnimInstance->OnPlayMontageNotifyEnd.AddDynamic(this, &ThisClass::HandleAvatarMontageNotify);
}

FBachComboInfoSummary UBachComboComponent::GetComboInfoSummary() const
{
    const auto Owner = ActorContext.Owner;
    const auto Avatar = ActorContext.Avatar;
    const auto MeshComponent = ActorContext.MeshComponent;
    const auto AbilitySystemComponent = ActorContext.AbilitySystemComponent;

    if (!Owner || !Avatar || !MeshComponent || !AbilitySystemComponent)
    {
        return {};
    }

    const auto AnimInstance = MeshComponent->GetAnimInstance();

    if (!AnimInstance || !AnimInstance->IsAnyMontagePlaying())
    {
        return {};
    }

    const auto MontageInstance = AnimInstance->GetActiveMontageInstance();

    if (!MontageInstance)
    {
        return {};
    }

    bool IsInComboWindow = false;

    const auto TargetProperty = MontageInstance->StaticStruct()->FindPropertyByName("ActiveStateBranchingPoints");
    TArray<FAnimNotifyEvent> ActiveStateBranchingPoints;
    TargetProperty->GetValue_InContainer(MontageInstance, &ActiveStateBranchingPoints);

    for (auto&& Event : ActiveStateBranchingPoints)
    {
        if (Event.NotifyStateClass && Event.NotifyStateClass.IsA(ComboWindowNotifyState))
        {
            IsInComboWindow = true;
        }
    }

    const auto MontageAsset = MontageInstance->Montage;
    const auto CurrentSection = MontageInstance->GetCurrentSection();
    const auto CurrentPosition = MontageInstance->GetPosition();

    float CurrentSectionStartTime;
    float CurrentSectionEndTime;
    MontageInstance->Montage->GetSectionStartAndEndTime(MontageAsset->GetSectionIndex(CurrentSection),
                                                        CurrentSectionStartTime, CurrentSectionEndTime);

    FAnimNotifyContext Context;
    MontageAsset->GetAnimNotifiesFromDeltaPositions(CurrentSectionStartTime, CurrentSectionEndTime,
                                                    Context);

    const auto ComboNSEvent = Context.ActiveNotifies.FindByPredicate([&](const FAnimNotifyEventReference& Event)
    {
        return Event.GetNotify()->NotifyStateClass.IsA(ComboWindowNotifyState);
    });

    if (!ComboNSEvent)
    {
        return {};
    }

    const auto StartTime = ComboNSEvent->GetNotify()->GetTriggerTime();
    const auto Duration = ComboNSEvent->GetNotify()->Duration;
    const auto EndTime = ComboNSEvent->GetNotify()->GetEndTriggerTime();
    const auto RemainTime = EndTime - CurrentPosition;

    FBachComboInfoSummary Result{
        .ComboWindowState = EBachComboWindowState::NoCombo,
        .MontageAsset = MontageAsset,
        .CurrentSection = CurrentSection,
        .CurrentPosition = CurrentPosition,
        .CurrentComboWindowRemainTime = RemainTime,
        .CurrentComboWindowDuration = Duration,
    };

    if (IsInComboWindow)
    {
        Result.ComboWindowState = EBachComboWindowState::InsideComboWindow;
    }

    if (CurrentPosition < StartTime)
    {
        Result.ComboWindowState = EBachComboWindowState::BeforeComboWindow;
    }

    if (CurrentPosition > EndTime)
    {
        Result.ComboWindowState = EBachComboWindowState::AfterComboWindow;
    }

    return Result;
}

void UBachComboComponent::SendComboInputEvent(const FGameplayTag Tag, const FBachComboInputEventPayload& Payload)
{
    SendStateTreeEvent(FStateTreeEvent(Tag, FInstancedStruct::Make(Payload), *this->GetName()));
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UBachComboComponent::HandleAvatarMontageNotify(FName NotifyName,
                                                    const FBranchingPointNotifyPayload& BranchingPointPayload)
{
    const auto& NotifyState = BranchingPointPayload.NotifyEvent->NotifyStateClass;
    if (!NotifyState.IsA(ComboWindowNotifyState))
    {
        return;
    }

    OnCrossComboWindow.Broadcast(GetComboInfoSummary().ComboWindowState == EBachComboWindowState::InsideComboWindow);
}
