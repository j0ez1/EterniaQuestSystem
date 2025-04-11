// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "EterniaQuestSystemSettings.generated.h"

/**
 * 
 */
UCLASS(Config = EterniaSettings, DefaultConfig, DisplayName="Eternia Quest System", meta=(ScriptName="QuestSystemSettings"))
class ETERNIAQUESTSYSTEM_API UEterniaQuestSystemSettings : public UDeveloperSettings {
	GENERATED_BODY()

public:
	UEterniaQuestSystemSettings(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Config, meta = (RequiredAssetDataTags = "RowStructure=/Script/EterniaQuestSystem.ETQuestDefinition"))
	TSoftObjectPtr<UDataTable> QuestData;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Config)
	// bool bPauseTaskTimersOnGamePause = true;

	/*
	 * true - all sequential quest step tasks will be added on step creation.
	 * false - a new task will be added if previous one is successfully finished
	 */
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Config)
	// bool bAddAllSequentialTasks = false;
};
