// Copyright 2019-Present tarnishablec. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "Bach/Combo/ComboTypes.h"
#include "Treecko/Component/TreeckoStateComponent.h"
#include "ScizorComboComponent.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tag_StateTreeEvent_BachComboInput);

class UAnimNotify_PlayMontageNotifyWindow;

namespace Scizor
{
	extern const FGameplayTag DefaultComboEventTag;
}

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FScizorCrossComboWindowDelegate, bool, bWindowOpen);

UCLASS(ClassGroup=(Scizor), meta=(BlueprintSpawnableComponent))
class BACH_API UScizorComboComponent : public UTreeckoStateComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UScizorComboComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual bool SetContextRequirements(FStateTreeExecutionContext& Context, bool bLogErrors = false) override;

	virtual TSubclassOf<UStateTreeSchema> GetSchema() const override;
	////
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UAnimNotify_PlayMontageNotifyWindow> ComboWindowClass;

	UPROPERTY(BlueprintAssignable)
	FScizorCrossComboWindowDelegate OnCrossComboWindow;

	UFUNCTION(BlueprintPure)
	FScizorComboInfoSummary GetComboInfoSummary() const;

	FScizorComboInfoSummary ComboInfoSummaryCache;

	UFUNCTION(BlueprintCallable, meta=(CPP_Default_Tag = "StateTreeEvent.Bach.Combo.ComboInput", CPP_Default_Payload))
	void SendComboInputEvent(const FGameplayTag Tag = Scizor::DefaultComboEventTag,
	                         const TInstancedStruct<FScizorComboInputEventPayload>& Payload = {});

protected:
	UFUNCTION()
	void HandleAvatarMontageNotify(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
	UFUNCTION()
	void HandleMeshAnimInitialized();
	UFUNCTION()
	void HandleActorContextUpdated();
};
