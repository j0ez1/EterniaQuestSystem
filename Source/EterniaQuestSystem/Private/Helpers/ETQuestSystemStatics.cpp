// Fill out your copyright notice in the Description page of Project Settings.


#include "Helpers/ETQuestSystemStatics.h"

#include "ETQuestSubsystem.h"
#include "Components/ETQuestManagerComponent.h"
#include "Data/ETQuestDefinition.h"
#include "Helpers/ETLogging.h"
#include "Event/ETQuestEvent.h"
#include "GameFramework/PlayerState.h"
#include "StructUtils/InstancedStruct.h"

UETQuestManagerComponent* UETQuestSystemStatics::GetQuestManagerForPlayer(APlayerState* PlayerState) {
	if (!PlayerState) return nullptr;
	
	UETQuestSubsystem* QuestSubsystem = UETQuestSubsystem::GetCurrent(PlayerState);
	if (!QuestSubsystem) return nullptr;

	return QuestSubsystem->GetManagerListener(PlayerState);
}

void UETQuestSystemStatics::AcceptQuest(APlayerState* PlayerState, const FName& QuestId) {
	UETQuestManagerComponent* QuestManagerComponent = GetQuestManagerForPlayer(PlayerState);
	if (!QuestManagerComponent) return;

	QuestManagerComponent->AcceptQuest(QuestId);
}

void UETQuestSystemStatics::IncrementTaskProgress(APlayerState* PlayerState, const FName& QuestTaskId, int32 Increment) {
	UETQuestManagerComponent* QuestManagerComponent = GetQuestManagerForPlayer(PlayerState);
	if (!QuestManagerComponent) return;

	QuestManagerComponent->IncrementTaskProgress(QuestTaskId, Increment);
}

void UETQuestSystemStatics::CompleteTask(APlayerState* PlayerState, const FName& QuestTaskId) {
	UETQuestManagerComponent* QuestManagerComponent = GetQuestManagerForPlayer(PlayerState);
	if (!QuestManagerComponent) return;

	QuestManagerComponent->CompleteTask(QuestTaskId);
}

void UETQuestSystemStatics::FailTask(APlayerState* PlayerState, const FName& QuestTaskId) {
	UETQuestManagerComponent* QuestManagerComponent = GetQuestManagerForPlayer(PlayerState);
	if (!QuestManagerComponent) return;

	QuestManagerComponent->FailTask(QuestTaskId);
}

UETQuest* UETQuestSystemStatics::CreateQuestById(UObject* WorldContextObject, const FName& QuestId) {
	FETQuestDefinition QuestDefinition = GetQuestDefinitionById(WorldContextObject, QuestId);
	return CreateQuestByDefinition(QuestDefinition);
}

UETQuest* UETQuestSystemStatics::CreateQuestByDefinition(const FETQuestDefinition& QuestDefinition) {
	UETQuest* Quest = NewObject<UETQuest>();

	Quest->SetDefinitionId(QuestDefinition.Identifier);
	for (FETQuestStepDefinition StepDefinition : QuestDefinition.Steps) {
		for (const FInstancedStruct& Decorator : StepDefinition.Decorators) {
			FETQuestStepDecorator StepDecorator = Decorator.Get<FETQuestStepDecorator>();
			// TODO
		}
	}

	return Quest;
}

FETQuestDefinition UETQuestSystemStatics::GetQuestDefinitionById(UObject* WorldContextObject, const FName& QuestId) {
	UDataTable* QuestDataTable = GetQuestDataTable(WorldContextObject);
	if (!QuestDataTable) return FETQuestDefinition();

	TArray<FETQuestDefinition*> QuestDefinitions;
	QuestDataTable->GetAllRows<FETQuestDefinition>("", QuestDefinitions);
	for (FETQuestDefinition* QuestDefinition : QuestDefinitions) {
		if (QuestDefinition->Identifier == QuestId) {
			return *QuestDefinition;
		}
	}
	return FETQuestDefinition();
}

void UETQuestSystemStatics::ReportQuestEvent(UETQuestEvent* QuestEvent) {
	if (!QuestEvent) return;
	if (!QuestEvent->GetReporter()) return;
	
	UETQuestSubsystem* QuestSubsystem = UETQuestSubsystem::GetCurrent(QuestEvent->GetReporter());
	if (!QuestSubsystem) {
		EQS_ULOGS_ERROR(TEXT("Failed to route quest event to subsystem: QuestSubsystem is null"))
		return;
	}
	
	QuestSubsystem->OnEvent(QuestEvent);
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
