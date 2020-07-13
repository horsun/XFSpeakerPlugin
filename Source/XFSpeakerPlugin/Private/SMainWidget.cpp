// Fill out your copyright notice in the Description page of Project Settings.


#include "SMainWidget.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMainWidget::Construct(const FArguments& InArgs)
{
	VNSourceList.Add(MakeShareable(new FString("xiaoyan")));
	VNSourceList.Add(MakeShareable(new FString("aisjiuxu")));
	VNSourceList.Add(MakeShareable(new FString("aisxping")));
	VNSourceList.Add(MakeShareable(new FString("aisjinger")));
	VNSourceList.Add(MakeShareable(new FString("aisbabyxu")));
	VNSelectIndex = MakeShareable(new FString("xiaoyan"));

	ChildSlot
		[
		SNew(SHorizontalBox)
		 + SHorizontalBox::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill)
			[
				SNew(SCanvas)
				+ SCanvas::Slot().Size(FVector2D(800.f, 600.f)).Position(FVector2D(0.f,0.f))
				[
					SAssignNew(SContainer, SVerticalBox)
					+ SVerticalBox::Slot().HAlign(HAlign_Left).VAlign(VAlign_Top)
					[
						SNew(SBaseLine,this)
					]
				]
			]
		+ SHorizontalBox::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill)
			[
			
				
				SNew(SCanvas)
				+ SCanvas::Slot().Position(FVector2D(200.f, 50.f)).Size(FVector2D(100.0f, 30.0f))
				[
					SAssignNew(SDirText, STextBlock).Text(FText::FromString(SavedDir)).ToolTipText(FText::FromString(SavedDir))
				]
				+ SCanvas::Slot().Position(FVector2D(150.f, 100.f)).Size(FVector2D(100.0f, 30.0f))
				[
					SAssignNew(SCreateLine, SButton)
					.Text(FText::FromString("CreateNewRaw")).HAlign(HAlign_Center).VAlign(VAlign_Center)
					.OnClicked_Raw(this, &SMainWidget::OnClickCreate)
				]
				+ SCanvas::Slot().Position(FVector2D(150.f, 150.0f)).Size(FVector2D(100.0f, 30.0f))
				[
					SAssignNew(SDeleteAll, SButton)
					.Text(FText::FromString("DeleteAll")).HAlign(HAlign_Center).VAlign(VAlign_Center)
					.OnClicked_Raw(this, &SMainWidget::OnClickDeleteAll)
				]
				+ SCanvas::Slot().Position(FVector2D(150.f, 200.0f)).Size(FVector2D(100.0f, 30.0f))
				[
					SAssignNew(SSpawnWave, SButton)
					.Text(FText::FromString("SpawnWave")).HAlign(HAlign_Center).VAlign(VAlign_Center)
					.OnClicked_Raw(this, &SMainWidget::OnClickSpawnWave)
				]
				+ SCanvas::Slot().Position(FVector2D(150.f, 250.0f)).Size(FVector2D(100.0f, 30.0f))
				[
					SAssignNew(SOpenFloder, SButton)
					.Text(FText::FromString("OpenSavedDIR")).HAlign(HAlign_Center).VAlign(VAlign_Center)
					.OnClicked_Raw(this, &SMainWidget::OnClickOpenFloder).ToolTipText(FText::FromString("Open the DIR where  .wav files saved"))
				]
				+ SCanvas::Slot().Position(FVector2D(300.f, 250.0f)).Size(FVector2D(100.0f, 30.0f))
					[
						SAssignNew(SChooseDir, SButton)
						.Text(FText::FromString("ModifySavedDIR")).HAlign(HAlign_Center).VAlign(VAlign_Center)
					.OnClicked_Raw(this, &SMainWidget::OnClickOpenChooseDirWindow).ToolTipText(FText::FromString("Modify the DIR where .wav files saved "))
					]
				+SCanvas::Slot().Position(FVector2D(150.f,300.f)).Size(FVector2D(150.f,30.f))
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot().HAlign(HAlign_Left).VAlign(VAlign_Center)
							[
								SNew(STextBlock).Text(FText::FromString("Speed:"))
							]
						+SHorizontalBox::Slot()
							[
								SAssignNew(SSpeedText, SSpinBox<int>).MinValue(0).MaxValue(100).Value(50)
							]
					]
				+ SCanvas::Slot().Position(FVector2D(150.f, 350.f)).Size(FVector2D(150.f, 30.f))
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot().HAlign(HAlign_Left).VAlign(VAlign_Center)
							[
								SNew(STextBlock).Text(FText::FromString("Volume:"))
							]
						+ SHorizontalBox::Slot()
							[
								SAssignNew(SVolumeText, SSpinBox<int>).MinValue(0).MaxValue(100).Value(50)
							]
					]
				+ SCanvas::Slot().Position(FVector2D(150.f, 400.f)).Size(FVector2D(150.f, 30.f))
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot().HAlign(HAlign_Left).VAlign(VAlign_Center)
							[
								SNew(STextBlock).Text(FText::FromString("Pitch:"))
							]
						+ SHorizontalBox::Slot()
							[
								SAssignNew(SPitchText, SSpinBox<int>).MinValue(0).MaxValue(100).Value(50)
							]
					]
				+ SCanvas::Slot().Position(FVector2D(150.f, 450.f)).Size(FVector2D(150.f, 30.f))
					[
						SNew(SHorizontalBox)
						+ SHorizontalBox::Slot().HAlign(HAlign_Left).VAlign(VAlign_Center)
							[
								SNew(STextBlock).Text(FText::FromString("VoiceName:"))
							]
						+ SHorizontalBox::Slot()
							[
								SAssignNew(SVoiceNameText, SComboBox<VoiceNameSource>)
								.OptionsSource(&VNSourceList)
								.OnGenerateWidget_Raw(this,&SMainWidget::MakeWidgetForVNSource)
								.OnSelectionChanged_Raw(this,&SMainWidget::OnSelectedVNChanged)
								.InitiallySelectedItem(VNSelectIndex)
								[
									SNew(STextBlock).Text(this,&SMainWidget::GetCurrentVNLabel)
								]
							]
					]
			]
		];
}

