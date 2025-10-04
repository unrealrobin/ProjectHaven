

# Character Composition

1. Characters are made of 2 parts.
   2. Owner Actor - Holds all the State for Actor **(Player State)**
   3. Avatar Actor - The physical representation of the Actors.
   4. In Our Game there is no physical representation besides for Owned Land.
4. All Characters that need to utilize or recieve GameplayAbilities, Attributes, or Gameplay effects must have an actor that implements the **UAbilitySystemComponent**
5. UAbilitySystemComponent is the root component that handles all interactions.
   6. This is an Actor Component.
7. Each Character Also has an Attribute Set (List of Attributes)
   8. Currency Amount
   9. Soldier Spawn Rates
   10. Land Owned
   11. Cities Built
12. Both the Owner Actor and the Avatar Actor need to implement the IABilitySystemInterface
    13. This Interface has 1 function that needs to be overwritten.
    14. GetAbilitySystemComponent() -> Returns a pointer to its ASC (Ability System Component).
15. The Ability System Component Holds:
    16. Active Gameplay Abilities inside FActiveGameplayEffectsContainer (Gameplay Tags)
    17. ActivateableAbilities inside FActiveGameplayAbilitySpecContainer (Gameplay Tags)
        18. When iterating over there containers make sure to use ABILITYLIST_SCOPE_LOCK();
            19. This ensures we dont make changes to the list while iterating.

# Replication Modes
1. Full - Every gameplay Effect is replicated to every client.
2. Mixed - Multiplayer - Gameplay Effects are only replicated to the Owning Client.Only GameplayTags and Gameplay Cues are replicated to Everyone.
3. Minimal - Multiplayer - Gameplay Effects are never replicated to anyone. Only Gameplay Tags and Gameplay Cues.

** Mixed Replication Mode expects the OwnerActor to be the Controller. PlayerStates Owner is the Controller by default but characters is not.

# Attributes
1. Attributes are defined by the Struct FGameplayAttributeData. These are all values that belong to an actor.
2. Attributes should generally only be modified by GameplayEffects, so that the ASC can predict the changes.
3. Attributes live in an AttributeSet.

## Derived Atttributes
1. Attributes that rely on other attributes.
2. Use an Infinite GameplayEffect with one or more Attribute Base of MMC Modifiers.

# Attribute Set
1. Sublass from UAttributeSet
2. Creating the Attribute Set in an OwnerActors Constructor automatically registers it with the ASC.
   Attributes can only be defined in C++ in the AttributeSet's header file. It is recommended to add this block of macros to the top of every AttributeSet header file. It will automatically generate getter and setter functions for your Attributes.

// Uses macros from AttributeSet.h
```
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) 
```
A replicated health attribute would be defined like this:

```
UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
FGameplayAttributeData Health;
ATTRIBUTE_ACCESSORS(UGDAttributeSetBase, Health)
````
Also define the OnRep function in the header:

```
UFUNCTION()
virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

```
The .cpp file for the AttributeSet should fill in the OnRep function with the GAMEPLAYATTRIBUTE_REPNOTIFY macro used by the prediction system:
```
void UGDAttributeSetBase::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
GAMEPLAYATTRIBUTE_REPNOTIFY(UGDAttributeSetBase, Health, OldHealth);
}

```
Finally, the Attribute needs to be added to GetLifetimeReplicatedProps:
```
void UGDAttributeSetBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGDAttributeSetBase, Health, COND_None, REPNOTIFY_Always);
}
```
REPNOTIFY_Always tells the OnRep function to trigger if the local value is already equal to the value being repped down from the Server (due to prediction). By default it won't trigger the OnRep function if the local value is the same as the value being repped down from the Server.

If the Attribute is not replicated like a Meta Attribute, then the OnRep and GetLifetimeReplicatedProps steps can be skipped.