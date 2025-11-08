// Copyright Kaan Kirant.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OrderManager.generated.h"

class UImage;
class AItem;

USTRUCT()
struct FOrder
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<AItem*> Items;

	UPROPERTY(EditAnywhere)
	FName OrderName;

	UPROPERTY(EditAnywhere)
	UImage* OrderImage;
	
	UPROPERTY(VisibleAnywhere)
	bool IsOrderServed = false;
};

UCLASS()
class PENTOS_API AOrderManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AOrderManager();
	
	UPROPERTY(EditAnywhere, Category="Order")
	TArray<FOrder> OrderList;

	FOrder GetRandomOrder();
protected:
	virtual void BeginPlay() override;
};
