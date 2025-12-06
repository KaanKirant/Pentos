// Copyright Kaan Kirant.


#include "AI/PentosAIController.h"

#include "AI/CustomerAIComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Character/PentosCustomerCharacter.h"

APentosAIController::APentosAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackboardComponent");
	check(Blackboard);
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComponent");
	check(BehaviorTreeComponent);
	
}

void APentosAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void APentosAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	APentosCustomerCharacter* Customer = Cast<APentosCustomerCharacter>(GetPawn());
	if (!Customer) return;

	if (UCustomerAIComponent* Comp = Customer->FindComponentByClass<UCustomerAIComponent>())
	{
		Comp->OnMoveCompleted(Result);
	}
}