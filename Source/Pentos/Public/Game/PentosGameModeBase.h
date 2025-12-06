// Copyright Kaan Kirant.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PentosGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PENTOS_API APentosGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void TravelToMap(FString MapName = FString(TEXT("/Game/Maps/MainLevel")));
};
