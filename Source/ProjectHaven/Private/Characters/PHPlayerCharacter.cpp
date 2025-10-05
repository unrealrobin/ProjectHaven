// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PHPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
APHPlayerCharacter::APHPlayerCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	RootComponent = SpringArmComponent;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(RootComponent);
}	

// Called when the game starts or when spawned
void APHPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APHPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

