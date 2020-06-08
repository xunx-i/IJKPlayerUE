// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "IJKPlayerUELibrary.generated.h"

USTRUCT(BlueprintType)
struct FMovieURL
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = AndroidFunctionLibrary)
		FString Name;
	UPROPERTY(BlueprintReadWrite, Category = AndroidFunctionLibrary)
		FString URL;
};

UCLASS()
class IJKPLAYERUE_API UIJKPlayerUELibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "IJKPlayerUELibrary")
		static void PlayMovieForAndroid(const FString& url);

	UFUNCTION(BlueprintCallable, Category = "IJKPlayerUELibrary")
		static FString MakeMovieURL(const FString& Title, const TArray<FMovieURL>& URLArray);
	
};
