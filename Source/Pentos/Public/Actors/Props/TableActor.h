// Copyright Kaan Kirant.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TableActor.generated.h"

UCLASS()
class PENTOS_API ATableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ATableActor();
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	bool IsAvailable = true;
protected:
	virtual void BeginPlay() override;
};
