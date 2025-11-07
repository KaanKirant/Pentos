// Copyright Kaan Kirant.


#include "Actors/Queue/QueueArea.h"
#include "Components/SplineComponent.h"

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
		WaitPoints.Insert(WaitPoint, i);
	}
}

FWaitPoint* AQueueArea::GetFirstAvailableWaitPoint()
{
	for (FWaitPoint* WaitPoint : WaitPoints)
	{
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
	WaitPoint->IsAvailable = true;
}