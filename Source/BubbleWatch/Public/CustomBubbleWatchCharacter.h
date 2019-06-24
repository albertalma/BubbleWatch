// Copyright Albert Alma Ltd.

#pragma once

#include "CoreMinimal.h"
#include "BubbleWatchCharacter.h"
#include "CustomBubbleWatchCharacter.generated.h"

struct FActorSpawnParameters;
class UBubblePool;
class UHealthComponent;

UCLASS()
class BUBBLEWATCH_API ACustomBubbleWatchCharacter : public ABubbleWatchCharacter
{
	GENERATED_BODY()

public:

    ACustomBubbleWatchCharacter();

    UFUNCTION(BlueprintCallable, Category = "Bubbles")
    EColor GetCurrentBubble();

    UFUNCTION(BlueprintCallable, Category = "Bubbles")
    EColor GetNextBubble();

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetCurrentHealth();

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetMaxHealth();
	
protected:
    virtual void BeginPlay() override;

    virtual void SpawnProjectile(UWorld* const World, const FRotator SpawnRotation, const FVector SpawnLocation, FActorSpawnParameters ActorSpawnParams) override;

    virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

    UFUNCTION()
    void OnCharacterDead();

public:

    /** Projectile class to spawn */
    UPROPERTY(EditDefaultsOnly, Category = Projectile)
    TSubclassOf<class ABubbleProjectile> BubbleProjectileClass;

    UPROPERTY(EditAnyWhere, Category = Projectile)
    int MaxProjectiles = 20.0f;

private:

    UPROPERTY()
    UBubblePool* m_pBubblePool;

    UPROPERTY()
    UHealthComponent* m_pHealthComponent;
};
