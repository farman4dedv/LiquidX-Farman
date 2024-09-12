// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageExecCalculation.h"
#include "LiquidX/LiquidXAttributeSet.h"

UDamageExecCalculation::UDamageExecCalculation()
{
    // Capture the Damage attribute from the source
    RelevantAttributesToCapture.Add(FGameplayEffectAttributeCaptureDefinition(ULiquidXAttributeSet::GetDamageAttribute(), EGameplayEffectAttributeCaptureSource::Source, true));

    // Capture the Armor attribute from the target
    RelevantAttributesToCapture.Add(FGameplayEffectAttributeCaptureDefinition(ULiquidXAttributeSet::GetArmorAttribute(), EGameplayEffectAttributeCaptureSource::Target, true));

    // Capture the Health attribute from the target to modify it
    RelevantAttributesToCapture.Add(FGameplayEffectAttributeCaptureDefinition(ULiquidXAttributeSet::GetHealthAttribute(), EGameplayEffectAttributeCaptureSource::Target, true));
}

void UDamageExecCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    // Get the ability system component of both the source and target
    UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
    UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();

    // Attributes to capture
    float BaseDamage = 0.0f;
    float Armor = 0.0f;
    float Health = 0.0f;

    // Capture the base damage from the source
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FGameplayEffectAttributeCaptureDefinition(ULiquidXAttributeSet::GetDamageAttribute(), EGameplayEffectAttributeCaptureSource::Source, true), FAggregatorEvaluateParameters(), BaseDamage);

    // Capture the armor from the target
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FGameplayEffectAttributeCaptureDefinition(ULiquidXAttributeSet::GetArmorAttribute(), EGameplayEffectAttributeCaptureSource::Target, true), FAggregatorEvaluateParameters(), Armor);

    // Capture the health from the target
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FGameplayEffectAttributeCaptureDefinition(ULiquidXAttributeSet::GetHealthAttribute(), EGameplayEffectAttributeCaptureSource::Target, true), FAggregatorEvaluateParameters(), Health);

    // Armor-based damage reduction formula similar to DotA 2
    float ArmorConstant = 15.0f; 
    float DamageReductionFactor = Armor / (Armor + ArmorConstant);  // Armor reduces damage

    // Final damage after reduction
    float FinalDamage = BaseDamage * (1.0f - DamageReductionFactor);

    // Apply the final damage to the target's health
    float NewHealth = Health - FinalDamage;

    // Ensure health doesn't go below 0
    NewHealth = FMath::Max(0.0f, NewHealth);

    // Output the new health value, reducing health by the damage dealt
    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(ULiquidXAttributeSet::GetHealthAttribute(), EGameplayModOp::Override, NewHealth));
}