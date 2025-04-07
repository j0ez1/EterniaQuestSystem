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

void UETQuestSubsystem::RegisterManagerListener(UETQuestManagerComponent* Listener) {
	if (Listener == nullptr) return;

	UWorld* World = GEngine->GetWorldFromContextObject(Listener, EGetWorldErrorMode::LogAndReturnNull);
	if (!World) return;
	
	AActor* Owner = Listener->GetOwner();
	APlayerState* OwningPlayerState = nullptr;
	if (Owner->IsA(APlayerState::StaticClass())) {
		OwningPlayerState = Cast<APlayerState>(Owner);
	} else {
		UPlayer* NetOwningPlayer = Owner->GetNetOwningPlayer();
		APlayerController* PlayerController = NetOwningPlayer->GetPlayerController(World);
		if (PlayerController) {
			OwningPlayerState = PlayerController->GetPlayerState<APlayerState>();
		}
	}
	if (!OwningPlayerState) return;
	
	if (ManagerListeners.Contains(OwningPlayerState)) {
		EQS_ULOGS_ERROR(TEXT("Only one registered Quest Manager per player is supported. Player [ID: %s] tries to register more"),
		                *FString::FromInt(OwningPlayerState->GetPlayerId()))
		return;
	}
	ManagerListeners.Add(OwningPlayerState, Listener);
}

UETQuestManagerComponent* UETQuestSubsystem::GetManagerListener(APlayerState* PlayerState) {
	TObjectPtr<UETQuestManagerComponent>* Result = ManagerListeners.Find(PlayerState);
	return Result ? *Result : nullptr;
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
