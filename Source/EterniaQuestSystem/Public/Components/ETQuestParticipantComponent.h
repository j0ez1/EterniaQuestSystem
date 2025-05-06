// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ETQuestParticipantComponent.generated.h"

enum class EQuestTaskStatus : uint8;
enum class EQuestStepStatus : uint8;
enum class EQuestStatus : uint8;

USTRUCT(BlueprintType)
struct FQuestUpdate {
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPlayer* Player;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName QuestId;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestStatus QuestStatus;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName QuestStepId;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestStepStatus QuestStepStatus;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName QuestTaskId;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EQuestTaskStatus QuestTaskStatus;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestUpdated, const FQuestUpdate&, QuestUpdate);

UCLASS(ClassGroup=(Custom), DisplayName="Quest Participant", Category="Eternia", meta=(BlueprintSpawnableComponent))
class ETERNIAQUESTSYSTEM_API UETQuestParticipantComponent : public UActorComponent {
	GENERATED_BODY()

public:

	UETQuestParticipantComponent();

	void ReceiveQuestUpdate(const FQuestUpdate& QuestUpdate);

	UPROPERTY(BlueprintAssignable)
	FOnQuestUpdated OnQuestUpdated;

protected:

	virtual void BeginPlay() override;
};
