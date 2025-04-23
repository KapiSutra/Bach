// Copyright 2019-Present tarnishablec. All Rights Reserved.


#include "ScizorComboComponent.h"

#include "StateTree.h"
#include "Scizor/Combo/Animation/AnimNotifyState_ScizorComboWindow.h"
#include "Scizor/Combo/Schema/ScizorComboSchema.h"

UE_DEFINE_GAMEPLAY_TAG(Tag_StateTreeEvent_BachComboInput, "Scizor.Combo.ComboInput");

namespace Scizor
{
	const FGameplayTag DefaultComboEventTag = Tag_StateTreeEvent_BachComboInput;
}

// Sets default values for this component's properties
UScizorComboComponent::UScizorComboComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	ComboWindowClass = UAnimNotifyState_ScizorComboWindow::StaticClass();
}


bool UScizorComboComponent::SetContextRequirements(FStateTreeExecutionContext& Context, bool bLogErrors)
{
	return Super::SetContextRequirements(Context, bLogErrors);
}

TSubclassOf<UStateTreeSchema> UScizorComboComponent::GetSchema() const
{
	return UScizorComboSchema::StaticClass();
}


// Called when the game starts
void UScizorComboComponent::BeginPlay()
{
	OnActorContextUpdated.AddUniqueDynamic(this, &ThisClass::HandleActorContextUpdated);
	//
	Super::BeginPlay();
}

FScizorComboInfoSummary UScizorComboComponent::GetComboInfoSummary() const
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
		if (Event.NotifyStateClass && Event.NotifyStateClass.IsA(ComboWindowClass))
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
		return Event.GetNotify()->NotifyStateClass.IsA(ComboWindowClass);
	});

	if (!ComboNSEvent)
	{
		return {};
	}

	const auto StartTime = ComboNSEvent->GetNotify()->GetTriggerTime();
	const auto Duration = ComboNSEvent->GetNotify()->Duration;
	const auto EndTime = ComboNSEvent->GetNotify()->GetEndTriggerTime();
	const auto RemainTime = EndTime - CurrentPosition;

	FScizorComboInfoSummary Result{
		.ComboWindowState = EScizorComboWindowState::NoCombo,
		.MontageAsset = MontageAsset,
		.CurrentSection = CurrentSection,
		.CurrentPosition = CurrentPosition,
		.CurrentComboWindowRemainTime = RemainTime,
		.CurrentComboWindowDuration = Duration,
	};

	if (IsInComboWindow)
	{
		Result.ComboWindowState = EScizorComboWindowState::InsideComboWindow;
	}

	if (CurrentPosition < StartTime)
	{
		Result.ComboWindowState = EScizorComboWindowState::BeforeComboWindow;
	}

	if (CurrentPosition > EndTime)
	{
		Result.ComboWindowState = EScizorComboWindowState::AfterComboWindow;
	}

	return Result;
}

void UScizorComboComponent::SendComboInputEvent(const FGameplayTag Tag,
                                              const TInstancedStruct<FScizorComboInputEventPayload>& Payload)
{
	SendStateTreeEvent(FStateTreeEvent(Tag, FInstancedStruct::Make(Payload.Get()), *this->GetName()));
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UScizorComboComponent::HandleAvatarMontageNotify(FName NotifyName,
                                                    const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	const auto& NotifyState = BranchingPointPayload.NotifyEvent->NotifyStateClass;
	if (!NotifyState.IsA(ComboWindowClass))
	{
		return;
	}

	OnCrossComboWindow.Broadcast(GetComboInfoSummary().ComboWindowState == EScizorComboWindowState::InsideComboWindow);
}

void UScizorComboComponent::HandleMeshAnimInitialized()
{
	const auto AnimInstance = ActorContext.MeshComponent->GetAnimInstance();

	if (!AnimInstance)
	{
		return;
	}

	AnimInstance->OnPlayMontageNotifyBegin.AddUniqueDynamic(this, &ThisClass::HandleAvatarMontageNotify);
	AnimInstance->OnPlayMontageNotifyEnd.AddUniqueDynamic(this, &ThisClass::HandleAvatarMontageNotify);
}


void UScizorComboComponent::HandleActorContextUpdated()
{
	if (ActorContext.MeshComponent)
	{
		ActorContext.MeshComponent->OnAnimInitialized.AddUniqueDynamic(this, &ThisClass::HandleMeshAnimInitialized);
	}
}
