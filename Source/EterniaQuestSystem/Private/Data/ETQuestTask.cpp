// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ETQuestTask.h"

#include "Helpers/ETLogging.h"

UETQuestTask::UETQuestTask(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
, Status(EQuestTaskStatus::EQTS_Active)
, Progress(0) {
}

void UETQuestTask::ResetTimer() {
	if (Definition.TimeLimit > 0) {
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &UETQuestTask::OnTimerFinished, Definition.TimeLimit, false);
	}
}

void UETQuestTask::SetDefinition(const FETQuestTaskDefinition& InDefinition) {
	if (Definition.Identifier == InDefinition.Identifier) return;

	Definition = InDefinition;
	ResetTimer();
}

void UETQuestTask::SetStatus(EQuestTaskStatus NewStatus) {
	if (Status == NewStatus || Status == EQuestTaskStatus::EQTS_Completed || Status == EQuestTaskStatus::EQTS_Failed || Status ==
		EQuestTaskStatus::EQTS_Skipped) return;

	Status = NewStatus;

	if (Status != EQuestTaskStatus::EQTS_Active) {
		StopTimer();
	}

	OnStatusChanged.Broadcast(this);
}

void UETQuestTask::SetProgress(int32 NewProgress) {
	if (Progress != NewProgress) {
		Progress = NewProgress;
		OnProgressUpdate.Broadcast(this);
		if (Progress == Definition.TargetNumber) {
			SetStatus(EQuestTaskStatus::EQTS_Completed);
		}
	}
}

void UETQuestTask::IncrementProgress(int32 Increment) {
	if (Definition.TargetNumber <= 0) {
		EQS_ULOGO_WARNING(TEXT("Cannot increment progress for a task '%s' with TargetNumber equal to 0"), *Definition.Identifier.ToString())
		return;
	}
	int32 NewProgress = FMath::Clamp(Progress + Increment, 0, Definition.TargetNumber);
	SetProgress(NewProgress);
}

void UETQuestTask::OnTimerFinished() {
	SetStatus(EQuestTaskStatus::EQTS_Failed);
}

void UETQuestTask::StopTimer() {
	GetWorld()->GetTimerManager().ClearTimer(Timer);
}
