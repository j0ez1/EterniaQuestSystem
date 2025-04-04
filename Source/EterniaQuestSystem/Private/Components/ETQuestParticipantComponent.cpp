// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ETQuestParticipantComponent.h"


// Sets default values for this component's properties
UETQuestParticipantComponent::UETQuestParticipantComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UETQuestParticipantComponent::ReceiveQuestUpdate(const FQuestUpdate& QuestUpdate) {
	
}


// Called when the game starts
void UETQuestParticipantComponent::BeginPlay() {
	Super::BeginPlay();

	// ...
	
}