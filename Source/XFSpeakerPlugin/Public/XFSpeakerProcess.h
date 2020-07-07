// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "string"
#include "Http.h"
#include "XFStruct.h"
#include "UObject/NoExportTypes.h"
#include "XFSpeakerProcess.generated.h"

/**
 * 
 */
DECLARE_DELEGATE_OneParam(FProcessCallBack,FString);

UCLASS()
class XFSPEAKERPLUGIN_API UXFSpeakerProcess : public UObject
{
	GENERATED_BODY()

private:
	// �ϳ�webapi�ӿڵ�ַ
	FString Webtts_url = "http://api.xfyun.cn/v1/service/v1/tts";
	FString Text = "TextString";
	FString Aue = "raw";
	FString Auf = "audio/L16;rate=16000";
	FString Pitch = "50";
	FString Engine_type = "intp65";
	FString Text_type = "text";
public:
	FString Voice_name = "xiaoyan";
	FString Speed = "50";
	FString Volume = "50";
	FString Appid = ""; /*your appid*/
	FString Api_key = "";/*your api key*/
	FString SaveDir = *FPaths::ProjectSavedDir() + FString("/audio/");

public:
	void SpawnWaveFile(FString literalString, FString waveName);
	void CompletedCallback(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded);

	void initProperty(FXFConfig config);
	//UPROPERTY(BlueprintAssignable, Category = "Event")
	FProcessCallBack onCallBack;
	
	
};
