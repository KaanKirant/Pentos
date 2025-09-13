// Copyright Kaan Kirant.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PentosCharacterBase.generated.h"

UCLASS()
class PENTOS_API APentosCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	APentosCharacterBase();

protected:
	virtual void BeginPlay() override;
};
