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
	FString Appid;
	FString Api_key;
};