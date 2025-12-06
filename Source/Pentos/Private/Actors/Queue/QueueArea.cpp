// Copyright Kaan Kirant.


#include "Actors/Queue/QueueArea.h"

#include "AI/CustomerAIComponent.h"
#include "AI/PentosAIController.h"
#include "Character/PentosCustomerCharacter.h"
#include "Components/SplineComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

// Only one queue in each level. Should this be a singleton?
AQueueArea::AQueueArea()
{
	PrimaryActorTick.bCanEverTick = true;
	QueueSpline = CreateDefaultSubobject<USplineComponent>(TEXT("QueueSpline"));
	RootComponent = QueueSpline;
}

void AQueueArea::BeginPlay()
{
	Super::BeginPlay();
	FillWaitPoints();
}

void AQueueArea::FillWaitPoints()
{
	if (!QueueSpline) return;
	WaitPoints.Empty();
	
	for (int32 i = 0; i < QueueSpline->GetNumberOfSplinePoints()-1; i++)
	{
		FWaitPoint* WaitPoint = new FWaitPoint();
		WaitPoint->PointLocation = QueueSpline->GetLocationAtSplinePoint(i,ESplineCoordinateSpace::World);
		WaitPoint->PointIndex = i;
		WaitPoint->IsAvailable = true;
		WaitPoint->CurrentCustomer = nullptr;
		WaitPoints.Insert(WaitPoint, i);
	}
}

FWaitPoint* AQueueArea::GetFirstAvailableWaitPoint()
{
	for (FWaitPoint* WaitPoint : WaitPoints)
	{
		//if (WaitPoint->CurrentCustomer)
			//UE_LOG(LogTemp, Warning, TEXT("WaitPoint %i, Current Customer: %s, IsAvailable: %i"), WaitPoint->PointIndex, *WaitPoint->CurrentCustomer->GetName(), WaitPoint->IsAvailable);
		if (WaitPoint->IsAvailable)
		{
			return WaitPoint;
		}
	}
	return nullptr;
}

bool AQueueArea::IsFirstPoint(const FWaitPoint* WaitPoint)
{
	return WaitPoint->PointIndex == 0;
}

bool AQueueArea::IsAvailable(const FWaitPoint* WaitPoint)
{
	return WaitPoint->IsAvailable;
}

void AQueueArea::LeaveQueue(FWaitPoint* WaitPoint)
{
	if (!IsFirstPoint(WaitPoint)) return;
	WaitPoint->IsAvailable = true;
	WaitPoint->CurrentCustomer = nullptr;
}

void AQueueArea::MoveQueue()
{
	for (int32 i = 0; i < WaitPoints.Num()-1; i++)
	{
		if (i == 0)
		{
			LeaveQueue(WaitPoints[i]); //First moves out of queue
			continue;
		}
		if (WaitPoints[i]->CurrentCustomer == nullptr) continue;
		WaitPoints[i]->CurrentCustomer->WaitPoint = nullptr;
		WaitPoints[i-1]->CurrentCustomer = WaitPoints[i]->CurrentCustomer;
		WaitPoints[i]->CurrentCustomer = nullptr;
		WaitPoints[i-1]->CurrentCustomer->WaitPoint = WaitPoints[i-1];
		WaitPoints[i-1]->IsAvailable = false;
		WaitPoints[i]->IsAvailable = true;
		WaitPoints[i-1]->CurrentCustomer->CustomerAI->MoveCustomerTo(WaitPoints[i-1]->PointLocation);
		//WaitPoints[i-1]->CurrentCustomer->PentosAIController->GetBlackboardComponent()->SetValueAsVector("QueueTarget", WaitPoints[i-1]->PointLocation);
		//WaitPoints[i-1]->CurrentCustomer->PentosAIController->GetBlackboardComponent()->SetValueAsBool("IsFirst", IsFirstPoint(WaitPoints[i-1]));
	}
}
