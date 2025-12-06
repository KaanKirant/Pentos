// Copyright Kaan Kirant.


#include "AI/CustomerAIComponent.h"

#include "AI/PentosAIController.h"
#include "Character/PentosCustomerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"

UCustomerAIComponent::UCustomerAIComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCustomerAIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	StateTimer += DeltaTime;
	HandleState(DeltaTime);
}

void UCustomerAIComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCustomer = Cast<APentosCustomerCharacter>(GetOwner());
	if (!OwnerCustomer)
	{
		UE_LOG(LogTemp, Error, TEXT("CustomerAIComponent: Owner is not APentosCustomerCharacter!"));
	}
	if (OwnerCustomer)
	{
		AIController = Cast<APentosAIController>(OwnerCustomer->GetController());
		if (!AIController)
		{
			UE_LOG(LogTemp, Warning, TEXT("CustomerAIComponent: AIController not yet possessed at BeginPlay."));
		}
	}
}

void UCustomerAIComponent::HandleState(float DeltaTime)
{
	switch (CurrentState)
	{
	case ECustomerState::Eating:
		if (StateTimer > EatingDuration)
		{
			SetState(ECustomerState::Leaving);
		}
		break;
	default:
		break;
	}
}

void UCustomerAIComponent::SetState(const ECustomerState NewState)
{
	CurrentState = NewState;
	StateTimer = 0.f;

	switch (CurrentState)
	{
	case ECustomerState::Entering:        OnEnter_Entering(); break;
	case ECustomerState::Queuing:         OnEnter_Queuing(); break;
	case ECustomerState::WaitingForTable: OnEnter_WaitingForTable(); break;
	case ECustomerState::WalkingToTable:  OnEnter_WalkingToTable(); break;
	case ECustomerState::Eating:          OnEnter_Eating(); break;
	case ECustomerState::Leaving:         OnEnter_Leaving(); break;
	}
}

void UCustomerAIComponent::OnEnter_Entering()
{
	//Find Queue point
	if (FWaitPoint* WaitPoint = OwnerCustomer->QueueArea->GetFirstAvailableWaitPoint())
	{
		OwnerCustomer->WaitPoint = WaitPoint;
		OwnerCustomer->WaitPoint->IsAvailable = false;
		OwnerCustomer->WaitPoint->CurrentCustomer = OwnerCustomer;
		TargetLocation = WaitPoint->PointLocation;
		SetState(ECustomerState::Queuing);
	}
	// else: there was no available spot?
}

void UCustomerAIComponent::OnEnter_Queuing()
{
	//Move to queue point
	MoveCustomerTo(TargetLocation, 10.f);
	//SetState(ECustomerState::WaitingForTable);
}

void UCustomerAIComponent::OnEnter_WaitingForTable()
{
	GetAvailableTableActor();
	if (OwnerCustomer->CurrentTable != nullptr)
		SetState(ECustomerState::WalkingToTable);
}

void UCustomerAIComponent::OnEnter_WalkingToTable()
{
	OwnerCustomer->QueueArea->MoveQueue();
	MoveCustomerTo(TargetLocation, 100.f);
}

void UCustomerAIComponent::OnEnter_Eating()
{
	EatingDuration = FMath::RandRange(5.f, 12.f);
}

void UCustomerAIComponent::OnEnter_Leaving()
{
	//MoveTo Exit
	OwnerCustomer->CurrentTable->IsAvailable = true;
	OwnerCustomer->CurrentTable = nullptr;
	MoveCustomerTo(OwnerCustomer->SpawnManager->GetActorLocation());
}

void UCustomerAIComponent::MoveCustomerTo(const FVector& Location, float CustomerAcceptanceRadius)
{
	if (!OwnerCustomer)
	{
		OwnerCustomer = Cast<APentosCustomerCharacter>(GetOwner());
		if (!OwnerCustomer)
		{
			UE_LOG(LogTemp, Error, TEXT("MoveCustomerTo: No OwnerCustomer!"));
			return;
		}
	}

	if (!AIController)
	{
		APawn* Pawn = Cast<APawn>(OwnerCustomer);
		if (Pawn)
		{
			AIController = Cast<APentosAIController>(Pawn->GetController());
		}
		if (!AIController)
		{
			UE_LOG(LogTemp, Warning, TEXT("MoveCustomerTo: AIController null — cannot Move. Owner: %s"),
				   *GetNameSafe(OwnerCustomer));
			return;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("MoveCustomerTo: Target=(%s) AcceptanceRadius=%f"),
	   *Location.ToString(), CustomerAcceptanceRadius);
	FAIMoveRequest MoveReq;
	MoveReq.SetGoalLocation(Location);
	MoveReq.SetAcceptanceRadius(CustomerAcceptanceRadius);
	MoveReq.SetReachTestIncludesAgentRadius(true);
	MoveReq.SetReachTestIncludesGoalRadius(true);
	MoveReq.SetStartFromPreviousPath(false);
	MoveReq.SetAllowPartialPath(true);

	FNavPathSharedPtr NavPath;
	const FPathFollowingRequestResult Result = AIController->MoveTo(MoveReq, &NavPath);

	if (Result.Code == EPathFollowingRequestResult::Failed)
	{
		UE_LOG(LogTemp, Error, TEXT("MoveCustomerTo: MoveTo failed to start"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MoveCustomerTo: Move started (RequestID valid: %d)"), Result.MoveId.IsValid());
	}
}

void UCustomerAIComponent::OnMoveCompleted(const FPathFollowingResult& Result)
{
	if (Result.Code != EPathFollowingResult::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Move failed or aborted"));
		return;
	}

	switch (CurrentState)
	{
	case ECustomerState::WalkingToTable:
		//SetState(ECustomerState::Eating);
		break;

	case ECustomerState::Leaving:
		// reached exit
		OwnerCustomer->Destroy();
		break;

	default:
		break;
	}
}

void UCustomerAIComponent::GetAvailableTableActor()
{
	TArray<AActor*> TableActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), TableClass, TableActors);
	
	TArray<ATableActor*> AvailableTableActors;
	for (AActor* Actor : TableActors)
	{
		ATableActor* TableActor = Cast<ATableActor>(Actor);
		if (TableActor->IsAvailable)
		{
			AvailableTableActors.Add(TableActor);
		}
	}
	
	if (AvailableTableActors.Num() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("No available tables!"));
		return;
	}
	
	ATableActor* AvilableTableActor = AvailableTableActors[FMath::RandRange(0, AvailableTableActors.Num() - 1)];
	UE_LOG(LogTemp, Warning, TEXT("UCustomerAIComponent::GetAvailableTableActor, TableCount: %d"), AvailableTableActors.Num());
	
	if (AvilableTableActor)
	{
		OwnerCustomer->CurrentTable = AvilableTableActor;
		OwnerCustomer->CurrentTable->IsAvailable = false;
		TargetLocation = AvilableTableActor->GetActorLocation();
	}
}

