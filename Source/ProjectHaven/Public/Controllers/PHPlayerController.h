// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "PHPlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class UEnhancedInputLocalPlayerSubsystem;
/**
 * 
 */


UCLASS()
class PROJECTHAVEN_API APHPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	/*Input Actions created in Editor & Set on the Controller*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<UInputAction> MoveActionTouch;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<UInputAction> PinchZoomActionTouch;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<UInputAction> StandardActionTouch;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	UInputMappingContext* StandardInputMappingContext;

private:
	/* Subsystem that Stores our Input Mapping Contexts*/
	UPROPERTY()
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystem;
	
	void SetupInputComponent() override;
	void InitializeEnhancedInput();
	

	/* Input Delegates that get fired when an Input Triggers*/
	void HandleAdjustZoomAction(const FInputActionValue& ActionValue);
	void HandleStandardAction(const FInputActionValue& ActionValue);
	void HandleMoveAction(const FInputActionValue& ActionValue);
	void HandleMoveActionComplete(const FInputActionValue& InputActionValue);

	/* Zoom Data*/
	float PreviousPinchValue = 1.0f;
	float ZoomSensitivity = 0.2f;

	/*Move Data*/
	FVector2D LastMoveDelta = FVector2D::ZeroVector;
};
