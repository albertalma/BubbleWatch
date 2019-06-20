// Fill out your copyright notice in the Description page of Project Settings.


#include "BubbleProjectile.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

void ABubbleProjectile::BeginPlay()
{
    Super::BeginPlay();

    m_pShapeComponent = Cast<UShapeComponent>(GetComponentByClass(UShapeComponent::StaticClass()));
    m_pProjectileMovementComponent = Cast<UProjectileMovementComponent>(GetComponentByClass(UProjectileMovementComponent::StaticClass()));

    if (ensure(m_pShapeComponent))
    {
        m_pShapeComponent->BodyInstance.SetCollisionProfileName("Projectile");
        m_pShapeComponent->OnComponentHit.AddDynamic(this, &ABubbleProjectile::OnHit);

        m_pShapeComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
        m_pShapeComponent->CanCharacterStepUpOn = ECB_No;

        if (ensure(m_pProjectileMovementComponent))
        {
            m_pProjectileMovementComponent->UpdatedComponent = m_pShapeComponent;
        }
    }
}

void ABubbleProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    ABubble* hittedBubble = Cast<ABubble>(OtherActor);
    if (hittedBubble != nullptr)
    {
        hittedBubble->Destroy();
        Destroy();
    }
}
