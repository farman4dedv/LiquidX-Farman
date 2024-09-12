// Fill out your copyright notice in the Description page of Project Settings.


#include "LiquidXPlayerState.h"
#include "AbilitySystem/LiquidXAbilitySystemComponent.h"
#include "LiquidXAttributeSet.h"
#include "LiquidXCharacter.h"

ALiquidXPlayerState::ALiquidXPlayerState()
{
	// Create Ability System Component
	AbilitySystemComponent = CreateDefaultSubobject<ULiquidXAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->ReplicationMode = EGameplayEffectReplicationMode::Minimal;

	// Create Attribute Set
	AttributeSet = CreateDefaultSubobject<ULiquidXAttributeSet>("AttributeSet");
}

void ALiquidXPlayerState::BeginPlay()
{
	Super::BeginPlay();

	// Bind Health Changed Delegate
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			AttributeSet->GetHealthAttribute()).AddLambda(
				[this](const FOnAttributeChangeData& Data)
				{
					float Health = Data.NewValue;

					ALiquidXCharacter* LiquidXCharacter = Cast<ALiquidXCharacter>(GetPawn());

					if (LiquidXCharacter)
					{
						LiquidXCharacter->UpdateHealthWidget(GetHealth());

						if (Health <= 0.f && HasAuthority())
						{
							LiquidXCharacter->Die();
						}
					}
				}
			);
	}
}

UAbilitySystemComponent* ALiquidXPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

float ALiquidXPlayerState::GetHealth()
{
	if (!AttributeSet)
	{
		return 0.f;
	}

	return AttributeSet->GetHealth() / AttributeSet->GetMaxHealth();
}
