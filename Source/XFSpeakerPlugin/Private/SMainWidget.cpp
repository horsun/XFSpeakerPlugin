// Fill out your copyright notice in the Description page of Project Settings.


#include "SMainWidget.h"
#include "Widgets/SCanvas.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SMainWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
		[
		SNew(SHorizontalBox)
		 + SHorizontalBox::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill)
			[
				SNew(SCanvas)
				+ SCanvas::Slot().Size(FVector2D(400.f, 600.f)).Position(FVector2D(0.f,0.f))
				[
					SAssignNew(SContainer, SVerticalBox)
					+ SVerticalBox::Slot().HAlign(HAlign_Left).VAlign(VAlign_Top)
					[
						SNew(SBaseLine, SContainer)
					]
				]
			]
		+ SHorizontalBox::Slot().HAlign(HAlign_Fill).VAlign(VAlign_Fill)
			[
			
				
				SNew(SCanvas)
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
					.Text(FText::FromString("OpenFolder")).HAlign(HAlign_Center).VAlign(VAlign_Center)
					.OnClicked_Raw(this, &SMainWidget::OnClickOpenFloder)
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
FReply SMainWidget::OnClickOpenFloder()
{
	UXFPluginLib::OpenFloder();
	return FReply::Handled();
}
FReply SMainWidget::OnClickCreate()
{
		SContainer->AddSlot().HAlign(HAlign_Left).VAlign(VAlign_Top)
		[
			SNew(SBaseLine, SContainer)
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
