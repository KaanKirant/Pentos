// Copyright Kaan Kirant.


#include "Actors/Item/Item.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = false;
	ItemStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	ItemStaticMesh->SetupAttachment(GetRootComponent());
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}
