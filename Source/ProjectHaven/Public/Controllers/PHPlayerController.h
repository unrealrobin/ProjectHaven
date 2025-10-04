// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "PHPlayerController.generated.h"

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
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<UInputAction> AdjustZoomAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<UInputAction> StandardAction;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Input")
	UInputMappingContext* StandardInputMappingContext;

private:
	
	UPROPERTY()
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystem;
	void SetupInputComponent();
	void InitializeEnhancedInput();

	/* Input Delegates that get fired when an Input Triggers*/
	void HandleAdjustZoomAction();
	void HandleStandardAction();
	void HandleMoveAction();
};
