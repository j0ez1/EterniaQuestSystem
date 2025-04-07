// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ETQuestSubsystem.generated.h"

class UETQuestManagerComponent;
/**
 * 
 */
UCLASS()
class ETERNIAQUESTSYSTEM_API UETQuestSubsystem : public UGameInstanceSubsystem {
	GENERATED_BODY()

public:

	static UETQuestSubsystem* GetCurrent(UObject* WorldContextObject);

	void RegisterManagerListener(UETQuestManagerComponent* Listener);

	UETQuestManagerComponent* GetManagerListener(APlayerState* PlayerState);

	FORCEINLINE UDataTable* GetQuestDataTable() const { return QuestDataTable; }

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

private:

	UPROPERTY()
	TMap<TObjectPtr<APlayerState>, TObjectPtr<UETQuestManagerComponent>> ManagerListeners;

	UPROPERTY()
	TObjectPtr<UDataTable> QuestDataTable;

	void LoadSettings();
};
