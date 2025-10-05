// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/PHPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Characters/PHPlayerCharacter.h"


void APHPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;

	OwnedPlayerCharacter = Cast<APHPlayerCharacter>(GetPawn());
}

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

void APHPlayerController::HandleAdjustZoomAction(const FInputActionValue& ActionValue)
{
	const float PinchScale = ActionValue.Get<float>(); // >1 = fingers apart, <1 = together
	if (!IsValid(OwnedPlayerCharacter)) return;

	UCameraComponent* Camera = OwnedPlayerCharacter->CameraComponent;
	if (!Camera) return;

	float CurrentFOV = Camera->FieldOfView;

	// Lower sensitivity = slower zoom (try 0.05f–0.15f for touch)
	constexpr float ZoomSensitivity = 0.08f;

	// Apply zoom more gently
	const float AdjustedScale = 1.0f + (PinchScale - 1.0f) * ZoomSensitivity;
	float NewFOV = CurrentFOV / AdjustedScale;

	// Clamp to safe range
	NewFOV = FMath::Clamp(NewFOV, 60.f, 170.f);

	Camera->SetFieldOfView(NewFOV);
}

void APHPlayerController::HandleStandardAction(const FInputActionValue& ActionValue)
{
	//Handles Most of the Actions in Games
	//Dependent on what is clicked.

	//Single Touch Tap
}

void APHPlayerController::HandleMoveAction(const FInputActionValue& ActionValue)
{
	const FVector2D CurrScreenTouchPos = ActionValue.Get<FVector2D>();

	// First frame setup
	if (PrevScreenTouchPos == FVector2D::ZeroVector)
	{
		PrevScreenTouchPos = CurrScreenTouchPos;
		return;
	}

	// Screen delta (in pixels)
	const FVector2D ScreenDelta = CurrScreenTouchPos - PrevScreenTouchPos;
	PrevScreenTouchPos = CurrScreenTouchPos;

	if (ScreenDelta.IsNearlyZero()) return;

	if (!IsValid(OwnedPlayerCharacter) || !PlayerCameraManager) return;

	// Get camera rotation (we only need Yaw)
	const float Yaw = PlayerCameraManager->GetCameraRotation().Yaw;

	// Build horizontal movement axes from yaw
	const FVector Forward = FRotationMatrix(FRotator(0.f, Yaw, 0.f)).GetUnitAxis(EAxis::X);
	const FVector Right   = FRotationMatrix(FRotator(0.f, Yaw, 0.f)).GetUnitAxis(EAxis::Y);

	// Sensitivity — tune this
	const float Height = PlayerCameraManager->GetCameraLocation().Z;
	const float PanSpeed = Height * 0.00035f; // try 0.0005–0.002 depending on zoom

	// Dragging up moves camera forward (world “up”)
	const FVector MoveDelta =
		(-ScreenDelta.X * Right + ScreenDelta.Y * Forward) * PanSpeed;

	OwnedPlayerCharacter->AddActorWorldOffset(MoveDelta, false);
}

void APHPlayerController::HandleMoveActionComplete(const FInputActionValue& InputActionValue)
{
	
	PrevScreenTouchPos = FVector2D::ZeroVector;
	PrevWorldTouchPos = FVector::ZeroVector;

	UE_LOG(LogTemp, Warning, TEXT("Touch Move Action Complete"));
}

FVector APHPlayerController::GetWorldPosFromScreenPos(FVector2D ScreenPos)
{
	FVector WorldLocation = FVector::ZeroVector;
	FVector WorldDirection = FVector::ZeroVector;
	DeprojectScreenPositionToWorld(ScreenPos.X, ScreenPos.Y, WorldLocation, WorldDirection);

	return WorldLocation;
}


