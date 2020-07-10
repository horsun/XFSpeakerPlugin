// Copyright Epic Games, Inc. All Rights Reserved.

#include "XFSpeakerPluginCommands.h"

#define LOCTEXT_NAMESPACE "FXFSpeakerPluginModule"

void FXFSpeakerPluginCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow,"讯飞生成器", "讯飞语音在线生成", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
