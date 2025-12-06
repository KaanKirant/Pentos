// Copyright Kaan Kirant.


#include "Actors/Props/TableActor.h"

#include "Character/PentosCharacter.h"
#include "Components/WidgetComponent.h"
#include "Pentos/Pentos.h"


ATableActor::ATableActor()
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	
	ItemDropOffPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ItemDropOffPoint"));
	ItemDropOffPoint->SetupAttachment(StaticMesh);
	
	InteractWidget = CreateDefaultSubobject<UWidgetComponent>("InteractWidget");
	InteractWidget->SetupAttachment(StaticMesh);
	InteractWidget->SetVisibility(false);
}

void ATableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATableActor::ActivateInteractMessage()
{
	if (InteractWidget)
		InteractWidget->SetVisibility(true);
}

void ATableActor::DeactivateInteractMessage()
{
	if (InteractWidget)
		InteractWidget->SetVisibility(false);
}

void ATableActor::HighlightActor()
{
	StaticMesh->SetRenderCustomDepth(true);
	StaticMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void ATableActor::UnHighlightActor()
{
	StaticMesh->SetRenderCustomDepth(false);
}

void ATableActor::Interact(ACharacter* InteractInstigator)
{
	if (ItemOnTop)
	{
		if (APentosCharacter* PlayerCharacter = Cast<APentosCharacter>(InteractInstigator))
		{
			if (PlayerCharacter->CarriedItem == nullptr) // IsPicked? Should this be an actor or item?
			{
				PlayerCharacter->CarriedItem = ItemOnTop;
				ItemOnTop->SetOwner(PlayerCharacter);
				

				//PlayerCharacter->CarriedItem->StaticMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
				//PlayerCharacter->CarriedItem->StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);	
				//PlayerCharacter->CarriedItem->StaticMesh->SetSimulatePhysics(false);
			
				FAttachmentTransformRules TransformRules{ EAttachmentRule::SnapToTarget,false };
				ItemOnTop->AttachToComponent(PlayerCharacter->GetMesh(), TransformRules, FName(TEXT("RightHandSocket")));
				ItemOnTop = nullptr;
				SetReplicateMovement(false);
			}
		}
	}
	else
	{
		if (APentosCharacter* PlayerCharacter = Cast<APentosCharacter>(InteractInstigator))
		{
			if (PlayerCharacter->CarriedItem != nullptr) // IsPicked? Should this be an actor or item?
			{
				PlayerCharacter->CarriedItem->SetOwner(this);
				PlayerCharacter->CarriedItem->SetActorTransform(ItemDropOffPoint->GetComponentTransform());
				PlayerCharacter->CarriedItem->SetActorLocation(ItemDropOffPoint->GetComponentLocation());

				//PlayerCharacter->CarriedItem->StaticMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
				//PlayerCharacter->CarriedItem->StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);	
				//PlayerCharacter->CarriedItem->StaticMesh->SetSimulatePhysics(false);
			
				FAttachmentTransformRules TransformRules{ EAttachmentRule::SnapToTarget,false };
				PlayerCharacter->CarriedItem->AttachToComponent(StaticMesh, TransformRules, FName(TEXT("DropOffPoint")));
				ItemOnTop = PlayerCharacter->CarriedItem;
				PlayerCharacter->CarriedItem = nullptr;
				SetReplicateMovement(false);
			}
		}
	}
}
