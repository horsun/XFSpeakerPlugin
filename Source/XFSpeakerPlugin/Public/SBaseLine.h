// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XFPluginLib.h"
#include "SMainWidget.h"
#include "TimerManager.h"
#include "XFSpeakerProcess.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class XFSPEAKERPLUGIN_API SBaseLine : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBaseLine)
	{}
	SLATE_END_ARGS()


	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, SMainWidget *SParentBox);

	SMainWidget *SMainParentBox;

	FReply OnClickDelete();
	FReply OnClickPreview();

	/**define Slate ui**/
	TSharedPtr<SButton> SDeleteButton ;
	TSharedPtr<SButton> SPreivewButton ;
	TSharedPtr<SEditableTextBox> SFileName;
	TSharedPtr<SEditableTextBox> SWaveString;
	SVerticalBox *localParent;

	USoundWave *SpeachWaveObj;

	FString filename;
	FString fWaveString;

	UXFSpeakerProcess *cWaveCreater;

	FTimerHandle FSlateTimer;

public:
	void SpawnWave();
	void SpawnCallBack(FString callbackname);
};
