// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GenericPlatform/GenericPlatformProcess.h"
#include "Sound/SoundBase.h"
#include "Sound/SoundWave.h"
#include "Misc/FileHelper.h"
#include "XFPluginLib.generated.h"

/**
 * 
 */
UCLASS()
class XFSPEAKERPLUGIN_API UXFPluginLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	static void OpenFloder() {
		FString FilePath = FPaths::ConvertRelativePathToFull(*FPaths::ProjectSavedDir()) + FString("audio");
		FPlatformProcess::ExploreFolder(*FilePath);
	};

	static USoundWave* GetSoundWaveFromFile(const FString& InFilePath)
	{
		USoundWave* sw = NewObject<USoundWave>(USoundWave::StaticClass());
		if (!sw)
			return nullptr;
		TArray <uint8> rawFile;
		FFileHelper::LoadFileToArray(rawFile, InFilePath.GetCharArray().GetData());
		FWaveModInfo WaveInfo;

		if (WaveInfo.ReadWaveInfo(rawFile.GetData(), rawFile.Num()))
		{
			int32 DurationDiv = *WaveInfo.pChannels * *WaveInfo.pBitsPerSample * *WaveInfo.pSamplesPerSec;
			if (DurationDiv)
			{
				sw->SoundGroup = ESoundGroup::SOUNDGROUP_Default;
				sw->NumChannels = *WaveInfo.pChannels;
				sw->Duration = *WaveInfo.pWaveDataSize * 8.0f / DurationDiv; ;
				sw->RawPCMDataSize = WaveInfo.SampleDataSize;
				sw->SetSampleRate(*WaveInfo.pSamplesPerSec);


				sw->InvalidateCompressedData();
				sw->RawData.Lock(LOCK_READ_WRITE);
				FMemory::Memcpy(sw->RawData.Realloc(rawFile.Num()), rawFile.GetData(), rawFile.Num());
				sw->RawData.Unlock();


				sw->RawPCMDataSize = WaveInfo.SampleDataSize;
				sw->RawPCMData = (uint8 *)FMemory::Malloc(sw->RawPCMDataSize);
				FMemory::Memmove(sw->RawPCMData, rawFile.GetData(), rawFile.Num());
				return sw;
			}
			else
			{
				sw->Duration = 0.0f;
				return sw;
			}
		}
		else {
			return nullptr;
		}
	}
	
};
