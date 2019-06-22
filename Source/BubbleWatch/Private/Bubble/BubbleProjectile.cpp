// Copyright Albert Alma Ltd.


#include "BubbleProjectile.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

void ABubbleProjectile::Enable()
{
    SetLifeSpan(m_fInitialLifeSpan);
    SetActorHiddenInGame(false);
    SetActorEnableCollision(true);
    SetActorTickEnabled(true);
    m_pProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * m_pProjectileMovementComponent->InitialSpeed);
    m_pProjectileMovementComponent->Activate();
}

void ABubbleProjectile::Disable()
{
    int n = FMath::RandRange(0, static_cast<int>(EColor::LASTCOLOR) - 1);
    m_eColor = static_cast<EColor>(n);
    SetBubbleColor();
    SetLifeSpan(0.f);
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
    SetActorTickEnabled(false);
    m_pProjectileMovementComponent->Deactivate();
}

void ABubbleProjectile::LifeSpanExpired()
{
    Disable();
}

void ABubbleProjectile::BeginPlay()
{
    Super::BeginPlay();

    m_fInitialLifeSpan = InitialLifeSpan;
    m_pHitComponent = Cast<UShapeComponent>(GetComponentByClass(UShapeComponent::StaticClass()));
    TArray<UActorComponent*> overlapComponents = GetComponentsByTag(UShapeComponent::StaticClass(), "Overlap");
    if (ensure(overlapComponents.Num() > 0))
    {
        m_pOverlapComponent = Cast<UShapeComponent>(overlapComponents[0]);
    }
    m_pProjectileMovementComponent = Cast<UProjectileMovementComponent>(GetComponentByClass(UProjectileMovementComponent::StaticClass()));

    if (ensure(m_pHitComponent))
    {
        m_pHitComponent->BodyInstance.SetCollisionProfileName("Projectile");
        m_pHitComponent->OnComponentHit.AddDynamic(this, &ABubbleProjectile::OnHit);

        m_pHitComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
        m_pHitComponent->CanCharacterStepUpOn = ECB_No;

        if (ensure(m_pProjectileMovementComponent))
        {
            m_pProjectileMovementComponent->Deactivate();
            m_pProjectileMovementComponent->UpdatedComponent = m_pHitComponent;
        }
    }
}

void ABubbleProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor->Implements<UBubble>())
    {
        EColor hittedColor = IBubble::Execute_GetBubbleColor(OtherActor);
        if (hittedColor == IBubble::Execute_GetBubbleColor(this))
        {
            //OtherActor->Destroy();
            Disable();
        }
        else
        {
            SetLifeSpan(0.f);
            m_pProjectileMovementComponent->Deactivate();
        }
    }
}

EColor ABubbleProjectile::GetBubbleColor_Implementation()
{
    return m_eColor;
}
