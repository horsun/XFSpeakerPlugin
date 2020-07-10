// Copyright Epic Games, Inc. All Rights Reserved.

#include "XFSpeakerPlugin.h"
#include "XFSpeakerPluginStyle.h"
#include "XFSpeakerPluginCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName XFSpeakerPluginTabName("讯飞语音生成");

#define LOCTEXT_NAMESPACE "FXFSpeakerPluginModule"

void FXFSpeakerPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FXFSpeakerPluginStyle::Initialize();
	FXFSpeakerPluginStyle::ReloadTextures();

	FXFSpeakerPluginCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FXFSpeakerPluginCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FXFSpeakerPluginModule::PluginButtonClicked),
		FCanExecuteAction());
	FGlobalTabmanager::RegisterDefaultTabWindowSize(XFSpeakerPluginTabName, FVector2D(800.f, 600.f));
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FXFSpeakerPluginModule::RegisterMenus));
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(XFSpeakerPluginTabName, FOnSpawnTab::CreateRaw(this, &FXFSpeakerPluginModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FXFSpeakerPluginTabTitle", "讯飞语音生成"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
		

}

void FXFSpeakerPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FXFSpeakerPluginStyle::Shutdown();

	FXFSpeakerPluginCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(XFSpeakerPluginTabName);
}

TSharedRef<SDockTab> FXFSpeakerPluginModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(SCanvas)
			+SCanvas::Slot()
			.Position(FVector2D(0.f,0.f))
			.Size(FVector2D(800.f,500.f))
			[
				SNew(SMainWidget)
			]
			
		];
}

void FXFSpeakerPluginModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(XFSpeakerPluginTabName);
}

FReply FXFSpeakerPluginModule::SpawnTestButton()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("test"));
	if (USpawner==nullptr)
	{
		USpawner = NewObject<UXFSpeakerProcess>(); USpawner->AddToRoot();
	};

	USpawner->SpawnWaveFile(TEXT("哈哈哈哈哈哈哈哈哈哈"), "test.wav");

	return FReply::Handled();
}


void FXFSpeakerPluginModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FXFSpeakerPluginCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FXFSpeakerPluginCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FXFSpeakerPluginModule, XFSpeakerPlugin)