// Copyright Kaan Kirant.


#include "Player/PentosPlayerController.h"
#include "EnhancedInputSubsystems.h"

APentosPlayerController::APentosPlayerController()
{
	bReplicates = true;
}

void APentosPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void APentosPlayerController::OnRep_Pawn()
{
	Super::OnRep_Pawn();
	check(PentosContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	
	check(Subsystem);
	Subsystem->AddMappingContext(PentosContext, 0);
}
