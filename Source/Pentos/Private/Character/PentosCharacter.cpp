// Copyright Kaan Kirant.

#include "Character/PentosCharacter.h"
#include "Camera/CameraComponent.h"
#include "Player/PentosPlayerController.h"
#include "UI/HUD/PentosHUD.h"

APentosCharacter::APentosCharacter()
{
	bReplicates = true;
	SetReplicateMovement(true);
	SetNetUpdateFrequency(100.f);
	SetMinNetUpdateFrequency(33.f);
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(GetRootComponent());
}

void APentosCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (const APentosPlayerController* AuraPlayerController = Cast<APentosPlayerController>(GetController()))
	{
		if (APentosHUD* AuraHUD = Cast<APentosHUD>(AuraPlayerController->GetHUD()))
		{
			AuraHUD->InitOverlay();
		}
	}
}
