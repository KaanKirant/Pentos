// Copyright Kaan Kirant.


#include "Actors/AppleActor.h"

#include "Character/PentosCharacter.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"
#include "Pentos/Pentos.h"

AAppleActor::AAppleActor()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	SetReplicateMovement(true);
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMesh);
	StaticMesh->SetRenderCustomDepth(false);
	StaticMesh->SetIsReplicated(true);
	StaticMesh->SetMobility(EComponentMobility::Movable);

	InteractWidget = CreateDefaultSubobject<UWidgetComponent>("InteractWidget");
	InteractWidget->SetupAttachment(GetRootComponent());
	InteractWidget->SetVisibility(false);

}

void AAppleActor::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AAppleActor, IsPicked);
	DOREPLIFETIME(AAppleActor, AttachedCharacter);
}

void AAppleActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAppleActor::OnRep_AttachedCharacter()
{
	if (AttachedCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Client attaching apple to %s"), *AttachedCharacter->GetName());

		// Attach locally on client side (no physics or movement replication needed)
		FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, false);
		AttachToComponent(AttachedCharacter->GetMesh(), TransformRules, FName("RightHandSocket"));

		SetReplicateMovement(false);
		StaticMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);	
		StaticMesh->SetSimulatePhysics(false);
	}
}

void AAppleActor::ActivateInteractMessage()
{
	if (IsPicked) return;
	if (InteractWidget)
		InteractWidget->SetVisibility(true);
}

void AAppleActor::DeactivateInteractMessage()
{
	if (IsPicked) return;
	if (InteractWidget)
		InteractWidget->SetVisibility(false);
}

void AAppleActor::HighlightActor()
{
	if (IsPicked) return;
	StaticMesh->SetRenderCustomDepth(true);
	StaticMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAppleActor::UnHighlightActor()
{
	if (IsPicked) return;
	StaticMesh->SetRenderCustomDepth(false);
}

void AAppleActor::Interact(ACharacter* InteractInstigator)
{
	if (!HasAuthority()) return;
	UE_LOG(LogTemp, Warning, TEXT("In Interact"));
	if (APentosCharacter* PlayerCharacter = Cast<APentosCharacter>(InteractInstigator))
	{
		UE_LOG(LogTemp, Warning, TEXT("In Interact 2"));
		if (PlayerCharacter->CarriedItem == nullptr && !IsPicked)
		{
			UnHighlightActor();
			DeactivateInteractMessage();
			
			IsPicked = true;
			PlayerCharacter->CarriedItem = this;
			SetOwner(PlayerCharacter);
			SetInstigator(PlayerCharacter);

			StaticMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
			StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);	
			StaticMesh->SetSimulatePhysics(false);
			
			FAttachmentTransformRules TransformRules{ EAttachmentRule::SnapToTarget,false };
			AttachToComponent(PlayerCharacter->GetMesh(), TransformRules, FName("RightHandSocket"));

			AttachedCharacter = PlayerCharacter;

			SetReplicateMovement(false);

			
			UE_LOG(LogTemp, Warning, TEXT("Apple attached to %s on %s"),
				*PlayerCharacter->GetName(),
				HasAuthority() ? TEXT("Server") : TEXT("Client"));
		}
	}
}