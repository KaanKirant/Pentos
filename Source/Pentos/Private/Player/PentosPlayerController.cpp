// Copyright Kaan Kirant.


#include "Player/PentosPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

APentosPlayerController::APentosPlayerController()
{
	bReplicates = true;
}

void APentosPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (GetLocalPlayer())
	{
		AddMappingContext();
	}
}

void APentosPlayerController::OnRep_Pawn()
{
	Super::OnRep_Pawn();
	AddMappingContext();
}

void APentosPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APentosPlayerController::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APentosPlayerController::Look);
}

void APentosPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void APentosPlayerController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookingVector = InputActionValue.Get<FVector2D>();
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddControllerYawInput(LookingVector.X);
		ControlledPawn->AddControllerPitchInput(LookingVector.Y);
	}
}

void APentosPlayerController::AddMappingContext()
{
	check(PentosContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	
	check(Subsystem);
	Subsystem->AddMappingContext(PentosContext, 0);
}
