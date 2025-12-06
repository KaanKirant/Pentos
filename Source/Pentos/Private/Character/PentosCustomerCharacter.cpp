// Copyright Kaan Kirant.


#include "Character/PentosCustomerCharacter.h"

#include "Actors/Order/OrderManager.h"
#include "Actors/Props/PlateActor.h"
#include "Actors/Props/TableActor.h"
#include "Actors/Queue/QueueArea.h"
#include "AI/CustomerAIComponent.h"
#include "AI/PentosAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/PentosCharacter.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
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

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = APentosCustomerCharacter::StaticClass();

	CustomerAI = CreateDefaultSubobject<UCustomerAIComponent>(TEXT("CustomerAI"));
}

void APentosCustomerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;
	UE_LOG(LogTemp, Warning, TEXT("APentosCustomerCharacter::PossessedBy"));
	PentosAIController = Cast<APentosAIController>(NewController);

	PentosAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	PentosAIController->RunBehaviorTree(BehaviorTree);
	if (OrderManager)
	{
		Order = OrderManager->GetRandomOrder();
	}
}

void APentosCustomerCharacter::BeginPlay()
{
	Super::BeginPlay();
	QueueArea = Cast<AQueueArea>(UGameplayStatics::GetActorOfClass(GetWorld(), QueueAreaClass));
	OrderManager = Cast<AOrderManager>(UGameplayStatics::GetActorOfClass(GetWorld(), OrderManagerClass));
	SpawnManager = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), SpawnManagerClass));
	if (OrderManager)
	{
		Order = OrderManager->GetRandomOrder();
	}
	if (QueueArea)
		CustomerAI->SetState(ECustomerState::Entering);
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
	
	//if (PentosAIController->GetBlackboardComponent()->GetValueAsBool("IsSatDown")) // && CurrentTable->Customer = this (Customer should be child of the table when they arrive to the table) (So player cannot take order while customer is going to the table)
	if (CurrentTable != nullptr)
	{
		CustomerAI->SetState(ECustomerState::Eating);
		// If already at a table -> Serve
		APentosCharacter* PlayerCharacter = Cast<APentosCharacter>(InteractInstigator);
		UE_LOG(LogTemp, Warning, TEXT("APentosCustomerCharacter::Interact-Table, CustomerName: %s"), *this->GetName());
		//PentosAIController->GetBlackboardComponent()->SetValueAsBool("IsOrderTaken", true);
		if (APlateActor* PlayerPlate = Cast<APlateActor>( PlayerCharacter->CarriedItem))
		{
			if (PlayerPlate->PlateItems == Order.Items)
			{
				//Same items in the plate and in the order so give the plate to the customer
				
			}
			else
			{
				//Missing items in the order
			}
			
		}
		return;
	}
	
	//If the customer have a waitpoint to go they cannot search for better one. Make a delegate to let other customer know that someone moved in the queue.
	
	if (QueueArea->IsFirstPoint(WaitPoint))
	{
		UE_LOG(LogTemp, Warning, TEXT("APentosCustomerCharacter::Interact-Queue, CustomerName: %s"), *this->GetName());
		//CurrentTable = Cast<ATableActor>(PentosAIController->GetBlackboardComponent()->GetValueAsObject("ClosestTableActor"));
		//if (CurrentTable == nullptr) return;
		
		APentosCharacter* PlayerCharacter = Cast<APentosCharacter>(InteractInstigator);
		PlayerCharacter->OrderList.Add(Order);
		CustomerAI->SetState(ECustomerState::WaitingForTable);
		//PentosAIController->GetBlackboardComponent()->SetValueAsBool("IsOrderTaken", true); // Change it to EKeyPressed?
		//QueueArea->MoveQueue();
		//QueueArea->LeaveQueue(WaitPoint);
	}
}


