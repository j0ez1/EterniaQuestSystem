// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ETQuestStep.h"

#include "Data/ETQuestTask.h"
#include "Helpers/ETLogging.h"

void UETQuestStep::SetDefinition(const FETQuestStepDefinition& InDefinition) {
	if (Definition.Identifier == InDefinition.Identifier) return;

	Definition = InDefinition;

	for (const FInstancedStruct& Decorator : Definition.Decorators) {
		FETQuestStepDecorator StepDecorator = Decorator.Get<FETQuestStepDecorator>();
		// TODO
	}

	DoCleanup();
	if (Definition.Tasks.IsEmpty()) {
		EQS_ULOGO_ERROR(TEXT("Failed to fill quest step with tasks: tasks array is empty"));
		return;
	}

	for (FETQuestTaskDefinition TaskDef : InDefinition.Tasks) {
		AddTaskByDefinition(TaskDef);
	}
}

void UETQuestStep::IncrementTaskProgress(const FName& TaskId, int32 Increment) {
	TObjectPtr<UETQuestTask>* Task = Tasks.Find(TaskId);
	if (Task && *Task) {
		(*Task)->IncrementProgress(Increment);
	}
}

void UETQuestStep::CompleteTask(const FName& TaskId) {
	SetTaskStatus(TaskId, EQTS_Completed);
}

void UETQuestStep::FailTask(const FName& TaskId) {
	SetTaskStatus(TaskId, EQTS_Failed);
}

void UETQuestStep::SetStatus(EQuestStepStatus NewStatus) {
	if (Status == NewStatus || Status == EQSS_Completed || Status == EQSS_Failed) return;

	Status = NewStatus;
	OnStatusChanged.Broadcast(this);
}

void UETQuestStep::SetTaskStatus(const FName TaskId, EQuestTaskStatus NewStatus) {
	TObjectPtr<UETQuestTask>* Task = Tasks.Find(TaskId);
	if (Task && *Task) {
		(*Task)->SetStatus(NewStatus);
	}
}

void UETQuestStep::OnTaskStatusChanged(UETQuestTask* UpdatedTask) {
	if (UpdatedTask->IsFailed() && UpdatedTask->IsMandatory()) {
		for (auto ExistingTask : Tasks) {
			ExistingTask.Value->SetStatus(EQTS_Skipped);
		}
		SetStatus(EQSS_Failed);
	} else if (UpdatedTask->IsCompleted()) {
		bool bAreMandatoryTasksCompleted = true;
		for (auto ExistingTask : Tasks) {
			if (ExistingTask.Value->IsMandatory() && ExistingTask.Value->IsFailed()) {
				bAreMandatoryTasksCompleted = false;
				break;
			}
		}
		if (bAreMandatoryTasksCompleted) {
			for (auto ExistingTask : Tasks) {
				if (!ExistingTask.Value->IsMandatory()) {
					ExistingTask.Value->SetStatus(EQTS_Skipped);
				}
			}
			SetStatus(EQSS_Completed);
		}
	}
}

void UETQuestStep::DoCleanup() {
	for (auto Task : Tasks) {
		if (Task.Value->OnStatusChanged.IsAlreadyBound(this, &UETQuestStep::OnTaskStatusChanged)) {
			Task.Value->OnStatusChanged.RemoveDynamic(this, &UETQuestStep::OnTaskStatusChanged);
		}
	}
	Tasks.Empty();
}

void UETQuestStep::AddTaskByDefinition(const FETQuestTaskDefinition& TaskDef) {
	UETQuestTask* Task = NewObject<UETQuestTask>(GetOuter());
	Task->SetDefinition(TaskDef);
	Task->OnStatusChanged.AddUniqueDynamic(this, &UETQuestStep::OnTaskStatusChanged);
	Tasks.Add(TaskDef.Identifier, Task);
}
