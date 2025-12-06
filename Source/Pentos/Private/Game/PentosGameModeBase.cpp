// Copyright Kaan Kirant.


#include "Game/PentosGameModeBase.h"

void APentosGameModeBase::TravelToMap(FString MapName)
{
	UWorld* World = GetWorld();
	if (!World) return;

	// Travel all players into the game map
	World->ServerTravel(FString::Printf(TEXT("%s?listen"), *MapName));
}
