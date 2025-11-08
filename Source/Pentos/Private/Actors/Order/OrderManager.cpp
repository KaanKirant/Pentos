// Copyright Kaan Kirant.


#include "Actors/Order/OrderManager.h"

// Sets default values
AOrderManager::AOrderManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AOrderManager::BeginPlay()
{
	Super::BeginPlay();
}

FOrder AOrderManager::GetRandomOrder()
{
	if (OrderList.Num() > 0)
	{
		return OrderList[FMath::RandRange(0, OrderList.Num() - 1)];
	}
	else
	{
		return FOrder();
	}
}