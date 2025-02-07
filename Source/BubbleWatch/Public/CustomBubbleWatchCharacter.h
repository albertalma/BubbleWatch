// Copyright Albert Alma Ltd.

#pragma once

#include "CoreMinimal.h"
#include "BubbleWatchCharacter.h"
#include "CustomBubbleWatchCharacter.generated.h"

struct FActorSpawnParameters;
class UBubbleProjectilePool;
class UHealthComponent;

UCLASS()
class BUBBLEWATCH_API ACustomBubbleWatchCharacter : public ABubbleWatchCharacter
{
	GENERATED_BODY()

public:

    ACustomBubbleWatchCharacter();

    UFUNCTION(BlueprintCallable, Category = "Bubbles")
    EColor GetCurrentBubble() const;

    UFUNCTION(BlueprintCallable, Category = "Bubbles")
    EColor GetNextBubble() const;

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetCurrentHealth() const;

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetMaxHealth() const;
	
protected:

    virtual void BeginPlay() override;

    virtual void SpawnProjectile(UWorld* const World, const FRotator SpawnRotation, const FVector SpawnLocation, FActorSpawnParameters ActorSpawnParams) override;

    virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

    UFUNCTION()
    void OnCharacterDead();

public:

    /** Projectile class to spawn */
    UPROPERTY(EditDefaultsOnly, Category = "Projectile")
    TSubclassOf<class ABubbleProjectile> BubbleProjectileClass;

    UPROPERTY(EditAnyWhere, Category = "Projectile")
    int MaxProjectiles = 20.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
    class USoundBase* DamageSound;

private:

    UPROPERTY()
    UBubbleProjectilePool* m_pBubbleProjectilePool;

    UPROPERTY()
    UHealthComponent* m_pHealthComponent;
};
