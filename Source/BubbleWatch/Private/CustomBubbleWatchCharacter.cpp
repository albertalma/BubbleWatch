// Copyright Albert Alma Ltd.

#include "CustomBubbleWatchCharacter.h"
#include "Bubble/BubbleProjectile.h"
#include "Pool/BubblePool.h"
#include "Components/HealthComponent.h"

ACustomBubbleWatchCharacter::ACustomBubbleWatchCharacter()
{

}

void ACustomBubbleWatchCharacter::BeginPlay()
{
    Super::BeginPlay();
    m_pBubblePool = NewObject<UBubblePool>();
    m_pBubblePool->InitialisePool(GetWorld(), BubbleProjectileClass, MaxProjectiles);

    m_pHealthComponent = Cast< UHealthComponent>(GetComponentByClass(UHealthComponent::StaticClass()));
    ensure(m_pHealthComponent);
}

void ACustomBubbleWatchCharacter::SpawnProjectile(UWorld* const World, const FRotator SpawnRotation, const FVector SpawnLocation, FActorSpawnParameters ActorSpawnParams)
{
    ABubbleProjectile* bubbleProjectile = m_pBubblePool->GetBubble();
    bubbleProjectile->SetActorLocationAndRotation(SpawnLocation, SpawnRotation);
    bubbleProjectile->Enable();
}

float ACustomBubbleWatchCharacter::GetCurrentHealth()
{
    return m_pHealthComponent->GetCurrentHealth();
}

float ACustomBubbleWatchCharacter::GetMaxHealth()
{
    return m_pHealthComponent->GetMaxHealth();
}

EColor ACustomBubbleWatchCharacter::GetCurrentBubble()
{
    return m_pBubblePool->GetCurrentBubbleColor();
}

EColor ACustomBubbleWatchCharacter::GetNextBubble()
{
    return m_pBubblePool->GetNextBubbleColor();
}

