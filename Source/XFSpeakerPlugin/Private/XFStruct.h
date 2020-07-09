#pragma once
#include "CoreMinimal.h"
#include "XFStruct.generated.h"

USTRUCT()
struct FXFConfig
{
	GENERATED_USTRUCT_BODY()

	FString Voice_name;
	FString Speed;
	FString Volume;
	FString Pitch;
	FString Appid;
	FString Api_key;
};

USTRUCT(BlueprintType)
struct FVoiceName
{
	GENERATED_USTRUCT_BODY()

	FString CName;
	FString EName;
};