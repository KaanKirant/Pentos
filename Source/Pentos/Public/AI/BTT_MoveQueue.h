// Copyright Kaan Kirant.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_MoveQueue.generated.h"

/**
 * 
 */
UCLASS()
class PENTOS_API UBTT_MoveQueue : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTT_MoveQueue();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
