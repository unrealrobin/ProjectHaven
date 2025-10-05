// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/PHPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Characters/PHPlayerCharacter.h"


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

void APHPlayerController::HandleAdjustZoomAction(const FInputActionValue& ActionValue)
{
	//Extends or shortens the Owning Player Actors Camera Spring Arm.
	//TODO::Needs work to make much smoother.
	TWeakObjectPtr PlayerCharacter = Cast<APHPlayerCharacter>(GetPawn());
	if (PlayerCharacter.IsValid() && PlayerCharacter->CameraComponent)
	{
		//Use Values to Adjust Zoom. Clamp as required.
		float PinchScaleValue = FMath::Clamp(ActionValue.Get<float>(), 0.5f, 3.0f);
		float PinchDelta = PinchScaleValue / PreviousPinchValue;
		if (PinchDelta > 0.2f )
		{
			float CurrentCameraFOV = PlayerCharacter->CameraComponent->FieldOfView; 
			PlayerCharacter->CameraComponent->FieldOfView = FMath::Clamp(CurrentCameraFOV * PinchDelta, 60.0f, 160.0f);
			
			PreviousPinchValue = PinchScaleValue;
			UE_LOG(LogTemp, Warning, TEXT("Camera Field Of View: %f, Pinch Value: %f. Pinch Delta: %f"), PlayerCharacter->CameraComponent->FieldOfView, PinchScaleValue, PinchDelta);
		}
	}
}

void APHPlayerController::HandleMoveAction(const FInputActionValue& ActionValue)
{
	//Moves the Character on a plane. No Vertical movement.
	if (LastMoveDelta == FVector2D::ZeroVector)
	{
		LastMoveDelta = ActionValue.Get<FVector2D>();
	}
	else
	{
		TWeakObjectPtr PlayerCharacter = Cast<APHPlayerCharacter>(GetPawn());
		if (PlayerCharacter.IsValid())
		{
			FVector ActorLocation = PlayerCharacter->GetActorLocation();
			FVector2D LocationOffset = ActionValue.Get<FVector2D>();
			FVector NewActorLocation = FVector(ActorLocation.X + LocationOffset.X, ActorLocation.Y + LocationOffset.Y, ActorLocation.Z);
			PlayerCharacter->SetActorLocation(NewActorLocation);
		}
		LastMoveDelta = ActionValue.Get<FVector2D>() - LastMoveDelta;
	}

	//Swipe up, right, left, down moves camera actor up, right, left, down
}

void APHPlayerController::HandleMoveActionComplete(const FInputActionValue& InputActionValue)
{
}

void APHPlayerController::HandleStandardAction(const FInputActionValue& ActionValue)
{
	//Handles Most of the Actions in Games
	//Dependent on what is clicked.

	//Single Touch Tap
}

void APHPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComponent)
	{

		/*All Mapped Input Options*/

		//EnhancedInputComponent->BindAction(StandardAction, ETriggerEvent::Triggered, this, &ATimberPlayerController::UsePrimaryAbility);
		EnhancedInputComponent->BindAction(PinchZoomActionTouch, ETriggerEvent::Triggered, this, &APHPlayerController::HandleAdjustZoomAction);
		EnhancedInputComponent->BindAction(MoveActionTouch, ETriggerEvent::Triggered, this, &APHPlayerController::HandleMoveAction);
		EnhancedInputComponent->BindAction(MoveActionTouch, ETriggerEvent::Completed, this, &APHPlayerController::HandleMoveActionComplete);
		EnhancedInputComponent->BindAction(StandardActionTouch, ETriggerEvent::Triggered, this, &APHPlayerController::HandleStandardAction);
	}
}



