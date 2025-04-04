// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogQuest, Log, All);

#define EQS_ULOG_ERROR(fmt, ...) \
UE_LOG(LogQuest, Error, \
TEXT("[%s] %s:%i [%s]->[%s] %s"), \
TEXT("Context"), \
*FString(__FUNCTION__), __LINE__, \
*GetNameSafe(GetOwner()), *GetNameSafe(this), \
*FString::Printf(fmt, ##__VA_ARGS__) \
)

#define EQS_ULOGO_ERROR(fmt, ...) \
UE_LOG(LogQuest, Error, \
TEXT("[%s] %s:%i [%s]->[%s] %s"), \
TEXT("Context"), \
*FString(__FUNCTION__), __LINE__, \
*GetNameSafe(GetOuter()), *GetNameSafe(this), \
*FString::Printf(fmt, ##__VA_ARGS__) \
)

#define EQS_ULOGS_ERROR(fmt, ...) \
UE_LOG(LogQuest, Error, \
TEXT("[%s] %s:%i [%s] %s"), \
TEXT("Context"), \
*FString(__FUNCTION__), __LINE__, \
*StaticClass()->GetName(), \
*FString::Printf(fmt, ##__VA_ARGS__) \
)

#define EQS_ULOG_WARNING(fmt, ...) \
UE_LOG(LogQuest, Warning, \
TEXT("[%s] %s:%i [%s]->[%s] %s"), \
TEXT("Context"), \
*FString(__FUNCTION__), __LINE__, \
*GetNameSafe(GetOwner()), *GetNameSafe(this), \
*FString::Printf(fmt, ##__VA_ARGS__) \
)

#define EQS_ULOGO_WARNING(fmt, ...) \
UE_LOG(LogQuest, Warning, \
TEXT("[%s] %s:%i [%s]->[%s] %s"), \
TEXT("Context"), \
*FString(__FUNCTION__), __LINE__, \
*GetNameSafe(GetOuter()), *GetNameSafe(this), \
*FString::Printf(fmt, ##__VA_ARGS__) \
)

#define EQS_ULOGS_WARNING(fmt, ...) \
UE_LOG(LogQuest, Warning, \
TEXT("[%s] %s:%i [%s] %s"), \
TEXT("Context"), \
*FString(__FUNCTION__), __LINE__, \
*StaticClass()->GetName(), \
*FString::Printf(fmt, ##__VA_ARGS__) \
)

#define EQS_ULOG_DISPlAY(fmt, ...) \
UE_LOG(LogQuest, Display, \
TEXT("[%s] %s:%i [%s]->[%s] %s"), \
TEXT("Context"), \
*FString(__FUNCTION__), __LINE__, \
*GetNameSafe(GetOwner()), *GetNameSafe(this), \
*FString::Printf(fmt, ##__VA_ARGS__) \
)

#define EQS_ULOGO_DISPlAY(fmt, ...) \
UE_LOG(LogQuest, Display, \
TEXT("[%s] %s:%i [%s]->[%s] %s"), \
TEXT("Context"), \
*FString(__FUNCTION__), __LINE__, \
*GetNameSafe(GetOuter()), *GetNameSafe(this), \
*FString::Printf(fmt, ##__VA_ARGS__) \
)

#define EQS_ULOGS_DISPlAY(fmt, ...) \
UE_LOG(LogQuest, Display, \
TEXT("[%s] %s:%i [%s] %s"), \
TEXT("Context"), \
*FString(__FUNCTION__), __LINE__, \
*StaticClass()->GetName(), \
*FString::Printf(fmt, ##__VA_ARGS__) \
)

#define EQS_ULOG(fmt, ...) \
UE_LOG(LogQuest, Log, \
TEXT("[%s] %s:%i [%s]->[%s] %s"), \
TEXT("Context"), \
*FString(__FUNCTION__), __LINE__, \
*GetNameSafe(GetOwner()), *GetNameSafe(this), \
*FString::Printf(fmt, ##__VA_ARGS__) \
)

#define EQS_ULOGO(fmt, ...) \
UE_LOG(LogQuest, Log, \
TEXT("[%s] %s:%i [%s]->[%s] %s"), \
TEXT("Context"), \
*FString(__FUNCTION__), __LINE__, \
*GetNameSafe(GetOuter()), *GetNameSafe(this), \
*FString::Printf(fmt, ##__VA_ARGS__) \
)

#define EQS_ULOGS(fmt, ...) \
UE_LOG(LogQuest, Log, \
TEXT("[%s] %s:%i [%s] %s"), \
TEXT("Context"), \
*FString(__FUNCTION__), __LINE__, \
*StaticClass()->GetName(), \
*FString::Printf(fmt, ##__VA_ARGS__) \
)

#define EQS_ULOG_VERBOSE(fmt, ...) \
UE_LOG(LogQuest, Verbose, \
TEXT("[%s] %s:%i [%s]->[%s] %s"), \
TEXT("Context"), \
*FString(__FUNCTION__), __LINE__, \
*GetNameSafe(GetOwner()), *GetNameSafe(this), \
*FString::Printf(fmt, ##__VA_ARGS__) \
)

#define EQS_ULOGO_VERBOSE(fmt, ...) \
UE_LOG(LogQuest, Verbose, \
TEXT("[%s] %s:%i [%s]->[%s] %s"), \
TEXT("Context"), \
*FString(__FUNCTION__), __LINE__, \
*GetNameSafe(GetOuter()), *GetNameSafe(this), \
*FString::Printf(fmt, ##__VA_ARGS__) \
)

#define EQS_ULOGS_VERBOSE(fmt, ...) \
UE_LOG(LogQuest, Verbose, \
TEXT("[%s] %s:%i [%s] %s"), \
TEXT("Context"), \
*FString(__FUNCTION__), __LINE__, \
*StaticClass()->GetName(), \
*FString::Printf(fmt, ##__VA_ARGS__) \
)