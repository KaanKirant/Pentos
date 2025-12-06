// Copyright Kaan Kirant.


#include "Actors/Props/PlateActor.h"

APlateActor::APlateActor()
{
	PrimaryActorTick.bCanEverTick = false;
	PlateStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	PlateStaticMesh->SetupAttachment(GetRootComponent());
}

void APlateActor::BeginPlay()
{
	Super::BeginPlay();
	
}

