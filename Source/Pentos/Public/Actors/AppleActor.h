// Copyright Kaan Kirant.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/InteractInterface.h"
#include "AppleActor.generated.h"

class UWidgetComponent;

UCLASS()
class PENTOS_API AAppleActor : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	AAppleActor();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* InteractWidget;
	
	/** Interact Interface */
	virtual void ActivateInteractMessage() override;
	virtual void DeactivateInteractMessage() override;
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	virtual void Interact(ACharacter* InteractInstigator) override;
	/** End Interact Interface */
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMesh;
	
	UPROPERTY(Replicated)
	bool IsPicked = false;

	UPROPERTY(ReplicatedUsing=OnRep_AttachedCharacter)
	ACharacter* AttachedCharacter;

	UFUNCTION()
	void OnRep_AttachedCharacter();
};
