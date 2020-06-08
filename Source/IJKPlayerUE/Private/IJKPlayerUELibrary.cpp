// Fill out your copyright notice in the Description page of Project Settings.


#include "IJKPlayerUELibrary.h"
#include "Json.h"

#if PLATFORM_ANDROID
	#include "Android/AndroidApplication.h"
	#if USE_ANDROID_JNI
		#include "Android/AndroidJNI.h"
	#endif
#endif

void UIJKPlayerUELibrary::PlayMovieForAndroid(const FString& url)
{
#if PLATFORM_ANDROID && USE_ANDROID_JNI
	if (url.Len() == 0)
	{
		return;
	}
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

FString UIJKPlayerUELibrary::MakeMovieURL(const FString& Title, const TArray<FMovieURL>& URLArray)
{
	TSharedPtr<FJsonObject> url_object = MakeShareable(new FJsonObject);
	url_object->SetStringField("Title", Title);
	TArray<TSharedPtr<FJsonValue>> urlArray;

	for (int i = 0; i < URLArray.Num(); i++)
	{
		TSharedPtr<FJsonObject> url = MakeShareable(new FJsonObject);
		url->SetStringField("name", URLArray[i].Name);
		url->SetStringField("url", URLArray[i].URL);
		urlArray.Add(MakeShareable(new FJsonValueObject(url)));
	}
	url_object->SetArrayField("array", urlArray);
	FString strGet;
	TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<>::Create(&strGet);
	FJsonSerializer::Serialize(url_object.ToSharedRef(), Writer);
	Writer->Close();
	return strGet;
}