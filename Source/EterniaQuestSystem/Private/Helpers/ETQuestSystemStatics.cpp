// Fill out your copyright notice in the Description page of Project Settings.


#include "Helpers/ETQuestSystemStatics.h"

#include "ETQuestSubsystem.h"
#include "Components/ETQuestManagerComponent.h"
#include "Data/ETQuestDefinition.h"
#include "GameFramework/PlayerState.h"

UETQuestManagerComponent* UETQuestSystemStatics::GetQuestManagerForPlayer(APlayerState* PlayerState) {
	if (!PlayerState) return nullptr;
	
	UETQuestSubsystem* QuestSubsystem = UETQuestSubsystem::GetCurrent(PlayerState);
	if (!QuestSubsystem) return nullptr;

	return QuestSubsystem->GetManagerListener(PlayerState);
}

void UETQuestSystemStatics::AcceptQuest(APlayerState* PlayerState, const FString& QuestId) {
	UETQuestManagerComponent* QuestManagerComponent = GetQuestManagerForPlayer(PlayerState);
	if (!QuestManagerComponent) return;
	
	UETQuest* Quest = CreateQuestById(QuestManagerComponent, FName(QuestId));
	QuestManagerComponent->AcceptQuest(Quest);
}

void UETQuestSystemStatics::IncrementTaskProgress(APlayerState* PlayerState, const FString& QuestId, const FString& QuestStepId, const FString& QuestTaskId, int32 Increment) {
	UETQuestManagerComponent* QuestManagerComponent = GetQuestManagerForPlayer(PlayerState);
	if (!QuestManagerComponent) return;

	QuestManagerComponent->IncrementTaskProgress(FName(QuestId), FName(QuestStepId), FName(QuestTaskId), Increment);
}

void UETQuestSystemStatics::CompleteTask(APlayerState* PlayerState, const FString& QuestId, const FString& QuestStepId, const FString& QuestTaskId) {
	UETQuestManagerComponent* QuestManagerComponent = GetQuestManagerForPlayer(PlayerState);
	if (!QuestManagerComponent) return;

	QuestManagerComponent->CompleteTask(FName(QuestId), FName(QuestStepId), FName(QuestTaskId));
}

void UETQuestSystemStatics::FailTask(APlayerState* PlayerState, const FString& QuestId, const FString& QuestStepId, const FString& QuestTaskId) {
	UETQuestManagerComponent* QuestManagerComponent = GetQuestManagerForPlayer(PlayerState);
	if (!QuestManagerComponent) return;

	QuestManagerComponent->FailTask(FName(QuestId), FName(QuestStepId), FName(QuestTaskId));
}

UETQuest* UETQuestSystemStatics::CreateQuestById(UObject* Outer, const FName& QuestId) {
	FETQuestDefinition QuestDefinition = GetQuestDefinitionById(Outer, QuestId);
	return CreateQuestByDefinition(Outer, QuestDefinition);
}

UETQuest* UETQuestSystemStatics::CreateQuestByDefinition(UObject* Outer, const FETQuestDefinition& QuestDefinition) {
	UETQuest* Quest = NewObject<UETQuest>(Outer);
	Quest->SetDefinition(QuestDefinition);
	return Quest;
}

FETQuestDefinition UETQuestSystemStatics::GetQuestDefinitionById(UObject* WorldContextObject, const FName& QuestId) {
	UDataTable* QuestDataTable = GetQuestDataTable(WorldContextObject);
	if (!QuestDataTable) return FETQuestDefinition();

	TArray<FETQuestDefinition*> QuestDefinitions;
	QuestDataTable->GetAllRows<FETQuestDefinition>("", QuestDefinitions);
	for (FETQuestDefinition* QuestDefinition : QuestDefinitions) {
		if (QuestDefinition->Identifier.IsEqual(QuestId)) {
			return *QuestDefinition;
		}
	}
	return FETQuestDefinition();
}

UDataTable* UETQuestSystemStatics::GetQuestDataTable(UObject* WorldContextObject) {
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (World) {
		UGameInstance* GameInstance = World->GetGameInstance();
		if (GameInstance) {
			UETQuestSubsystem* QuestSubsystem = GameInstance->GetSubsystem<UETQuestSubsystem>();
			if (QuestSubsystem) {
				return QuestSubsystem->GetQuestDataTable();
			}
		}
	}
	return nullptr;
}
