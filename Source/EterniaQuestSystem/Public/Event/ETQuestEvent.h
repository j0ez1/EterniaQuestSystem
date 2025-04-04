// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ETQuestEvent.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName="[Eternia] Quest Event")
class ETERNIAQUESTSYSTEM_API UETQuestEvent : public UObject {
	GENERATED_BODY()

public:

	FORCEINLINE AActor* GetReporter() const { return Reporter; }

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn, AllowPrivateAccess=true))
	AActor* Reporter;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn, AllowPrivateAccess=true))
	AActor* Instigator;
};
