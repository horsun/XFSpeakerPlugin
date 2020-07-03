// Copyright Epic Games, Inc. All Rights Reserved.

#include "XFSpeakerPluginCommands.h"

#define LOCTEXT_NAMESPACE "FXFSpeakerPluginModule"

void FXFSpeakerPluginCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "XFSpeakerPlugin", "Bring up XFSpeakerPlugin window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
