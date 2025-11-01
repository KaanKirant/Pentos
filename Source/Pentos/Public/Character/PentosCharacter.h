// Copyright Kaan Kirant.

#pragma once

#include "CoreMinimal.h"
#include "Character/PentosCharacterBase.h"
#include "PentosCharacter.generated.h"

class UCameraComponent;
/**
 * 
 */
UCLASS()
class PENTOS_API APentosCharacter : public APentosCharacterBase
{
	GENERATED_BODY()
public:
	APentosCharacter();
	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(BlueprintReadOnly)
	AActor* CarriedItem;
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> Camera;
public:
	FORCEINLINE UCameraComponent* GetCamera() {return Camera;}
};
