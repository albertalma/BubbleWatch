// Copyright Albert Alma Ltd.

#pragma once

#include "CoreMinimal.h"
#include "BubbleInterface.h"
#include "GameFramework/Actor.h"
#include "Bubble_fwd.h"
#include "BubbleProjectile.generated.h"

class UProjectileMovementComponent;
class UShapeComponent;
class AEnemySpawner;

UCLASS()
class BUBBLEWATCH_API ABubbleProjectile : public AActor, public IBubbleInterface
{
    GENERATED_BODY()

public:

    virtual void Enable_Implementation() override;

    virtual void Disable_Implementation() override;
   
    virtual EColor GetBubbleColor_Implementation() const override;

    virtual void SetBubbleColor_Implementation(EColor Color) override;

    /* When a bubble projectile hit something it will check if it is another bubble and it is the same color.
       - If true, both bubbles will be disabled
       - If false, it will spawn a new enemy with the color of the bubble
    */
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:

    virtual void BeginPlay() override;

    virtual void LifeSpanExpired() override;

public:

    //TODO Create some kind of entity manager to get the Enemy Spawner of the current level
    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Settings")
    AEnemySpawner* EnemySpawner;

private:

    //UPROPERTY(EditAnyWhere, Category = "Settings")
    EColor m_eColor;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    TSubclassOf<class AGhost> GhostClass;

    UPROPERTY()
    UProjectileMovementComponent* m_pProjectileMovementComponent;

    UPROPERTY()
    UShapeComponent* m_pHitComponent;

    UPROPERTY()
    float m_fInitialLifeSpan;

};
