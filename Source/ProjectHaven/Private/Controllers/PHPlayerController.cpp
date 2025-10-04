// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/PHPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


void APHPlayerController::InitializeEnhancedInput()
{
	InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	FInputModeGameAndUI GameAndUiInputMode;
	SetInputMode(GameAndUiInputMode);

	if (InputSubsystem && StandardInputMappingContext)
	{
		InputSubsystem->AddMappingContext(StandardInputMappingContext, 0);
	}
	
}

void APHPlayerController::HandleAdjustZoomAction()
{
	//Extends or shortens the Owning Player Actors Camera Spring Arm.
}

void APHPlayerController::HandleStandardAction()
{
	//Handles Most of the Actions in Games
	//Dependent on what is clicked.
}

void APHPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	/*All Mapped Input Options*/

	//EnhancedInputComponent->BindAction(StandardAction, ETriggerEvent::Triggered, this, &ATimberPlayerController::UsePrimaryAbility);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APHPlayerController::HandleMoveAction);
	EnhancedInputComponent->BindAction(AdjustZoomAction, ETriggerEvent::Triggered, this, &APHPlayerController::HandleAdjustZoomAction);
	EnhancedInputComponent->BindAction(StandardAction, ETriggerEvent::Triggered, this, &APHPlayerController::HandleStandardAction);
}

void APHPlayerController::HandleMoveAction()
{
	//Moves the Character on a plane. No Vertical movement.
}
