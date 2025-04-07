// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ETQuestDefinition.h"
#include "ETStatuses.h"
#include "UObject/Object.h"
#include "ETQuestStep.generated.h"

class UETQuestTask;
class UETQuestStep;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatusChanged_QuestStep, UETQuestStep*, Step);

/**
 * 
 */
UCLASS()
class ETERNIAQUESTSYSTEM_API UETQuestStep : public UObject {
	GENERATED_BODY()

public:

	void SetDefinition(const FETQuestStepDefinition& InDefinition);

	FName GetId() const { return Definition.Identifier; }

	void IncrementTaskProgress(const FName& TaskId, int32 Increment);

	void CompleteTask(const FName& TaskId);

	void FailTask(const FName& TaskId);

	UPROPERTY(BlueprintAssignable)
	FOnStatusChanged_QuestStep OnStatusChanged;

private:

	UPROPERTY(BlueprintReadOnly, SaveGame, meta = (AllowPrivateAccess = true))
	TMap<FName, TObjectPtr<UETQuestTask>> Tasks;

	UPROPERTY(BlueprintReadOnly, SaveGame, meta=(AllowPrivateAccess=true))
	TEnumAsByte<EQuestStepStatus> Status = EQSS_Active;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FETQuestStepDefinition Definition;

	void SetStatus(EQuestStepStatus NewStatus);

	void SetTaskStatus(const FName TaskId, EQuestTaskStatus NewStatus);

	UFUNCTION()
	void OnTaskStatusChanged(UETQuestTask* UpdatedTask);
	
	void DoCleanup();

	void AddTaskByDefinition(const FETQuestTaskDefinition& TaskDef);
};
