// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/ETQuest.h"
#include "ETQuestManagerComponent.generated.h"

class UETQuestEvent;
class UETQuest;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQuestStatusChanged_QuestManager, UETQuestManagerComponent*, QuestManager, UETQuest*, AcceptedQuest);

UCLASS(ClassGroup=(Custom), DisplayName="Quest Manager", Category="Eternia", meta=(BlueprintSpawnableComponent))
class ETERNIAQUESTSYSTEM_API UETQuestManagerComponent : public UActorComponent {
	GENERATED_BODY()

public:

	UETQuestManagerComponent();

	void AcceptQuest(UETQuest* Quest);

	void CompleteTask(const FName& QuestId, const FName& QuestStepId, const FName& QuestTaskId);

	void FailTask(const FName& QuestId, const FName& QuestStepId, const FName& QuestTaskId);

	void IncrementTaskProgress(const FName& QuestId, const FName& QuestStepId, const FName& QuestTaskId, int32 Increment);

	TArray<TObjectPtr<UETQuest>> GetQuests() const;

	UPROPERTY(BlueprintAssignable)
	FOnQuestStatusChanged_QuestManager OnQuestStatusChanged;

	virtual void InitializeComponent() override;

protected:

	UPROPERTY(SaveGame)
	TMap<FName, TObjectPtr<UETQuest>> Quests;

	UFUNCTION()
	void OnStatusChanged_Quest(UETQuest* Quest);

private:

	void RegisterInSubsystem();
};
