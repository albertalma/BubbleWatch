// Copyright Albert Alma Ltd.

#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
    m_fHealth = m_fMaxHealth;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

float UHealthComponent::DecreaseHealth(float DecreaseValue)
{
    m_fHealth -= DecreaseValue;
    if (m_fHealth <= 0)
    {
        OnHealthBelowZero.Broadcast();
        m_fHealth = 0;
    }
    return m_fHealth;
}