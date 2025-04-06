// Fill out your copyright notice in the Description page of Project Settings.


#include "ETQuestSubsystem.h"

#include "EterniaQuestSystemSettings.h"
#include "GameFramework/PlayerState.h"
#include "Components/ETQuestManagerComponent.h"
#include "Helpers/ETLogging.h"

UETQuestSubsystem* UETQuestSubsystem::GetCurrent(UObject* WorldContextObject) {
	UWorld* World = Cast<UWorld>(WorldContextObject);
	if (World == nullptr && WorldContextObject != nullptr) {
		World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	}

	if (World) {
		UGameInstance* GameInstance = World->GetGameInstance();
		if (GameInstance) {
			return GameInstance->GetSubsystem<UETQuestSubsystem>();
		}
	}

	return nullptr;
}

void UETQuestSubsystem::OnEvent(UETQuestEvent* QuestEvent) {
	for (TTuple<TObjectPtr<APlayerState>, TObjectPtr<UETQuestManagerComponent>> ListenerEntry : ManagerListeners) {
		ListenerEntry.Value->ReceiveQuestEvent(QuestEvent);
	}
}

void UETQuestSubsystem::RegisterManagerListener(UETQuestManagerComponent* Listener) {
	if (Listener == nullptr) return;

	UWorld* World = GEngine->GetWorldFromContextObject(Listener, EGetWorldErrorMode::LogAndReturnNull);
	if (World) {
		APlayerState* OwningPlayerState = Listener->GetOwner()->GetNetOwningPlayer()->GetPlayerController(World)->GetPlayerState<APlayerState>();
		if (ManagerListeners.Contains(OwningPlayerState)) {
			EQS_ULOGS_ERROR(TEXT("Only one registered Quest Manager per player is supported. Player %s tries to register more"),
			                *GetNameSafe(OwningPlayerState))
		}
		ManagerListeners.Add(OwningPlayerState, Listener);
	}
}

UETQuestManagerComponent* UETQuestSubsystem::GetManagerListener(APlayerState* PlayerState) {
	return ManagerListeners[PlayerState];
}

void UETQuestSubsystem::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);

	LoadSettings();
}

void UETQuestSubsystem::LoadSettings() {
	const UEterniaQuestSystemSettings* QuestSystemSettings = GetDefault<UEterniaQuestSystemSettings>();
	if (QuestSystemSettings) {
		QuestDataTable = QuestSystemSettings->QuestData.LoadSynchronous();
	}
}
