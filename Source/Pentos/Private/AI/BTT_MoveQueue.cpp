// Copyright Kaan Kirant.


#include "AI/BTT_MoveQueue.h"

#include "Actors/Queue/QueueArea.h"
#include "AI/PentosAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Character/PentosCustomerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_MoveQueue::UBTT_MoveQueue()
{
	NodeName = TEXT("Move Queue");
}

EBTNodeResult::Type UBTT_MoveQueue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const APentosAIController* AIController = Cast<APentosAIController>(OwnerComp.GetAIOwner());
	APentosCustomerCharacter* Customer = Cast<APentosCustomerCharacter>(AIController->GetPawn());
	if (!Customer) return EBTNodeResult::Failed;
	
	AQueueArea* QueueArea = Customer->QueueArea;
	if (!QueueArea) return EBTNodeResult::Failed;

	QueueArea->MoveQueue();

	for (int32 i = 1; i < QueueArea->WaitPoints.Num()-1; i++)
	{
		//First one null as well
		if (QueueArea->WaitPoints[i]->CurrentCustomer == nullptr) continue;
		UE_LOG(LogTemp, Warning, TEXT("(Before Change) WaitPoint %i, Current Customer: %s, IsAvailable: %i"), QueueArea->WaitPoints[i]->PointIndex, *QueueArea->WaitPoints[i]->CurrentCustomer->GetName(), QueueArea->WaitPoints[i]->IsAvailable);
		QueueArea->WaitPoints[i]->CurrentCustomer->PentosAIController->GetBlackboardComponent()->SetValueAsBool("CanMove", false);
		QueueArea->WaitPoints[i]->CurrentCustomer->PentosAIController->GetBlackboardComponent()->SetValueAsVector("QueueTarget", QueueArea->WaitPoints[i-1]->PointLocation);
		//if (i==1) QueueArea->WaitPoints[i]->CurrentCustomer->PentosAIController->GetBlackboardComponent()->SetValueAsBool("IsFirst", true);
		QueueArea->WaitPoints[i-1]->CurrentCustomer = QueueArea->WaitPoints[i]->CurrentCustomer; // The customer behind is now is ahead customer
		UE_LOG(LogTemp, Warning, TEXT("(After Change) WaitPoint %i, Current Customer: %s, IsAvailable: %i"), QueueArea->WaitPoints[i]->PointIndex, *QueueArea->WaitPoints[i]->CurrentCustomer->GetName(), QueueArea->WaitPoints[i]->IsAvailable);
		QueueArea->WaitPoints[i-1]->CurrentCustomer->PentosAIController->GetBlackboardComponent()->SetValueAsBool("IsFirst", QueueArea->IsFirstPoint(QueueArea->WaitPoints[i-1]->CurrentCustomer->WaitPoint));
		QueueArea->WaitPoints[i]->CurrentCustomer = nullptr; // The customer moved from this spot so there is no one here.
		QueueArea->WaitPoints[i]->IsAvailable = true; // The customer moved from this position so its available
		QueueArea->WaitPoints[i-1]->IsAvailable = false; // The customer moved to this position so its not available
		QueueArea->WaitPoints[i-1]->CurrentCustomer->WaitPoint = QueueArea->WaitPoints[i-1];
	}
	return EBTNodeResult::Succeeded;
}
