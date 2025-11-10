// Copyright Kaan Kirant.


#include "Character/PentosCustomerCharacter.h"

#include "Actors/Order/OrderManager.h"
#include "Actors/Props/TableActor.h"
#include "Actors/Queue/QueueArea.h"
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
	if (OrderManager)
	{
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
		
		CurrentTable = Cast<ATableActor>(PentosAIController->GetBlackboardComponent()->GetValueAsObject("ClosestTableActor"));
		if (CurrentTable)
		{
			CurrentTable->IsAvailable = false;
			PentosAIController->GetBlackboardComponent()->SetValueAsBool("ClosestTableIsAvailable", CurrentTable->IsAvailable);
		}
	}
	if (CurrentTable)
	{
		//TODO: if already at a table -> Serve
	}
}


