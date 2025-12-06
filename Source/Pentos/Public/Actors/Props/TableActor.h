// Copyright Kaan Kirant.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/InteractInterface.h"
#include "TableActor.generated.h"

class UWidgetComponent;

UCLASS()
class PENTOS_API ATableActor : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	ATableActor();
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	USceneComponent* ItemDropOffPoint;

	UPROPERTY(EditAnywhere)
	bool IsAvailable = true;

	UPROPERTY(EditAnywhere)
	AActor* ItemOnTop = nullptr;

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
};
