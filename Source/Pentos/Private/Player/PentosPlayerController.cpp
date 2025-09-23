// Copyright Kaan Kirant.


#include "Player/PentosPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Character/PentosCharacter.h"
#include "Interaction/InteractInterface.h"
#include "Camera/CameraComponent.h"

APentosPlayerController::APentosPlayerController()
{
	bReplicates = true;
}

void APentosPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	if (PlayerCharacter)
		PerformTraceLine();
}

void APentosPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (GetLocalPlayer())
	{
		if (APawn* ControlledPawn = GetPawn<APawn>())
		{
			PlayerCharacter = Cast<APentosCharacter>(ControlledPawn);
		}
		AddMappingContext();
	}
}

void APentosPlayerController::OnRep_Pawn()
{
	Super::OnRep_Pawn();
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		PlayerCharacter = Cast<APentosCharacter>(ControlledPawn);
	}
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

void APentosPlayerController::PerformTraceLine()
{
	const FVector Start = PlayerCharacter->GetCamera()->GetComponentLocation();
	FVector End = Start + PlayerCharacter->GetCamera()->GetForwardVector() * 500.f;
	
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params, FCollisionResponseParams());
	DrawDebugLine(GetWorld(),Start,End, FColor::Red, false, 0.1f, 0, 1.f);
	if (!HitResult.bBlockingHit) return;
	UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *HitResult.GetActor()->GetName());
	
	LastActor = ThisActor;
	ThisActor = HitResult.GetActor();
	
	/*
	 * Line trace from player. There are several scenairos:
	 * A. Last Actor is null && This Actor is null.
	 *		-Do nothing.
	 *	B.Last Actor is null && This Actor is valid.
	 *		-Highlight and show text on this actor.
	 *	C.Last Actor is valid && this actor is null.
	 *		-Unhighlight and hide text on last actor.
	 *	D.Last actor is valid && this actor is valid. But last actor != this actor
	 *		Unhighlight and hide text on last actor && highlight and show text on this actor.
	 *	E.Last actor is valid && this actor is valid. But last actor == this actor
	 *		Do nothing.
	 */

	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			//Case B
			UE_LOG(LogTemp, Warning, TEXT("Case B"));
			ThisActor->ActivateInteractMessage();
			ThisActor->HighlightActor();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Case A"));
			// Case A - Do nothing.
		}
	}
	else // Last actor is valid
	{
		if (ThisActor == nullptr)
		{
			// Case C
			UE_LOG(LogTemp, Warning, TEXT("Case C"));
			LastActor->DeactivateInteractMessage();
			LastActor->UnHighlightActor();
		}
		else // Both actors valid
		{
			if (LastActor != ThisActor)
			{
				// Case D
				UE_LOG(LogTemp, Warning, TEXT("Case D"));
				LastActor->DeactivateInteractMessage();
				LastActor->UnHighlightActor();
				ThisActor->ActivateInteractMessage();
				ThisActor->HighlightActor();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Case E"));
				// Case E - Do nothing
			}
		}
	}
}
