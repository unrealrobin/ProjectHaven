// Fill out your copyright notice in the Description page of Project Settings.


#include "PHPlayerState.h"

#include "GAS/PHAbilitySystemComponent.h"
#include "GAS/PHAttributeSet.h"

APHPlayerState::APHPlayerState()
{
	ASC = CreateDefaultSubobject<UPHAbilitySystemComponent>("Ability System Component");
	ASC->SetIsReplicated(true);
	ASC->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UPHAttributeSet>("Attribute Set");
}

UAbilitySystemComponent* APHPlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}

void APHPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority() && ASC)
	{
		//Owner Actor of the ASC is the Player State
		//Avatar Actor set to this for now, as there is no character for the player.
		ASC->InitAbilityActorInfo(this, this);
	}
}
