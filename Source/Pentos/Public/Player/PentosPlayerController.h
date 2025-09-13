// Copyright Kaan Kirant.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PentosPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

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
	void AddMappingContext();
	virtual void OnRep_Pawn() override;
	virtual void SetupInputComponent() override;
private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> PentosContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);
};
