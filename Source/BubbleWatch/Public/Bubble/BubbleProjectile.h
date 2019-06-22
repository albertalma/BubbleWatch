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

private:

    UPROPERTY(EditAnyWhere, Category = "Settings")
    EColor m_eColor;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    TSubclassOf<class AGhost> GhostClass;

    UProjectileMovementComponent* m_pProjectileMovementComponent;

    UShapeComponent* m_pHitComponent;
    UShapeComponent* m_pOverlapComponent;

    float m_fInitialLifeSpan;

};
