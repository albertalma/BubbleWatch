// Fill out your copyright notice in the Description page of Project Settings.

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

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    EColor GetBubbleColor();
    virtual EColor GetBubbleColor_Implementation() override;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:

    virtual void BeginPlay() override;

private:

    UPROPERTY(EditAnyWhere, Category = "Settings")
    EColor m_eColor;

    UProjectileMovementComponent* m_pProjectileMovementComponent;

    UShapeComponent* m_pHitComponent;
    UShapeComponent* m_pOverlapComponent;

};
