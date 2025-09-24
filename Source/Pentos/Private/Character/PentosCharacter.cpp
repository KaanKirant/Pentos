// Copyright Kaan Kirant.

#include "Character/PentosCharacter.h"
#include "Camera/CameraComponent.h"

APentosCharacter::APentosCharacter()
{
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(GetRootComponent());
}
