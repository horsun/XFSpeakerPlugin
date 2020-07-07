// Fill out your copyright notice in the Description page of Project Settings.


#include "XFSpeakerProcess.h"

void UXFSpeakerProcess::SpawnWaveFile(FString literalString, FString waveName)
{
	TSharedPtr<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();

	/** 设置请求头 */
	FDateTime  now = FDateTime::UtcNow();
	FString curTime = FString::FromInt(now.ToUnixTimestamp());
	FString param = TEXT("{\"auf\":\"" + Auf + "\",\"aue\":\"" + Aue + "\",\"voice_name\":\"" + Voice_name + "\",\"speed\":\"" + Speed + "\",\"volume\":\"" + Volume + "\",\"pitch\":\"" + Pitch + "\",\"engine_type\":\"" + Engine_type + "\",\"text_type\":\"" + Text_type + "\"}");


	//TArray<UTF8CHAR> tArray = StringToArray<UTF8CHAR>(*param, param.Len() + 1);
	/*TCHAR* pSendData = param.GetCharArray().GetData();
	uint8* dst = (uint8*)TCHAR_TO_UTF8(pSendData);*/

	//1.转换格式到Base64//先转成TArray<uint8>，再转成FBase64	
	TArray<uint8> content;
	std::string _s(TCHAR_TO_UTF8(*param));
	content.Append((unsigned char *)_s.data(), _s.size());
	FString xparam = FBase64::Encode(content);

	FString hashString;
	hashString.Append(Api_key);// + curTime + xparam;
	hashString.Append(curTime);// + curTime + xparam;
	hashString.Append(xparam);// + curTime + xparam;
	FString checkSum = FMD5::HashAnsiString(*hashString);

	HttpRequest->SetHeader("Content-Type", "application/x-www-form-urlencoded; charset=utf-8");
	HttpRequest->SetHeader("X-Param", xparam);
	HttpRequest->SetHeader("X-CurTime", curTime);
	HttpRequest->SetHeader("X-CheckSum", checkSum);
	HttpRequest->SetHeader("X-Appid", Appid);
	HttpRequest->SetHeader("X-FileName", waveName);

	/** 设置请求的URL */
	HttpRequest->SetURL(Webtts_url);
	/** 设置请求方式为POST */
	HttpRequest->SetVerb("POST");
	///** 设置上传的JSON数据 */

	//FString bodyText = TEXT("测试中文是否可以");
	FString body = "text=\"" + literalString + "\"";
	HttpRequest->SetContentAsString(body);

	/** 设置请求成功后的响应事件 */
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UXFSpeakerProcess::CompletedCallback);
	/** 处理请求 */
	HttpRequest->ProcessRequest();
}

void UXFSpeakerProcess::CompletedCallback(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
{
	int i = 0;

	FString ResponseCode = HttpResponse->GetContentAsString();

	GLog->Logf(TEXT("SpeechActor Result:%s"), *ResponseCode);

	/** 判断服务器返回状态 */
	if (!EHttpResponseCodes::IsOk(HttpResponse->GetResponseCode()))
	{
		/** 如果服务器未返回成功则返回 */
		return;
	}

	// 获取响应header
	if (HttpResponse->GetContentType().Equals("audio/mpeg"))
	{
		FString FileName = HttpRequest->GetHeader("X-FileName");
		FFileHelper::SaveArrayToFile(HttpResponse->GetContent(), *FString::Printf(TEXT("%s%s"), *SaveDir, *FileName));
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("语音转换成功"));
		onCallBack.ExecuteIfBound(FileName);
	}
	else
	{
		onCallBack.ExecuteIfBound("");
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("语音转换失败"));
	}
}

void UXFSpeakerProcess::initProperty(FXFConfig config)
{
	Voice_name = config.Voice_name;
	Speed = config.Speed;
	Api_key = config.Api_key;
	Appid = config.Appid;
	Volume = config.Volume;
}
