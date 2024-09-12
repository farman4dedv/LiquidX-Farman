// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Attack.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "AbilitySystemComponent.h"

void UGA_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    // Get the avatar actor from the ability info
    AActor* AvatarActor = GetAvatarActorFromActorInfo();
    
    if (AvatarActor && CommitAbility(Handle, ActorInfo, ActivationInfo))  // Check if the ability can be committed for cooldown
    {
        // Get the start location from the avatar's current position
        FVector StartLocation = AvatarActor->GetActorLocation();

        // Calculate the end location by extending the actor's forward vector
        FVector ForwardVector = AvatarActor->GetActorForwardVector();
        FVector EndLocation = StartLocation + (ForwardVector * 200.0f);

        // Set up the parameters for the trace
        FHitResult HitResult;
        FCollisionQueryParams QueryParams;
        QueryParams.AddIgnoredActor(AvatarActor); // Ignore the avatar itself in the trace

        // Perform the line trace (single trace)
        bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams);
                        
        if (bHit)
        {
            // Get the hit actor
			AActor* HitActor = HitResult.GetActor();

            // Check if we have damage effect class to apply
            if (DamageEffect)
            {
                BP_ApplyGameplayEffectToTarget(UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(HitActor), DamageEffect, 1.0f);
            }
        }

        // Play the montage using the PlayMontageAndWait task (Later can wait for tag to recieve from Montage to trace for applying damage)
        UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, AttackMontage, 1.0f, NAME_None, false, 1.0f, 0.0f);

        // Bind callback for when the montage is finished or canceled
        MontageTask->OnCompleted.AddDynamic(this, &UGA_Attack::MontageFinished);
        MontageTask->OnBlendOut.AddDynamic(this, &UGA_Attack::MontageFinished);
        MontageTask->OnInterrupted.AddDynamic(this, &UGA_Attack::MontageFinished);
        MontageTask->OnCancelled.AddDynamic(this, &UGA_Attack::MontageFinished);

        // Activate the task
        MontageTask->ReadyForActivation();
        
    }
}

void UGA_Attack::MontageFinished()
{
	// End the ability once the montage is finished
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}
