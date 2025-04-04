// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ETQuestStep.generated.h"

UENUM(BlueprintType)
enum EQuestStepStatus : uint8 {
	EQSS_Active UMETA(DisplayName = "Active"),
	EQSS_Completed UMETA(DisplayName = "Completed"),
	EQSS_Failed UMETA(DisplayName = "Failed"),
	EQSS_Ignored UMETA(DisplayName = "Ignored"),
	EQSS_MAX UMETA(DisplayName = "Invalid")
};

/**
 * 
 */
UCLASS()
class ETERNIAQUESTSYSTEM_API UETQuestStep : public UObject {
	GENERATED_BODY()
};
