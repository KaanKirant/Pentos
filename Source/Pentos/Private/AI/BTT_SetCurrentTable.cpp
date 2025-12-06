// Copyright Kaan Kirant.


#include "AI/BTT_SetCurrentTable.h"

#include "Actors/Props/TableActor.h"
#include "AI/PentosAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/PentosCustomerCharacter.h"
#include "Kismet/GameplayStatics.h"

UBTT_SetCurrentTable::UBTT_SetCurrentTable()
{
	NodeName = TEXT("Set Current Table");
}

EBTNodeResult::Type UBTT_SetCurrentTable::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APentosAIController* AIController = Cast<APentosAIController>(OwnerComp.GetAIOwner());
	APentosCustomerCharacter* Customer = Cast<APentosCustomerCharacter>(AIController->GetPawn());
	if (!Customer) return EBTNodeResult::Failed;

	//ATableActor* TableActor = Cast<ATableActor>(AIController->GetBlackboardComponent()->GetValueAsObject("ClosestTableActor"));
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), TableClass, TableActors);
	GetAvailableTableActors();

	if (AvailableTableActors.Num() > 0)
	{
		ATableActor* AvilableTableActor = Cast<ATableActor>(AvailableTableActors[FMath::RandRange(0, AvailableTableActors.Num() - 1)]);

		if (AvilableTableActor)
		{
			Customer->CurrentTable = AvilableTableActor;
			AIController->GetBlackboardComponent()->SetValueAsObject("ClosestTableActor", AvilableTableActor);
			AvilableTableActor->IsAvailable = false;
			return EBTNodeResult::Succeeded;
		}
		else
		{
			return EBTNodeResult::Failed;
		}
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}

void UBTT_SetCurrentTable::GetAvailableTableActors()
{
	for (AActor* Actor : TableActors)
	{
		ATableActor* TableActor = Cast<ATableActor>(Actor);
		if (TableActor->IsAvailable)
		{
			AvailableTableActors.Add(TableActor);
		}
	}
}
