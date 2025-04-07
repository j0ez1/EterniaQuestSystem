// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ETQuestDefinition.h"
#include "ETStatuses.h"
#include "UObject/Object.h"
#include "ETQuestTask.generated.h"

class UETQuestTask;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatusChanged_QuestTask, UETQuestTask*, Task);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProgressUpdate_QuestTask, UETQuestTask*, Task);

/**
 * 
 */
UCLASS()
class ETERNIAQUESTSYSTEM_API UETQuestTask : public UObject {
	GENERATED_BODY()

public:

	void ResetTimer();

	void SetDefinition(const FETQuestTaskDefinition& InDefinition);

	UFUNCTION(BlueprintCallable)
	bool IsMandatory() const { return Definition.bMandatory; }

	void SetStatus(EQuestTaskStatus NewStatus);

	void SetProgress(int32 NewProgress);

	EQuestTaskStatus GetStatus() const { return Status; }

	bool IsFailed() const { return Status == EQTS_Failed; }

	bool IsCompleted() const { return Status == EQTS_Completed; }

	void IncrementProgress(int32 Increment);

	FName GetId() const { return Definition.Identifier; }

	UPROPERTY(BlueprintAssignable)
	FOnStatusChanged_QuestTask OnStatusChanged;

	UPROPERTY(BlueprintAssignable)
	FOnProgressUpdate_QuestTask OnProgressUpdate;

private:

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	FETQuestTaskDefinition Definition;

	UPROPERTY(BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = true))
	TEnumAsByte<EQuestTaskStatus> Status = EQTS_Active;

	UPROPERTY(BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = true))
	int32 Progress = 0;

	FTimerHandle Timer;

	void OnTimerFinished();

	void StopTimer();
};
