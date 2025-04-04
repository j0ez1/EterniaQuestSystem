// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ETQuestManagerComponent.h"

#include "Helpers/ETLogging.h"
#include "Helpers/ETQuestSystemStatics.h"
#include "ETQuestSubsystem.h"
#include "Data/ETQuest.h"


UETQuestManagerComponent::UETQuestManagerComponent() {
	PrimaryComponentTick.bCanEverTick = false;

}

void UETQuestManagerComponent::AcceptQuest(const FName& QuestId) {
	ChangeQuestStatus(QuestId, EQuestStatus::EQS_Accepted);
}

void UETQuestManagerComponent::ChangeQuestStatus(const FName& QuestId, EQuestStatus NewStatus) {
	UETQuest* Quest;
	if (Quests[QuestId] != nullptr) {
		Quest = Quests[QuestId];
	} else {
		Quest = UETQuestSystemStatics::CreateQuestById(this, QuestId);
		Quests.Add(QuestId, Quest);
	}
	if (Quest->SetStatus(NewStatus)) {
		OnQuestStatusChanged.Broadcast(this, Quest->GetDefinitionId(), Quest->GetStatus());	
	}
}

void UETQuestManagerComponent::ReceiveQuestEvent(UETQuestEvent* QuestEvent) {
	
}

void UETQuestManagerComponent::CompleteTask(const FName& QuestTaskId) {
}

void UETQuestManagerComponent::FailTask(const FName& QuestTaskId) {
}

void UETQuestManagerComponent::IncrementTaskProgress(const FName& QuestTaskId, int32 Increment) {
}

void UETQuestManagerComponent::BeginPlay() {
	Super::BeginPlay();

	RegisterInSubsystem();
}

void UETQuestManagerComponent::RegisterInSubsystem() {
	UETQuestSubsystem* QuestWorldSubsystem = UETQuestSubsystem::GetCurrent(this);
	if (QuestWorldSubsystem) {
		QuestWorldSubsystem->RegisterManagerListener(this);	
	} else {
		EQS_ULOG_ERROR(TEXT("Failed to register in quest subsystem because it is null"))
	}
}
