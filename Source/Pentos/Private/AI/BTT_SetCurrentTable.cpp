// Copyright Kaan Kirant.


#include "AI/BTT_SetCurrentTable.h"

#include "Actors/Props/TableActor.h"
#include "AI/PentosAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/PentosCustomerCharacter.h"

UBTT_SetCurrentTable::UBTT_SetCurrentTable()
{
	NodeName = TEXT("Set Current Table");
}

EBTNodeResult::Type UBTT_SetCurrentTable::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APentosAIController* AIController = Cast<APentosAIController>(OwnerComp.GetAIOwner());
	APentosCustomerCharacter* Customer = Cast<APentosCustomerCharacter>(AIController->GetPawn());
	if (!Customer) return EBTNodeResult::Failed;

	ATableActor* TableActor = Cast<ATableActor>(AIController->GetBlackboardComponent()->GetValueAsObject("ClosestTableActor"));

	if (TableActor && TableActor->IsAvailable)
	{
		Customer->CurrentTable = TableActor;
		AIController->GetBlackboardComponent()->SetValueAsBool("ClosestTableIsAvailable", true);
		TableActor->IsAvailable = false;
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}
