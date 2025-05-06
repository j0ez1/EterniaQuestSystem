// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EQuestStatus : uint8 {
	EQS_Accepted UMETA(DisplayName = "Accepted"),
	EQS_Completed UMETA(DisplayName = "Completed"),
	EQS_Failed UMETA(DisplayName = "Failed"),
	EQS_MAX UMETA(DisplayName = "Invalid")
};

UENUM(BlueprintType)
enum class EQuestStepStatus : uint8 {
	EQSS_Active UMETA(DisplayName = "Active"),
	EQSS_Completed UMETA(DisplayName = "Completed"),
	EQSS_Failed UMETA(DisplayName = "Failed"),
	EQSS_MAX UMETA(DisplayName = "Invalid")
};

UENUM(BlueprintType)
enum class EQuestTaskStatus : uint8 {
	EQTS_Active UMETA(DisplayName = "Active"),
	EQTS_Completed UMETA(DisplayName = "Completed"),
	EQTS_Failed UMETA(DisplayName = "Failed"),
	EQTS_Skipped UMETA(DisplayName = "Skipped"),
	EQTS_MAX UMETA(DisplayName = "Invalid")
};
