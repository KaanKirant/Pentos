// Copyright Kaan Kirant.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
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
protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};
