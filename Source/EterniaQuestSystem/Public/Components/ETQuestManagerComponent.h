// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/ETQuest.h"
#include "Data/ETQuestStep.h"
#include "ETQuestManagerComponent.generated.h"

class UETQuestEvent;
class UETQuest;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnQuestStatusChanged,
                                               UETQuestManagerComponent*, QuestManager, FName, QuestId, EQuestStatus, NewStatus);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnQuestStepStatusChanged,
                                               UETQuestManagerComponent*, QuestManager, FName, StepId, EQuestStepStatus, NewStatus);

UCLASS(ClassGroup=(Custom), DisplayName="Quest Manager", Category="Eternia", meta=(BlueprintSpawnableComponent))
class ETERNIAQUESTSYSTEM_API UETQuestManagerComponent : public UActorComponent {
	GENERATED_BODY()

public:

	UETQuestManagerComponent();

	void AcceptQuest(const FName& QuestId);

	void ChangeQuestStatus(const FName& QuestId, EQuestStatus NewStatus);

	void ReceiveQuestEvent(UETQuestEvent* QuestEvent);

	void CompleteTask(const FName& QuestTaskId);

	void FailTask(const FName& QuestTaskId);

	void IncrementTaskProgress(const FName& QuestTaskId, int32 Increment);

	UPROPERTY(BlueprintAssignable)
	FOnQuestStatusChanged OnQuestStatusChanged;

	UPROPERTY(BlueprintAssignable)
	FOnQuestStepStatusChanged OnQuestStepStatusChanged;

protected:

	TMap<FName, TObjectPtr<UETQuest>> Quests;

	virtual void BeginPlay() override;

private:

	void RegisterInSubsystem();
};
