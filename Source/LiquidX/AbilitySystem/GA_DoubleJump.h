// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_DoubleJump.generated.h"

/**
 * 
 */
UCLASS()
class LIQUIDX_API UGA_DoubleJump : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
    UGA_DoubleJump();

    ACharacter* Character;

    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

    // Event for when the character has landed
    UFUNCTION()
    void OnCharacterLanded(const FHitResult& Hit);

protected:
    float JumpImpulse = 1200.0f;
};
