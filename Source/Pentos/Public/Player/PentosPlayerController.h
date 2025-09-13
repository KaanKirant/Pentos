// Copyright Kaan Kirant.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PentosPlayerController.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class PENTOS_API APentosPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	APentosPlayerController();
protected:
	virtual void BeginPlay() override;
	virtual void OnRep_Pawn() override;
private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> PentosContext;
};
