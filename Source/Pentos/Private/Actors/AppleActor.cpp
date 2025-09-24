// Copyright Kaan Kirant.


#include "Actors/AppleActor.h"

#include "Components/WidgetComponent.h"
#include "Pentos/Pentos.h"

AAppleActor::AAppleActor()
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetRenderCustomDepth(false);
	SetRootComponent(StaticMesh);

	InteractWidget = CreateDefaultSubobject<UWidgetComponent>("InteractWidget");
	InteractWidget->SetupAttachment(GetRootComponent());
	InteractWidget->SetVisibility(false);

}

void AAppleActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAppleActor::ActivateInteractMessage()
{
	if (InteractWidget)
		InteractWidget->SetVisibility(true);
}

void AAppleActor::DeactivateInteractMessage()
{
	if (InteractWidget)
		InteractWidget->SetVisibility(false);
}

void AAppleActor::HighlightActor()
{
	StaticMesh->SetRenderCustomDepth(true);
	StaticMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAppleActor::UnHighlightActor()
{
	StaticMesh->SetRenderCustomDepth(false);
}

void AAppleActor::Interact()
{
}