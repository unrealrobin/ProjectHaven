// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "PHPlayerState.generated.h"


class UPHAttributeSet;
class UPHAbilitySystemComponent;


/**
 * 
 */
UCLASS()
class PROJECTHAVEN_API APHPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

	APHPlayerState();

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability System")
	TObjectPtr<UPHAbilitySystemComponent> ASC = nullptr;

	UPROPERTY()
	TObjectPtr<UPHAttributeSet> AttributeSet;
};
