// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetGuidLibrary.h"
#include "StructUtils/InstancedStruct.h"
#include "ETQuestDefinition.generated.h"

enum EQuestStepStatus : uint8;
class UKismetGuidLibrary;

USTRUCT(BlueprintType)
struct FETQuestTaskDefinition {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Identifier = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Title = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bMandatory = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 TargetNumber = -1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 TimeLimit = -1;
};

USTRUCT(BlueprintType, DisplayName="(Abstract) Step Decorator")
struct FETQuestStepDecorator {
	GENERATED_BODY()

};

USTRUCT(DisplayName="Requires Step Completion")
struct FETQuestStepDecorator_RequiresStepCompletion : public FETQuestStepDecorator {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName StepId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bActivateOnStepSuccess;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bActivateOnStepFailure;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly)
	// bool bCompleteRequiredStepOnActivation = true;
};

USTRUCT(DisplayName="Requires Quest Completion")
struct FETQuestStepDecorator_RequiresQuestCompletion : public FETQuestStepDecorator {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName QuestId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bActivateOnQuestSuccess;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bActivateOnQuestFailure;
};

USTRUCT(DisplayName="Complete On Step Completion")
struct FETQuestStepDecorator_CompleteOnStepCompletion : public FETQuestStepDecorator {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName StepId;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCompleteOnStepSuccess = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCompleteOnStepFailure = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EQuestStepStatus> StatusToSet;
};

USTRUCT(DisplayName="Complete On Quest Completion")
struct FETQuestStepDecorator_CompleteOnQuestCompletion : public FETQuestStepDecorator {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName QuestId;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCompleteOnQuestSuccess = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCompleteOnQuestFailure = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EQuestStepStatus> StatusToSet;
};

USTRUCT(BlueprintType)
struct FETQuestStepDefinition {
	GENERATED_BODY()

	FETQuestStepDefinition() {}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Identifier = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Title = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText SuccessDescription = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText FailureDescription = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialInterface* Image = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bParallelTasks = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bMarkQuestAsFailedOnStepFailure = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FETQuestTaskDefinition> Tasks;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BaseStruct="ETQuestStepDecorator"))
	TArray<FInstancedStruct> Decorators;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGuid GUID = UKismetGuidLibrary::NewGuid();
};

USTRUCT(BlueprintType, DisplayName="(Abstract) Quest Decorator")
struct FETQuestDecorator {
	GENERATED_BODY()

};

USTRUCT(DisplayName="Requires Quest Completion")
struct FETQuestDecorator_RequiresQuestCompletion : public FETQuestDecorator {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName QuestId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bUnlockOnQuestSuccess;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bUnlockOnQuestFailure;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bAutoActivateOnUnlock;
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct FETQuestDefinition : public FTableRowBase {
	GENERATED_BODY()

	FETQuestDefinition() {}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Identifier = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Title = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText SuccessDescription = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText FailureDescription = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialInterface* Image = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bHidden = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = bHidden, EditConditionHides))
	bool bUnhideOnCompletion = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FETQuestStepDefinition> Steps = TArray<FETQuestStepDefinition>();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(BaseStruct="ETQuestDecorator"))
	TArray<FInstancedStruct> Decorators = TArray<FInstancedStruct>();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGuid GUID = UKismetGuidLibrary::NewGuid();

};
