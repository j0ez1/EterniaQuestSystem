// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ETQuest.h"

void UETQuest::SetIsTracked(bool bInIsTracked) {

}

bool UETQuest::CanChangeStatus(EQuestStatus InStatus) {
	return Status != InStatus
	// TODO
	// && (Status == EQuestStatus::EQS_NotStarted && (InStatus == EQuestStatus::EQS_Accepted || InStatus == EQuestStatus::EQS_Completed || InStatus == EQuestStatus::EQS_Failed))
	;
}

bool UETQuest::SetStatus(EQuestStatus InStatus) {
	if (CanChangeStatus(InStatus)) {
		Status = InStatus;
		return true;
	}
	return false;
}
