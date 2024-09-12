// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "LiquidXAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class LIQUIDX_API ULiquidXAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	void AddAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
};
