// Copyright Albert Alma Ltd.

#include "CustomBubbleWatchCharacter.h"
#include "Bubble/BubbleProjectile.h"
#include "Pool/BubbleProjectilePool.h"
#include "Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Bubble_fwd.h"

ACustomBubbleWatchCharacter::ACustomBubbleWatchCharacter()
{
}

void ACustomBubbleWatchCharacter::BeginPlay()
{
    Super::BeginPlay();
    m_pBubbleProjectilePool = NewObject<UBubbleProjectilePool>();
    m_pBubbleProjectilePool->InitialisePool(GetWorld(), BubbleProjectileClass, MaxProjectiles, GetActorLocation(), GetActorRotation());

    m_pHealthComponent = Cast<UHealthComponent>(GetComponentByClass(UHealthComponent::StaticClass()));
    if (ensure(m_pHealthComponent))
    {
        m_pHealthComponent->OnHealthBelowZero.AddUniqueDynamic(this, &ACustomBubbleWatchCharacter::OnCharacterDead);
    }
}

void ACustomBubbleWatchCharacter::SpawnProjectile(UWorld* const World, const FRotator SpawnRotation, const FVector SpawnLocation, FActorSpawnParameters ActorSpawnParams)
{
    ABubbleProjectile* bubbleProjectile =  (ABubbleProjectile*) m_pBubbleProjectilePool->PopBubble();
    bubbleProjectile->SetActorLocation(SpawnLocation);
    bubbleProjectile->SetActorRotation(SpawnRotation);
    IBubbleInterface::Execute_Enable(bubbleProjectile);
}

float ACustomBubbleWatchCharacter::GetCurrentHealth() const
{
    return m_pHealthComponent->GetCurrentHealth();
}

float ACustomBubbleWatchCharacter::GetMaxHealth() const
{
    return m_pHealthComponent->GetMaxHealth();
}

EColor ACustomBubbleWatchCharacter::GetCurrentBubble() const
{
    return m_pBubbleProjectilePool->GetCurrentBubbleColor();
}

EColor ACustomBubbleWatchCharacter::GetNextBubble() const
{
    return m_pBubbleProjectilePool->GetNextBubbleColor();
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
    UWorld* TheWorld = GetWorld();
    UGameplayStatics::OpenLevel(GetWorld(), "GameOver");
}