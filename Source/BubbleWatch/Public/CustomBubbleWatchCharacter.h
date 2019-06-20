// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BubbleWatchCharacter.h"
#include "CustomBubbleWatchCharacter.generated.h"

struct FActorSpawnParameters;

UCLASS()
class BUBBLEWATCH_API ACustomBubbleWatchCharacter : public ABubbleWatchCharacter
{
	GENERATED_BODY()
	
protected:

    virtual void SpawnProjectile(UWorld* const World, const FRotator SpawnRotation, const FVector SpawnLocation, FActorSpawnParameters ActorSpawnParams) override;

public:

    /** Projectile class to spawn */
    UPROPERTY(EditDefaultsOnly, Category = Projectile)
    TSubclassOf<class ABubbleProjectile> BubbleProjectileClass;
};
