// Copyright Kaan Kirant.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlateActor.generated.h"

class AItem;

UCLASS()
class PENTOS_API APlateActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APlateActor();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PlateStaticMesh;

	UPROPERTY(EditAnywhere)
	TArray<AItem*> PlateItems;

	UPROPERTY(EditAnywhere)
	bool IsClean = true;
protected:
	virtual void BeginPlay() override;
};
