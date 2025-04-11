// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ETQuestManagerComponent.h"

#include "Helpers/ETLogging.h"
#include "ETQuestSubsystem.h"
#include "Data/ETQuest.h"


UETQuestManagerComponent::UETQuestManagerComponent() {
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UETQuestManagerComponent::AcceptQuest(UETQuest* Quest) {
	if (Quest && !Quests.Contains(Quest->GetId())) {
		Quests.Add(Quest->GetId(), Quest);

		Quest->OnStatusChanged.AddUniqueDynamic(this, &UETQuestManagerComponent::OnStatusChanged_Quest);
		OnStatusChanged_Quest(Quest);
	}
}

void UETQuestManagerComponent::CompleteTask(const FName& QuestId, const FName& QuestStepId, const FName& QuestTaskId) {
	TObjectPtr<UETQuest>* QuestPtr = Quests.Find(QuestId);
	if (QuestPtr && *QuestPtr) {
		(*QuestPtr)->CompleteTask(QuestStepId, QuestTaskId);
	} else {
		EQS_ULOG_WARNING(TEXT("Cannot complete quest task: quest '%s' is not found"), *QuestId.ToString());
	}
}

void UETQuestManagerComponent::FailTask(const FName& QuestId, const FName& QuestStepId, const FName& QuestTaskId) {
	TObjectPtr<UETQuest>* QuestPtr = Quests.Find(QuestId);
	if (QuestPtr && *QuestPtr) {
		(*QuestPtr)->FailTask(QuestStepId, QuestTaskId);
	} else {
		EQS_ULOG_WARNING(TEXT("Cannot fail quest task: quest '%s' is not found"), *QuestId.ToString());
	}
}

void UETQuestManagerComponent::IncrementTaskProgress(const FName& QuestId, const FName& QuestStepId, const FName& QuestTaskId, int32 Increment) {
	TObjectPtr<UETQuest>* QuestPtr = Quests.Find(QuestId);
	if (QuestPtr && *QuestPtr) {
		(*QuestPtr)->IncrementTaskProgress(QuestStepId, QuestTaskId, Increment);
	} else {
		EQS_ULOG_WARNING(TEXT("Cannot increment quest task progress: quest '%s' is not found"), *QuestId.ToString());
	}
}

TArray<TObjectPtr<UETQuest>> UETQuestManagerComponent::GetQuests() const {
	TArray<TObjectPtr<UETQuest>> OutArray;
	Quests.GenerateValueArray(OutArray);
	return OutArray;
}

void UETQuestManagerComponent::InitializeComponent() {
	Super::InitializeComponent();

	RegisterInSubsystem();
}

void UETQuestManagerComponent::OnStatusChanged_Quest(UETQuest* Quest) {
	OnQuestStatusChanged.Broadcast(this, Quest);
}

void UETQuestManagerComponent::RegisterInSubsystem() {
	UETQuestSubsystem* QuestWorldSubsystem = UETQuestSubsystem::GetCurrent(this);
	if (QuestWorldSubsystem) {
		QuestWorldSubsystem->RegisterManagerListener(this);
	} else {
		EQS_ULOG_ERROR(TEXT("Failed to register in quest subsystem because it is null"))
	}
}
