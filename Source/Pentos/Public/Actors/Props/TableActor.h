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
	// Sets default values for this actor's properties
	ATableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
