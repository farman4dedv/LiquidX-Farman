// Fill out your copyright notice in the Description page of Project Settings.


#include "LiquidXAbilitySystemComponent.h"

void ULiquidXAbilitySystemComponent::AddAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	// Iterate over the array of abilities and give each one to the owner of the ability system component
	for (TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		GiveAbility(AbilitySpec);
	}
}