// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "DamageExecCalculation.generated.h"

/**
 * 
 */
UCLASS()
class LIQUIDX_API UDamageExecCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	UDamageExecCalculation();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
