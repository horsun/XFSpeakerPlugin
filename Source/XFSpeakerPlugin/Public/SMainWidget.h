// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "XFPluginLib.h"
#include "XFSpeakerProcess.h"
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
	TSharedPtr<SVerticalBox> SContainer;





	/** click event **/
	FReply OnClickCreate();
	FReply OnClickDeleteAll();
	FReply OnClickOpenFloder();
	FReply OnClickSpawnWave();
};
