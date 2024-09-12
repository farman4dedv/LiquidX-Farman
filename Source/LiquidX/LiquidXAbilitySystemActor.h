// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "LiquidXAbilitySystemActor.generated.h"


class UGameplayEffect;
class UAbilitySystemComponent;
class ULiquidXAttributeSet;
class UGameplayAbility;

UCLASS()
class LIQUIDX_API ALiquidXAbilitySystemActor : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALiquidXAbilitySystemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*Get the ability system component of the pawn*/
	UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystemComp;
	};

	virtual void PostInitializeComponents() override;

	UPROPERTY()
	TObjectPtr<ULiquidXAttributeSet> AttributeSet;

	//Ability System Component
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystemComp;

	//Actor Attributes
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultAttributes;

	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;

	void InitializeAttributes() const;

	void AddAbilities();

	UFUNCTION(BlueprintImplementableEvent)
	void Die();

private:
	//Startup abilities
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

};
