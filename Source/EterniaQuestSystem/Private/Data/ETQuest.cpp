// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ETQuest.h"

#include "Data/ETQuestDefinition.h"
#include "Data/ETQuestStep.h"

void UETQuest::SetDefinition(const FETQuestDefinition& InDefinition) {
	if (Definition.Identifier == InDefinition.Identifier) return;

	Definition = InDefinition;
	Steps.Empty();
	if (!InDefinition.Steps.IsEmpty()) {
		FETQuestStepDefinition StepDefinition = InDefinition.Steps[0];
		AddStepByDefinition(StepDefinition);
	}
}

void UETQuest::CompleteTask(const FName& QuestStepId, const FName& TaskId) {
	if (Status != EQS_Accepted) return;

	TObjectPtr<UETQuestStep>* Step = Steps.Find(QuestStepId);
	if (Step && *Step) {
		(*Step)->CompleteTask(TaskId);
	}
}

void UETQuest::FailTask(const FName& QuestStepId, const FName& TaskId) {
	if (Status != EQS_Accepted) return;

	TObjectPtr<UETQuestStep>* Step = Steps.Find(QuestStepId);
	if (Step && *Step) {
		(*Step)->FailTask(TaskId);
	}
}

void UETQuest::IncrementTaskProgress(const FName& QuestStepId, const FName& TaskId, int32 Increment) {
	if (Status != EQS_Accepted) return;

	TObjectPtr<UETQuestStep>* Step = Steps.Find(QuestStepId);
	if (Step && *Step) {
		(*Step)->IncrementTaskProgress(TaskId, Increment);
	}
}

FText UETQuest::GetFinishedDescription() const {
	switch (Status) {
		case EQS_Failed: return Definition.FailureDescription;
		case EQSS_Completed: return Definition.SuccessDescription;
		default: return FText();
	}
}

void UETQuest::OnStepStatusChanged(UETQuestStep* QuestStep) {
	
}

UETQuestStep* UETQuest::CreateStepByDefinition(const FETQuestStepDefinition& StepDefinition) {
	UETQuestStep* Result = NewObject<UETQuestStep>(GetOuter());
	Result->SetDefinition(StepDefinition);
	return Result;
}

void UETQuest::AddStepByDefinition(const FETQuestStepDefinition& StepDefinition) {
	UETQuestStep* NewStep = CreateStepByDefinition(StepDefinition);
	NewStep->OnStatusChanged.AddUniqueDynamic(this, &UETQuest::OnStepStatusChanged);
	Steps.Add(StepDefinition.Identifier, NewStep);
	OnStepAdded.Broadcast(NewStep);
}
