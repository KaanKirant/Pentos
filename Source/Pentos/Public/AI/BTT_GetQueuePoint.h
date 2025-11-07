// Copyright Kaan Kirant.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_GetQueuePoint.generated.h"

/**
 * 
 */
UCLASS()
class PENTOS_API UBTT_GetQueuePoint : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTT_GetQueuePoint();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector SelfActorKey;

	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector QueueAreaKey;

	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector TargetPointKey;

	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector IsFirstKey;

	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector QueueTargetIndexKey;
};
