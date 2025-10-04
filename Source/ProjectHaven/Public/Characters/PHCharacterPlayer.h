// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PHCharacterBase.h"
#include "PHCharacterPlayer.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class PROJECTHAVEN_API APHCharacterPlayer : public APHCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APHCharacterPlayer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
