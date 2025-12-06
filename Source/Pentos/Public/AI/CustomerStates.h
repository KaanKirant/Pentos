// Copyright Kaan Kirant.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ECustomerState : uint8
{
	Entering,
	Queuing,
	WaitingForTable,
	WalkingToTable,
	Eating,
	Leaving
};

/**
 * 
 */
class PENTOS_API CustomerStates
{
public:
	CustomerStates();
	~CustomerStates();
};
