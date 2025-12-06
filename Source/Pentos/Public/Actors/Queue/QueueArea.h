// Copyright Kaan Kirant.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QueueArea.generated.h"

class APentosCustomerCharacter;
struct FSplinePoint;
class USplineComponent;

USTRUCT()
struct FWaitPoint
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere)
	FVector PointLocation = FVector::ZeroVector;
	
	UPROPERTY(VisibleAnywhere)
	int32 PointIndex = 99;

	UPROPERTY(VisibleAnywhere)
	APentosCustomerCharacter* CurrentCustomer = nullptr;
	
	UPROPERTY(VisibleAnywhere)
	bool IsAvailable = true;
};

UCLASS()
class PENTOS_API AQueueArea : public AActor
{
	GENERATED_BODY()
	
public:	
	AQueueArea();
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Queue")
	USplineComponent* QueueSpline;

	void FillWaitPoints();
	FWaitPoint* GetFirstAvailableWaitPoint();
	bool IsFirstPoint(const FWaitPoint* WaitPoint);
	bool IsAvailable(const FWaitPoint* WaitPoint);
	void LeaveQueue(FWaitPoint* WaitPoint);
	void MoveQueue();
	
	TArray<FWaitPoint*> WaitPoints;
};
