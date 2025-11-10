// Copyright Kaan Kirant.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Order/OrderManager.h"
#include "Actors/Queue/QueueArea.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Character/PentosCharacterBase.h"
#include "Interaction/InteractInterface.h"
#include "PentosCustomerCharacter.generated.h"

class ATableActor;
class UWidgetComponent;
class UBehaviorTree;
class APentosAIController;
class AQueueArea;
/**
 * 
 */
UCLASS()
class PENTOS_API APentosCustomerCharacter : public APentosCharacterBase, public IInteractInterface
{
	GENERATED_BODY()
public:
	APentosCustomerCharacter();
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* InteractWidget;

	UPROPERTY(EditAnywhere, Category="AI")
	AQueueArea* QueueArea;

	UPROPERTY(EditAnywhere, Category="AI")
	TSubclassOf<AQueueArea> QueueAreaClass;

	UPROPERTY(EditAnywhere, Category="Order")
	AOrderManager* OrderManager;

	UPROPERTY(EditAnywhere, Category="Order")
	TSubclassOf<AOrderManager> OrderManagerClass;

	UPROPERTY(EditAnywhere)
	ATableActor* CurrentTable = nullptr;

	UPROPERTY(VisibleAnywhere)
	FOrder Order;

	FWaitPoint* WaitPoint = nullptr;
	
	/** Interact Interface */
	virtual void ActivateInteractMessage() override;
	virtual void DeactivateInteractMessage() override;
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	virtual void Interact(ACharacter* InteractInstigator) override;
	/** End Interact Interface */
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	UPROPERTY()
	TObjectPtr<APentosAIController> PentosAIController;

	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector IsServedKey;
};
