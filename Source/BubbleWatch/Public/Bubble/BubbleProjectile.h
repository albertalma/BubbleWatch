// Copyright Albert Alma Ltd.

#pragma once

#include "CoreMinimal.h"
#include "Bubble.h"
#include "GameFramework/Actor.h"
#include "BubbleProjectile.generated.h"

class UProjectileMovementComponent;
class UShapeComponent;
class AEnemySpawner;

UCLASS()
class BUBBLEWATCH_API ABubbleProjectile : public AActor, public IBubble
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Enable();
    virtual void Enable_Implementation() override;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Disable();
    virtual void Disable_Implementation() override;
   
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    EColor GetBubbleColor();
    virtual EColor GetBubbleColor_Implementation() override;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetBubbleColor(EColor Color);
    virtual void SetBubbleColor_Implementation(EColor Color) override;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:

    virtual void BeginPlay() override;

    virtual void LifeSpanExpired() override;

public:

    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Settings")
    AEnemySpawner* EnemySpawner;

private:

    UPROPERTY(EditAnyWhere, Category = "Settings")
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
