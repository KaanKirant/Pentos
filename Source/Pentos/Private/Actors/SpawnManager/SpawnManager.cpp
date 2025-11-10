// Copyright Kaan Kirant.


#include "Actors/SpawnManager/SpawnManager.h"

#include "Character/PentosCustomerCharacter.h"

// Sets default values
ASpawnManager::ASpawnManager()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	SpawnBox = CreateDefaultSubobject<UBoxComponent>("SpawnBox");
	RootComponent = SpawnBox;
}

void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();
	if (ShouldSpawn)
	{
		ScheduleActorSpawn();
	}
}

void ASpawnManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	//Remove all timers
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
}

bool ASpawnManager::SpawnActor()
{
	APentosCustomerCharacter* SpawnedActor = nullptr;
	if (ActorClassToBeSpawned)
	{
		FBoxSphereBounds BoxBounds = SpawnBox->CalcBounds(GetActorTransform());

		FVector SpawnLocation = BoxBounds.Origin;
		SpawnLocation.X += -BoxBounds.BoxExtent.X + 2 * BoxBounds.BoxExtent.X * FMath::FRand();
		SpawnLocation.Y += -BoxBounds.BoxExtent.Y + 2 * BoxBounds.BoxExtent.Y * FMath::FRand();
		SpawnLocation.Z += -BoxBounds.BoxExtent.Z + 2 * BoxBounds.BoxExtent.Z * FMath::FRand();
		//Spawn actor
		SpawnedActor = Cast<APentosCustomerCharacter>(GetWorld()->SpawnActor(ActorClassToBeSpawned, &SpawnLocation));
		if (SpawnedActor && SpawnedActor->Controller == nullptr)
		{
			SpawnedActor->SpawnDefaultController();  // This triggers PossessedBy()
		}
	}

	return SpawnedActor != nullptr;
}

void ASpawnManager::SpawnActorScheduled()
{
	SpawnActor();
	if (ShouldSpawn)
	{
		ScheduleActorSpawn();
	}
}

void ASpawnManager::ScheduleActorSpawn()
{
	float DeltaToNextSpawn = AvgSpawnTime + (-RandomSpawnTimeOffset + 2 * RandomSpawnTimeOffset * FMath::FRand());

	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawnManager::SpawnActorScheduled, DeltaToNextSpawn, false);
}
