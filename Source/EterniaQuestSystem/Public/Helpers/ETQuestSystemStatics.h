// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ETQuest.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ETQuestSystemStatics.generated.h"

struct FETQuestDefinition;
class UETQuestManagerComponent;
/**
 * 
 */
UCLASS(DisplayName="Eternia Quest System Function Library")
class ETERNIAQUESTSYSTEM_API UETQuestSystemStatics : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Eternia|Quest")
	static UETQuestManagerComponent* GetQuestManagerForPlayer(APlayerState* PlayerState);

	UFUNCTION(BlueprintCallable, Category="Eternia|Quest")
	static void AcceptQuest(APlayerState* PlayerState, const FName& QuestId);

	UFUNCTION(BlueprintCallable, Category="Eternia|Quest")
	static void IncrementTaskProgress(APlayerState* PlayerState, const FName& QuestId, const FName& QuestStepId, const FName& QuestTaskId, int32 Increment = 1);

	UFUNCTION(BlueprintCallable, Category="Eternia|Quest")
	static void CompleteTask(APlayerState* PlayerState, const FName& QuestId, const FName& QuestStepId, const FName& QuestTaskId);

	UFUNCTION(BlueprintCallable, Category="Eternia|Quest")
	static void FailTask(APlayerState* PlayerState, const FName& QuestId, const FName& QuestStepId, const FName& QuestTaskId);

	UFUNCTION(BlueprintCallable, Category="Eternia|Quest")
	static FETQuestDefinition GetQuestDefinitionById(UObject* WorldContextObject, const FName& QuestId);

private:

	static UETQuest* CreateQuestById(UObject* Outer, const FName& QuestId);

	static UETQuest* CreateQuestByDefinition(UObject* Outer, const FETQuestDefinition& QuestDefinition);
	
	static UDataTable* GetQuestDataTable(UObject* WorldContextObject);
};
