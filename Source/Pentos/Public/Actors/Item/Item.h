// Copyright Kaan Kirant.

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class PENTOS_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ItemStaticMesh;

	UPROPERTY(EditAnywhere)
	UImage* ItemImage;

	UPROPERTY(EditAnywhere)
	FName ItemName;
protected:
	virtual void BeginPlay() override;
};
