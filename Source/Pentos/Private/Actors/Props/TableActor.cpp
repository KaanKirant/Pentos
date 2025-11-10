// Copyright Kaan Kirant.


#include "Actors/Props/TableActor.h"

ATableActor::ATableActor()
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
}

void ATableActor::BeginPlay()
{
	Super::BeginPlay();
	
}