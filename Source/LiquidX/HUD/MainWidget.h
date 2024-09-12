// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class LIQUIDX_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    // Function to update the health bar
    UFUNCTION(BlueprintCallable, Category = "Health")
    void UpdateHealthBar(float HealthPercent);

protected:
    // Progress bar reference to bind in the editor
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* HealthProgressBar;
};
