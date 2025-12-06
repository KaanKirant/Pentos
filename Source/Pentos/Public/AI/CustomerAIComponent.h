// Copyright Kaan Kirant.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AI/CustomerStates.h"
#include "Actors/Props/TableActor.h"
#include "CustomerAIComponent.generated.h"


struct FPathFollowingResult;
class APentosAIController;
class APentosCustomerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PENTOS_API UCustomerAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCustomerAIComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetState(const ECustomerState NewState);
	void MoveCustomerTo(const FVector& Location, float CustomerAcceptanceRadius = 10.f);
	void OnMoveCompleted(const FPathFollowingResult& Result);
	
	UPROPERTY()
	APentosAIController* AIController;
protected:
	virtual void BeginPlay() override;

private:
	void HandleState(float DeltaTime);

	void OnEnter_Entering();
	void OnEnter_Queuing();
	void OnEnter_WaitingForTable();
	void OnEnter_WalkingToTable();
	void OnEnter_Eating();
	void OnEnter_Leaving();

	void GetAvailableTableActor();

	UPROPERTY()
	APentosCustomerCharacter* OwnerCustomer;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ATableActor> TableClass;

	FVector TargetLocation;
	
	ECustomerState CurrentState;
	float StateTimer;
	float EatingDuration;
};
