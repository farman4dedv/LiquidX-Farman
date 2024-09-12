// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_DoubleJump.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"

UGA_DoubleJump::UGA_DoubleJump()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_DoubleJump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    // Get the avatar actor from the ability info
    AActor* AvatarActor = GetAvatarActorFromActorInfo();

    if (!AvatarActor)
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
        return;
    }

    Character = Cast<ACharacter>(AvatarActor);  // Get the player character
    if (Character)
    {
        UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
        if (MovementComponent)
        {
            if (MovementComponent->IsFalling())  // Ensure that the player is in the air
            {
                // Apply the second jump impulse
                MovementComponent->Velocity.Z = JumpImpulse;
                Character->LaunchCharacter(FVector(0, 0, JumpImpulse), false, true);  // Apply jump in upward direction

                //Todo, later we can add montage and wait for event to apply jump impulse from recieving tag
            }

            else
            {
                Character->Jump();  // Apply the first jump impulse
                EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
            }
        }

        Character->LandedDelegate.AddDynamic(this, &UGA_DoubleJump::OnCharacterLanded);  // Bind the OnLanded event
    }

    else
    {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
    }
}

void UGA_DoubleJump::OnCharacterLanded(const FHitResult& Hit)
{
    if (Character)
    {
        // Unbind the landing event to avoid multiple triggers
        Character->LandedDelegate.RemoveDynamic(this, &UGA_DoubleJump::OnCharacterLanded);
    }

    // End the ability once the character has landed
    EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}
