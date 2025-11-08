// Copyright Kaan Kirant.


#include "Character/PentosCustomerCharacter.h"

#include "Actors/Order/OrderManager.h"
#include "Actors/Queue/QueueArea.h"
#include "AI/PentosAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/PentosCharacter.h"
#include "Components/WidgetComponent.h"
#include "Pentos/Pentos.h"

APentosCustomerCharacter::APentosCustomerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	SetReplicateMovement(true);
	
	GetMesh()->SetRenderCustomDepth(false);
	GetMesh()->SetIsReplicated(true);

	InteractWidget = CreateDefaultSubobject<UWidgetComponent>("InteractWidget");
	InteractWidget->SetupAttachment(GetRootComponent());
	InteractWidget->SetVisibility(false);
}

void APentosCustomerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;
	PentosAIController = Cast<APentosAIController>(NewController);

	PentosAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	PentosAIController->RunBehaviorTree(BehaviorTree);
	if (OrderManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("APentosCustomerCharacter::PossessedBy"));
		
	}
		Order = OrderManager->GetRandomOrder();
}

void APentosCustomerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (OrderManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("APentosCustomerCharacter::BeginPlay"));
		Order = OrderManager->GetRandomOrder();
	}
		
}

void APentosCustomerCharacter::ActivateInteractMessage()
{
	if (InteractWidget)
		InteractWidget->SetVisibility(true);
}

void APentosCustomerCharacter::DeactivateInteractMessage()
{
	if (InteractWidget)
		InteractWidget->SetVisibility(false);
}

void APentosCustomerCharacter::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void APentosCustomerCharacter::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
}

void APentosCustomerCharacter::Interact(ACharacter* InteractInstigator)
{
	if (QueueArea->IsFirstPoint(WaitPoint))
	{
		APentosCharacter* PlayerCharacter = Cast<APentosCharacter>(InteractInstigator);
		PlayerCharacter->OrderList.Add(Order);
		PentosAIController->GetBlackboardComponent()->SetValueAsBool("IsServed", true); //KeyName should be ordertaken not served.
		QueueArea->LeaveQueue(WaitPoint);
	}

	//TODO: Serve
}


