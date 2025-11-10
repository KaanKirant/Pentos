// Copyright Kaan Kirant.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

UCLASS()
class PENTOS_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnManager();

	// Spawn enemy of setted class.
	UFUNCTION(BlueprintCallable)
	bool SpawnActor();

	// Will schedule an actor spawn
	void ScheduleActorSpawn();

	//Actor class to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ActorClassToBeSpawned;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ShouldSpawn = true;

	// Average time between spawns.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AvgSpawnTime = 5.f;

	// Random +1 or -1 offset.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RandomSpawnTimeOffset = 1.f;
protected:
	virtual void BeginPlay() override;

	// Called when the actor stops playing
	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
private:
	UFUNCTION()
	void SpawnActorScheduled();
	
	// Area to spawn
	UPROPERTY(EditAnywhere)
	UBoxComponent* SpawnBox;

	//Helper for timer
	FTimerHandle SpawnTimerHandle;
};