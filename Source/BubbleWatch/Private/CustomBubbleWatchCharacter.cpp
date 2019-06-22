// Copyright Albert Alma Ltd.

#include "CustomBubbleWatchCharacter.h"
#include "Bubble/BubbleProjectile.h"
#include "Pool/BubblePool.h"

ACustomBubbleWatchCharacter::ACustomBubbleWatchCharacter()
{

}

void ACustomBubbleWatchCharacter::BeginPlay()
{
    Super::BeginPlay();
    m_pBubblePool = NewObject<UBubblePool>();
    m_pBubblePool->InitialisePool(GetWorld(), BubbleProjectileClass, MaxProjectiles);
}

void ACustomBubbleWatchCharacter::SpawnProjectile(UWorld* const World, const FRotator SpawnRotation, const FVector SpawnLocation, FActorSpawnParameters ActorSpawnParams)
{
    ABubbleProjectile* bubbleProjectile = m_pBubblePool->GetBubble();
    bubbleProjectile->SetActorLocationAndRotation(SpawnLocation, SpawnRotation);
    bubbleProjectile->Enable();
}
