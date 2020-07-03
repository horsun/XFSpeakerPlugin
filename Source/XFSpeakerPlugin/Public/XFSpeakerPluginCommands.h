// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "XFSpeakerPluginStyle.h"

class FXFSpeakerPluginCommands : public TCommands<FXFSpeakerPluginCommands>
{
public:

	FXFSpeakerPluginCommands()
		: TCommands<FXFSpeakerPluginCommands>(TEXT("XFSpeakerPlugin"), NSLOCTEXT("Contexts", "XFSpeakerPlugin", "XFSpeakerPlugin Plugin"), NAME_None, FXFSpeakerPluginStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};