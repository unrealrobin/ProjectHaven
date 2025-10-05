// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/PHAttributeSet.h"
#include "Net/UnrealNetwork.h"

void UPHAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	// Used for predictablity
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPHAttributeSet, Health, OldValue);
}

void UPHAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UPHAttributeSet, Health, COND_None, REPNOTIFY_Always);
}
