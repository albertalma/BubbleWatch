// Copyright Albert Alma Ltd.

#include "CustomBubbleWatchCharacter.h"
#include "Bubble/BubbleProjectile.h"
#include "Pool/BubblePool.h"
#include "Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

ACustomBubbleWatchCharacter::ACustomBubbleWatchCharacter()
{

}

void ACustomBubbleWatchCharacter::BeginPlay()
{
    Super::BeginPlay();
    m_pBubblePool = NewObject<UBubblePool>();
    m_pBubblePool->InitialisePool(GetWorld(), BubbleProjectileClass, MaxProjectiles, GetActorLocation(), GetActorRotation());

    m_pHealthComponent = Cast<UHealthComponent>(GetComponentByClass(UHealthComponent::StaticClass()));
    if (ensure(m_pHealthComponent))
    {
        m_pHealthComponent->OnHealthBelowZero.AddUniqueDynamic(this, &ACustomBubbleWatchCharacter::OnCharacterDead);
    }
}

void ACustomBubbleWatchCharacter::SpawnProjectile(UWorld* const World, const FRotator SpawnRotation, const FVector SpawnLocation, FActorSpawnParameters ActorSpawnParams)
{
    ABubbleProjectile* bubbleProjectile = m_pBubblePool->GetBubble();
    bubbleProjectile->SetActorLocation(SpawnLocation);
    bubbleProjectile->SetActorRotation(SpawnRotation);
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

float ACustomBubbleWatchCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
    if (DamageSound != nullptr)
    {
        UGameplayStatics::PlaySoundAtLocation(this, DamageSound, GetActorLocation());
    }
    m_pHealthComponent->DecreaseHealth(Damage);
    return Damage;
}

void ACustomBubbleWatchCharacter::OnCharacterDead()
{
    if (LoseSound != nullptr)
    {
        UGameplayStatics::PlaySoundAtLocation(this, LoseSound, GetActorLocation());
    }
    UWorld* TheWorld = GetWorld();
    UGameplayStatics::OpenLevel(GetWorld(), "GameOver");
}