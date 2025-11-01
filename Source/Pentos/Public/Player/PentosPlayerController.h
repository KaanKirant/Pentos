// Copyright Kaan Kirant.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PentosPlayerController.generated.h"

class IInteractInterface;
class APentosCharacter;
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
	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void OnRep_Pawn() override;
	virtual void SetupInputComponent() override;
	void AddMappingContext();
	void PerformTraceLine();
private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> PentosContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditAnywhere)
	TObjectPtr<APentosCharacter> PlayerCharacter;

	TScriptInterface<IInteractInterface> LastActor;
	TScriptInterface<IInteractInterface> ThisActor;
	
	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);

	void TryToInteract();
	
	UFUNCTION(Server, Reliable)
	void ServerInteract(AActor* ActorToInteract);
	
};
