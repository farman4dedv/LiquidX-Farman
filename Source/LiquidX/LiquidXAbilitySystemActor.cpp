// Fill out your copyright notice in the Description page of Project Settings.


#include "LiquidXAbilitySystemActor.h"
#include "LiquidXAttributeSet.h"
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"

// Sets default values
ALiquidXAbilitySystemActor::ALiquidXAbilitySystemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Replicate actor
	SetReplicates(true);

	//Create Ability System Subobject and replicates it
	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	AbilitySystemComp->SetIsReplicated(true);
	AbilitySystemComp->ReplicationMode = EGameplayEffectReplicationMode::Minimal;

	AttributeSet = CreateDefaultSubobject<ULiquidXAttributeSet>("AttributeSet");

}

// Called when the game starts or when spawned
void ALiquidXAbilitySystemActor::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComp)
	{
		//Bind Health Changed Delegate
		AbilitySystemComp->GetGameplayAttributeValueChangeDelegate(
			AttributeSet->GetHealthAttribute()).AddLambda(
				[this](const FOnAttributeChangeData& Data)
				{
					float Health = Data.NewValue;

					if (Health <= 0.f && HasAuthority())
					{
						Die();
					}
				}
			);
	}
	
}

void ALiquidXAbilitySystemActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	InitializeAttributes();

	//for future actors to add abilities
	AddAbilities();
}

void ALiquidXAbilitySystemActor::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	if (GameplayEffectClass)
	{
		FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
		ContextHandle.AddSourceObject(this);
		const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
		GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
	}
}

void ALiquidXAbilitySystemActor::InitializeAttributes() const
{
	ApplyEffectToSelf(DefaultAttributes, 1.f);
}

void ALiquidXAbilitySystemActor::AddAbilities()
{
	if (AbilitySystemComp)
	{
		for (TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
		{
			AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(AbilityClass, 1));
		}
	}
}