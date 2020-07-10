// Fill out your copyright notice in the Description page of Project Settings.


#include "SBaseLine.h"
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
	UXFPluginLib::SaveSoundAssetToContent(SpeachWaveObj);
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
	}
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
