// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomBubbleWatchCharacter.h"
#include "BubbleProjectile.h"

void ACustomBubbleWatchCharacter::SpawnProjectile(UWorld* const World, const FRotator SpawnRotation, const FVector SpawnLocation, FActorSpawnParameters ActorSpawnParams)
{
    ABubbleProjectile* bubbleProjectile = World->SpawnActor<ABubbleProjectile>(BubbleProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
    ensure(bubbleProjectile);
}
