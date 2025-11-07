// Copyright Kaan Kirant.


#include "AI/BTT_GetQueuePoint.h"

#include "Actors/Queue/QueueArea.h"
#include "AI/PentosAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/PentosCustomerCharacter.h"

UBTT_GetQueuePoint::UBTT_GetQueuePoint()
{
	NodeName = TEXT("Get Queue Point");
}

EBTNodeResult::Type UBTT_GetQueuePoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const APentosAIController* AIController = Cast<APentosAIController>(OwnerComp.GetAIOwner());
	APentosCustomerCharacter* Customer = Cast<APentosCustomerCharacter>(AIController->GetPawn());
	if (!Customer) return EBTNodeResult::Failed;

	AQueueArea* QueueArea = Customer->QueueArea;

	if (!QueueArea) return EBTNodeResult::Failed;
	
	FWaitPoint* WaitPoint = QueueArea->GetFirstAvailableWaitPoint();
	
	if (Customer->WaitPoint) //Did customer had its first target?
	{
		//Yes customer has a target.
		if (WaitPoint->PointIndex >= Customer->WaitPoint->PointIndex) // The new spot better than the current spot?
		{
			return EBTNodeResult::Succeeded; // Customer has point and its either same one or worst index.
		}
		else // Customer has a point but there is a better point.
		{
			Customer->WaitPoint->IsAvailable = true; // Change customers previous spot to available
			Customer->WaitPoint = WaitPoint; // Assign the customer the new spot
			Customer->WaitPoint->IsAvailable = false; // Change the new spots availability.
			const FVector TargetPoint = WaitPoint->PointLocation; // Get the new spots location
			const int32 TargetIndex = WaitPoint->PointIndex;
			const bool TargetIsFirst = QueueArea->IsFirstPoint(WaitPoint);
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(IsFirstKey.SelectedKeyName, TargetIsFirst);
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetPointKey.SelectedKeyName, TargetPoint);
			OwnerComp.GetBlackboardComponent()->SetValueAsInt(QueueTargetIndexKey.SelectedKeyName, TargetIndex);
			return EBTNodeResult::Succeeded;
		}
	}
	else
	{
		// No this is the first target
		Customer->WaitPoint = WaitPoint;
		Customer->WaitPoint->IsAvailable = false;
		const FVector TargetPoint = WaitPoint->PointLocation; // Get the new spots location
		const int32 TargetIndex = WaitPoint->PointIndex;
		const bool TargetIsFirst = QueueArea->IsFirstPoint(WaitPoint);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(IsFirstKey.SelectedKeyName, TargetIsFirst);
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetPointKey.SelectedKeyName, TargetPoint);
		OwnerComp.GetBlackboardComponent()->SetValueAsInt(QueueTargetIndexKey.SelectedKeyName, TargetIndex);
		return EBTNodeResult::Succeeded;
	}
}
