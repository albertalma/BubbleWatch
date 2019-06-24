// Copyright Albert Alma Ltd.


#include "BubbleProjectile.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Ghost/Ghost.h"

void ABubbleProjectile::Enable_Implementation()
{
    SetLifeSpan(m_fInitialLifeSpan);
    SetActorHiddenInGame(false);
    SetActorEnableCollision(true);
    SetActorTickEnabled(true);
    m_pProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * m_pProjectileMovementComponent->InitialSpeed);
    m_pProjectileMovementComponent->Activate();
}

void ABubbleProjectile::Disable_Implementation()
{
    int n = FMath::RandRange(0, static_cast<int>(EColor::LASTCOLOR) - 1);
    if (ensure(this->GetClass()->ImplementsInterface(UBubble::StaticClass())))
    {
        IBubble::Execute_SetBubbleColor(this, static_cast<EColor>(n));
        IBubble::Execute_SetMaterialBubbleColor(this);
    }
    SetLifeSpan(0.f);
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
    SetActorTickEnabled(false);
    m_pProjectileMovementComponent->Deactivate();
}

void ABubbleProjectile::LifeSpanExpired()
{
    IBubble* projectileInterface = Cast<IBubble>(this);
    if (ensure(projectileInterface))
    {
        projectileInterface->Execute_Disable(this);
    }
}

void ABubbleProjectile::BeginPlay()
{
    Super::BeginPlay();

    m_fInitialLifeSpan = InitialLifeSpan;
    m_pHitComponent = Cast<UShapeComponent>(GetComponentByClass(UShapeComponent::StaticClass()));
    m_pProjectileMovementComponent = Cast<UProjectileMovementComponent>(GetComponentByClass(UProjectileMovementComponent::StaticClass()));

    if (ensure(m_pHitComponent))
    {
        m_pHitComponent->BodyInstance.SetCollisionProfileName("Projectile");
        m_pHitComponent->OnComponentHit.AddDynamic(this, &ABubbleProjectile::OnHit);

        m_pHitComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
        m_pHitComponent->CanCharacterStepUpOn = ECB_No;

        if (ensure(m_pProjectileMovementComponent))
        {
            m_pProjectileMovementComponent->UpdatedComponent = m_pHitComponent;
        }
    }
}

void ABubbleProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    IBubble* bubbleInterface = Cast<IBubble>(OtherActor);
    IBubble* projectileInterface = Cast<IBubble>(this);
    if (bubbleInterface && ensure(projectileInterface))
    {
        EColor hittedColor = bubbleInterface->Execute_GetBubbleColor(OtherActor);
        if (hittedColor == projectileInterface->Execute_GetBubbleColor(this))
        {
            bubbleInterface->Execute_Disable(OtherActor);
        }
        else
        {
            UWorld* const World = GetWorld();
            if (World != nullptr)
            {
                FVector direction = GetActorForwardVector();
                FVector origin;
                FVector box;
                OtherActor->GetActorBounds(true, origin, box);
                direction *= -1; 
                FVector spawnLocation = GetActorLocation() + direction * box.Z;
                spawnLocation.Z = OtherActor->GetActorLocation().Z;
                AGhost* ghost = (AGhost*) World->SpawnActor<AGhost>(GhostClass, spawnLocation, GetActorRotation());
                if (ghost != nullptr)
                {
                    IBubble* ghostBubble = Cast<IBubble>(ghost);
                    ensure(ghostBubble);
                    ghostBubble->Execute_SetBubbleColor(ghost, m_eColor);
                    ghostBubble->Execute_SetMaterialBubbleColor(ghost);
                }
            }
        }
        projectileInterface->Execute_Disable(this);
    }
}

EColor ABubbleProjectile::GetBubbleColor_Implementation()
{
    return m_eColor;
}

void ABubbleProjectile::SetBubbleColor_Implementation(EColor Color)
{
    m_eColor = Color;
}
