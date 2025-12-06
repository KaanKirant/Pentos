// Copyright Kaan Kirant.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AITypes.h"
#include "PentosAIController.generated.h"

class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class PENTOS_API APentosAIController : public AAIController
{
	GENERATED_BODY()
public:
	APentosAIController();
	virtual void OnPossess(APawn* InPawn) override;

protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
	
	virtual void OnMoveCompleted(FAIRequestID RequestID,const FPathFollowingResult& Result) override;
};
