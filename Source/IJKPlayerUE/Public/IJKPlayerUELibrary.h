// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Async/AsyncWork.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IJKPlayerUELibrary.generated.h"



class FMakeURLTask : public FNonAbandonableTask
{
public:

	friend class FAsyncTask<FMakeURLTask>;

	FMakeURLTask(const FString& title, const TMap<FString,FString>& urlMap)
		: Title(title),
		URLMap(urlMap)
	{
	}
	void DoWork();

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FMakeURLTask, STATGROUP_ThreadPoolAsyncTasks);
	}

private:
	FString Title;
	TMap<FString,FString> URLMap;
};
typedef FAutoDeleteAsyncTask<FMakeURLTask> MakeURLTask;


DECLARE_DYNAMIC_DELEGATE_OneParam(FMakeURLTaskCompleted, const FString&, URL);

UCLASS()
class IJKPLAYERUE_API UIJKPlayerUELibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "IJKPlayerUELibrary")
		static void PlayMovieForAndroid(const FString& url);

	UFUNCTION(BlueprintCallable, Category = "IJKPlayerUELibrary")
		static void MakeMovieURL(const FMakeURLTaskCompleted& CompletedEvent, const FString& Title, const TMap<FString,FString>& UrlMap);

	static void OnCompleted(const FString& url);
};
