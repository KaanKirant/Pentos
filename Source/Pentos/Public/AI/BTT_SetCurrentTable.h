// Copyright Kaan Kirant.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_SetCurrentTable.generated.h"

class APentosCustomerCharacter;
class ATableActor;
/**
 * 
 */
UCLASS()
class PENTOS_API UBTT_SetCurrentTable : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTT_SetCurrentTable();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATableActor> TableClass;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> TableActors;

	UPROPERTY(EditAnywhere)
	TArray<ATableActor*> AvailableTableActors;

	void GetAvailableTableActors();
};
