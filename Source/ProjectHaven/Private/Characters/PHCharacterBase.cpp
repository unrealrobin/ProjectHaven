// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PHCharacterBase.h"

#include "GAS/PHAbilitySystemComponent.h"
#include "GAS/PHAttributeSet.h"


// Sets default values
APHCharacterBase::APHCharacterBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APHCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void APHCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

