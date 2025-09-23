// Copyright Kaan Kirant.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PENTOS_API IInteractInterface
{
	GENERATED_BODY()

public:
	virtual void ActivateInteractMessage() = 0;
	virtual void DeactivateInteractMessage() = 0;
	virtual void HighlightActor() = 0;
	virtual void UnHighlightActor() = 0;
	virtual void Interact() = 0;
};
