// Copyright Albert Alma Ltd.

#pragma once

#include "CoreMinimal.h"
#include "Bubble.h"
#include "GameFramework/Actor.h"
#include "BubbleProjectile.generated.h"


class UProjectileMovementComponent;
class UShapeComponent;

UCLASS()
class BUBBLEWATCH_API ABubbleProjectile : public AActor, public IBubble
{
    GENERATED_BODY()

public:

    void Enable();
    void Disable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    EColor GetBubbleColor();
    virtual EColor GetBubbleColor_Implementation() override;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    UFUNCTION(BlueprintImplementableEvent)
    void SetBubbleColor();

protected:

    virtual void BeginPlay() override;

    virtual void LifeSpanExpired() override;

private:

    UPROPERTY(EditAnyWhere, Category = "Settings")
    EColor m_eColor;

    UProjectileMovementComponent* m_pProjectileMovementComponent;

    UShapeComponent* m_pHitComponent;
    UShapeComponent* m_pOverlapComponent;

    float m_fInitialLifeSpan;

};
