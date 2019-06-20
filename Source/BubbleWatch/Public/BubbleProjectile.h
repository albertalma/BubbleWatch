// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Bubble.h"
#include "BubbleProjectile.generated.h"


class UProjectileMovementComponent;
class UShapeComponent;

UCLASS()
class BUBBLEWATCH_API ABubbleProjectile : public ABubble
{
    GENERATED_BODY()

public:

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:

    virtual void BeginPlay() override;

private:

    UProjectileMovementComponent* m_pProjectileMovementComponent;
    UShapeComponent* m_pShapeComponent;
};
