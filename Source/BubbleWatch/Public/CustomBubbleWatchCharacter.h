// Copyright Albert Alma Ltd.

#pragma once

#include "CoreMinimal.h"
#include "BubbleWatchCharacter.h"
#include "CustomBubbleWatchCharacter.generated.h"

struct FActorSpawnParameters;
class UBubblePool;

UCLASS()
class BUBBLEWATCH_API ACustomBubbleWatchCharacter : public ABubbleWatchCharacter
{
	GENERATED_BODY()

public:

    ACustomBubbleWatchCharacter();
	
protected:
    virtual void BeginPlay() override;

    virtual void SpawnProjectile(UWorld* const World, const FRotator SpawnRotation, const FVector SpawnLocation, FActorSpawnParameters ActorSpawnParams) override;

public:

    /** Projectile class to spawn */
    UPROPERTY(EditDefaultsOnly, Category = Projectile)
    TSubclassOf<class ABubbleProjectile> BubbleProjectileClass;

    UPROPERTY(EditAnyWhere, Category = Projectile)
    int MaxProjectiles = 20.0f;

private:

    UBubblePool* m_pBubblePool;
};