FReply SMainWidget::OnClickSpawnWave()
{
	FChildren* Children = SContainer->GetChildren();

	for (int i = 0; i < Children->Num(); i++)
	{
		TSharedRef<SWidget> tempWgt = Children->GetChildAt(i);
		static_cast<SBaseLine&>(tempWgt->AsShared().Get()).SpawnWave();
	}
	return FReply::Handled();
}
TSharedRef<SWidget> SMainWidget::MakeWidgetForVNSource(VoiceNameSource InOption)
{
	return SNew(STextBlock).Text(FText::FromString(*InOption));
}

void SMainWidget::OnSelectedVNChanged(VoiceNameSource NewValue, ESelectInfo::Type)
{
	VNSelectIndex = NewValue;
}

FText SMainWidget::GetCurrentVNLabel() const
{
	if (VNSelectIndex.IsValid())
	{
		return FText::FromString(*VNSelectIndex);
	}

	return FText::FromString("xiaoyan");
}
FXFConfig SMainWidget::GetConfig()
{
	FXFConfig tmp;
	tmp.Api_key = "";
	tmp.Appid = "";
	tmp.Speed = FString::FromInt(int(SSpeedText->GetValue()));
	tmp.Voice_name = *SVoiceNameText->GetSelectedItem();
	tmp.Volume = FString::FromInt(int(SVolumeText->GetValue()));
	tmp.Pitch = FString::FromInt(int(SPitchText->GetValue()));

	return tmp;
}
FReply SMainWidget::OnClickOpenChooseDirWindow()
{
	SavedDir = UXFPluginLib::ChooseFloder();
	SDirText->SetText(SavedDir);
	SDirText->SetToolTipText(FText::FromString(SavedDir));
	return FReply::Handled();
}
FReply SMainWidget::OnClickOpenFloder()
{
	UXFPluginLib::OpenFloder();
	return FReply::Handled();
}
FReply SMainWidget::OnClickCreate()
{
		SContainer->AddSlot().HAlign(HAlign_Left).VAlign(VAlign_Top)
		[
			SNew(SBaseLine,this)
		];
	
	return FReply::Handled();
}

FReply SMainWidget::OnClickDeleteAll()
{
	FChildren* Children = SContainer->GetAllChildren();
	int childrenLen = Children->Num();

	for (int i = 0; i < childrenLen; i++)
	{
		TSharedRef<SWidget> tempWgt = Children->GetChildAt(0);
		SContainer->RemoveSlot(tempWgt);
	}
	return FReply::Handled(); 
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
