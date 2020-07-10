// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XFPluginLib.h"
#include "XFSpeakerProcess.h"
#include "Widgets/SCanvas.h"
#include "XFStruct.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Input/STextComboBox.h"
#include "Widgets/Input/SSpinBox.h"
#include "Widgets/SCompoundWidget.h"

/**
 *
 */

class XFSPEAKERPLUGIN_API SMainWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMainWidget)
	{}
	SLATE_END_ARGS()

		/** Constructs this widget with InArgs */
		void Construct(const FArguments& InArgs);
	/** Assign Swidget  **/
	TSharedPtr<SButton> SCreateLine;
	TSharedPtr<SButton> SDeleteAll;
	TSharedPtr<SButton> SOpenFloder;
	TSharedPtr<SButton> SSpawnWave;
	TSharedPtr<SButton> SChooseDir;
	TSharedPtr<SVerticalBox> SContainer;


	TSharedPtr<STextBlock> SDirText;
	FString SavedDir = "/Saved/audio/";


	TSharedPtr<SSpinBox<int>> SSpeedText;
	TSharedPtr<SSpinBox<int>> SVolumeText;
	TSharedPtr<SSpinBox<int>> SPitchText;

	typedef TSharedPtr <FString>  VoiceNameSource;
	TArray<VoiceNameSource> VNSourceList;
	VoiceNameSource VNSelectIndex;
	TSharedPtr<SComboBox<VoiceNameSource>> SVoiceNameText;
	
	//TSharedPtr<FString> VoiceNameSource;
	//= { "xiaoyan","aisjiuxu","aisxping" };

	/** click event **/
	FReply OnClickCreate();
	FReply OnClickDeleteAll();
	FReply OnClickOpenFloder();
	FReply OnClickSpawnWave();
	FReply OnClickOpenChooseDirWindow();


	/** Generate combobox swidget function **/
	TSharedRef <SWidget> MakeWidgetForVNSource(VoiceNameSource InOption);
	FText GetCurrentVNLabel() const;
	void OnSelectedVNChanged(VoiceNameSource NewValue, ESelectInfo::Type)
	{
		VNSelectIndex = NewValue;
	}

public:
	FXFConfig GetConfig();
};
