// Fill out your copyright notice in the Description page of Project Settings.


#include "SBaseLine.h"

#include "AssetRegistryModule.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SBaseLine::Construct(const FArguments& InArgs, SMainWidget *SParentBox)
{
	//UE_LOG(LogTemp, Log, TEXT("total slate count %d"), test);
	SMainParentBox = SParentBox;
	cWaveCreater = NewObject<UXFSpeakerProcess>();
	cWaveCreater->initProperty(SMainParentBox->GetConfig());
	ChildSlot
		[
			SNew(SHorizontalBox)
			//SNew(SPanel)
			+ SHorizontalBox::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).FillWidth(1)
				.Padding(10.f, 10.f, 10.f, 0.f)
				[
					SAssignNew(SWaveString,SEditableTextBox)
					.HintText(FText::FromString("Editor your speech"))
				]
			+ SHorizontalBox::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).FillWidth(1)
				.Padding(10.f, 10.f, 10.f, 0.f)
				[
					SAssignNew(SFileName, SEditableTextBox)
					.HintText(FText::FromString("SoundName"))
				]
			+ SHorizontalBox::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).FillWidth(1)
				.Padding(10.f, 10.f, 10.f, 0.f)
				[
					SAssignNew(SDeleteButton,SButton)
					.Text(FText::FromString("X")).HAlign(HAlign_Center).VAlign(VAlign_Center)
					.OnClicked_Raw(this, &SBaseLine::OnClickDelete)
					
				]
			+ SHorizontalBox::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).FillWidth(1)
				.Padding(10.f, 10.f, 10.f, 0.f)
				[
					SAssignNew(SPreivewButton, SButton)
					.Text(FText::FromString("Preview")).HAlign(HAlign_Center).VAlign(VAlign_Center)
					.OnClicked_Raw(this,&SBaseLine::OnClickPreview)
					.IsEnabled(false)
				]
			+ SHorizontalBox::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill).FillWidth(1)
				.Padding(10.f, 10.f, 10.f, 0.f)
				[
					SAssignNew(SSaveAsAsset, SButton)
					.Text(FText::FromString("SaveToEditor")).HAlign(HAlign_Center).VAlign(VAlign_Center)
				.OnClicked_Raw(this, &SBaseLine::ONClickSaveAsset)
				.IsEnabled(false)
				]
			
		];
}
FReply SBaseLine::OnClickDelete()
{
	
	return FReply::Handled();
}
FReply SBaseLine::OnClickPreview()
{
	//Play Preview SoundWave
	UGameplayStatics::SpawnSound2D(GEngine->GetWorldContexts()[0].World(),SpeachWaveObj);
	
	return FReply::Handled();
}

FReply SBaseLine::ONClickSaveAsset()
{
	/* get full path */
	FString InFilePath = cWaveCreater->SaveDir;
	FString localFileName = SFileName->GetText().ToString();
	InFilePath.Append(filename);

	/* Asset init */
	FString AssetPath = FString("/Game/test/");
	FString PackagePath = FString("/Game/test");
	UPackage *Package = CreatePackage(nullptr, *PackagePath);

	/* sound wave init*/
	USoundWave* sw = NewObject<USoundWave>(Package, USoundWave::StaticClass(), *localFileName, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone);

		 
	/* config inited wave file */
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
		}
	}
	FAssetRegistryModule::AssetCreated(sw);

	sw->MarkPackageDirty();

	FString FilePath = FString::Printf(TEXT("%s%s%s"), *AssetPath, *localFileName, *FPackageName::GetAssetPackageExtension());

	bool success = UPackage::SavePackage(Package, sw, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *FilePath);

	return FReply::Handled();
}
void SBaseLine::SpawnWave()
{	
	//Spawn .wav file
	filename = SFileName->GetText().ToString();
	fWaveString = SWaveString->GetText().ToString();
	cWaveCreater->initProperty(SMainParentBox->GetConfig());
	if (cWaveCreater!=nullptr&&filename.Len()!=0&& fWaveString.Len()!=0)
	{
		filename.Append(".wav");
		cWaveCreater->SpawnWaveFile(fWaveString, filename);
		cWaveCreater->onCallBack.BindRaw(this, &SBaseLine::SpawnCallBack);
		//GetWorldTimerManager().SetTimer(FSlateTimer, this, &SBaseLine::SpawnCallBack, true, 5.0f);
	}
}
void SBaseLine::SpawnCallBack(FString callbackname)
{
	// create SoundWave with .wav file
	UE_LOG(LogTemp, Warning, TEXT("Local String %s CallBack String %s"), *filename, *callbackname);
	if (callbackname==filename)
	{
		FString filePath = cWaveCreater->SaveDir;
		filePath.Append(filename);
		SpeachWaveObj = UXFPluginLib::GetSoundWaveFromFile(filePath);
		SPreivewButton->SetEnabled(true);
		SSaveAsAsset->SetEnabled(true);
	}
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
