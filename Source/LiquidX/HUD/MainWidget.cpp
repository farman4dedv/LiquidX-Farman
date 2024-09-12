// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"

#include "Components/ProgressBar.h"

void UMainWidget::UpdateHealthBar(float HealthPercent)
{
    if (HealthProgressBar)
    {
        HealthProgressBar->SetPercent(HealthPercent);
    }
}