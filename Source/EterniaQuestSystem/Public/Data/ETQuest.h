// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ETQuestDefinition.h"
#include "ETStatuses.h"
#include "UObject/Object.h"
#include "ETQuest.generated.h"

class UETQuestStep;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatusChanged_Quest, UETQuest*, Quest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStepAdded, UETQuestStep*, Step);

/**
 * 
 */
UCLASS()
class ETERNIAQUESTSYSTEM_API UETQuest : public UObject {
	GENERATED_BODY()

public:

	void SetIsTracked(bool bInIsTracked) { bIsTracked = bInIsTracked; }

	FORCEINLINE EQuestStatus GetStatus() const { return Status; }

	void SetDefinition(const FETQuestDefinition& InDefinition);

	FORCEINLINE FName GetId() const { return Definition.Identifier; }

	void CompleteTask(const FName& QuestStepId, const FName& TaskId);

	void FailTask(const FName& QuestStepId, const FName& TaskId);

	void IncrementTaskProgress(const FName& QuestStepId, const FName& TaskId, int32 Increment);

	FText GetAcceptedDescription() const { return Definition.Description; }

	FText GetFinishedDescription() const;
	
	UPROPERTY(BlueprintAssignable)
	FOnStatusChanged_Quest OnStatusChanged;

	UPROPERTY(BlueprintAssignable)
	FOnStepAdded OnStepAdded;

private:

	UPROPERTY(BlueprintReadOnly, SaveGame, meta=(AllowPrivateAccess=true))
	TMap<FName, TObjectPtr<UETQuestStep>> Steps;

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FETQuestDefinition Definition;

	UPROPERTY(SaveGame)
	TEnumAsByte<EQuestStatus> Status = EQS_Accepted;

	UPROPERTY(BlueprintReadOnly, SaveGame, meta=(AllowPrivateAccess=true))
	bool bIsTracked;

	UFUNCTION()
	void OnStepStatusChanged(UETQuestStep* QuestStep);

	UETQuestStep* CreateStepByDefinition(const FETQuestStepDefinition& StepDefinition);

	void AddStepByDefinition(const FETQuestStepDefinition& StepDefinition);
};
