// Fill out your copyright notice in the Description page of Project Settings.


#include "IJKPlayerUELibrary.h"
#include "Json.h"

#if PLATFORM_ANDROID
	#include "Android/AndroidApplication.h"
	#if USE_ANDROID_JNI
		#include "Android/AndroidJNI.h"
	#endif
#endif

FMakeURLTaskCompleted TaskCompleted;

void UIJKPlayerUELibrary::PlayMovieForAndroid(const FString& url)
{
	if (url.Len() == 0)
	{
		return;
	}
#if PLATFORM_ANDROID && USE_ANDROID_JNI
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	if (Env)
	{
		static jmethodID UiLayerMethod = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_PlayMovie", "(Ljava/lang/String;)V", false);
		jstring urlJava = Env->NewStringUTF(TCHAR_TO_UTF8(*url));
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, UiLayerMethod, urlJava);
		Env->DeleteLocalRef(urlJava);
	}
#endif
}

void UIJKPlayerUELibrary::MakeMovieURL(const FMakeURLTaskCompleted& CompletedEvent, const FString& Title, const TMap<FString,FString>& UrlMap)
{
	TaskCompleted = CompletedEvent;
	MakeURLTask* task = new MakeURLTask(Title, UrlMap);
	task->StartBackgroundTask();
}

void UIJKPlayerUELibrary::OnCompleted(const FString& url)
{
	TaskCompleted.ExecuteIfBound(url);
}

void FMakeURLTask::DoWork()
{
	TSharedPtr<FJsonObject> url_object = MakeShareable(new FJsonObject);
	url_object->SetStringField("Title", Title);
	TArray<TSharedPtr<FJsonValue>> urlArray;

	for (auto it :URLMap)
	{
		TSharedPtr<FJsonObject> url = MakeShareable(new FJsonObject);
		url->SetStringField("name", *it.Key);
		url->SetStringField("url", *it.Value);
		urlArray.Add(MakeShareable(new FJsonValueObject(url)));
	}
	
	url_object->SetArrayField("array", urlArray);
	FString strGet;
	TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<>::Create(&strGet);
	FJsonSerializer::Serialize(url_object.ToSharedRef(), Writer);
	Writer->Close();

	UIJKPlayerUELibrary::OnCompleted(strGet);
}
