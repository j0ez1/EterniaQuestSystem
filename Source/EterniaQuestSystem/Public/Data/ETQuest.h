// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ETQuest.generated.h"

class UETQuestStep;

UENUM(BlueprintType)
enum EQuestStatus : uint8 {
	EQS_NotStarted UMETA(DisplayName = "Not Started"),
	EQS_Accepted UMETA(DisplayName = "Accepted"),
	EQS_Completed UMETA(DisplayName = "Completed"),
	EQS_Failed UMETA(DisplayName = "Failed"),
	EQS_MAX UMETA(DisplayName = "Invalid")
};

/**
 * 
 */
UCLASS()
class ETERNIAQUESTSYSTEM_API UETQuest : public UObject {
	GENERATED_BODY()

public:

	void SetIsTracked(bool bInIsTracked);

	bool CanChangeStatus(EQuestStatus InStatus);

	FORCEINLINE EQuestStatus GetStatus() const { return Status; }

	FORCEINLINE bool SetStatus(EQuestStatus InStatus);

	FORCEINLINE void SetDefinitionId(const FName& InDefinitionId) { DefinitionId = InDefinitionId; }

	FORCEINLINE FName GetDefinitionId() const { return DefinitionId; }

protected:

	UPROPERTY()
	TArray<TObjectPtr<UETQuestStep>> Steps;

	UPROPERTY()
	FName DefinitionId;

	UPROPERTY()
	TEnumAsByte<EQuestStatus> Status = EQuestStatus::EQS_NotStarted;

	UPROPERTY()
	bool bIsTracked;
};
