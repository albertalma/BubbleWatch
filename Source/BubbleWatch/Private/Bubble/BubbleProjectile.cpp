// Copyright Albert Alma Ltd.


#include "BubbleProjectile.h"
#include "Components/ShapeComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Ghost/Ghost.h"
#include "EnemySpawner.h"
#include "BubbleInterface.h"
#include "Bubble_fwd.h"

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
    if (ensure(this->GetClass()->ImplementsInterface(UBubbleInterface::StaticClass())))
    {
        IBubbleInterface::Execute_SetBubbleColor(this, static_cast<EColor>(n));
        IBubbleInterface::Execute_SetMaterialBubbleColor(this);
    }
    SetLifeSpan(0.f);
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
    SetActorTickEnabled(false);
    m_pProjectileMovementComponent->Deactivate();
}

void ABubbleProjectile::LifeSpanExpired()
{
    IBubbleInterface* projectileInterface = Cast<IBubbleInterface>(this);
    if (ensure(projectileInterface))
    {
        IBubbleInterface::Execute_Disable(this);
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
    IBubbleInterface* bubbleInterface = Cast<IBubbleInterface>(OtherActor);
    IBubbleInterface* projectileInterface = Cast<IBubbleInterface>(this);
    if (bubbleInterface != nullptr && projectileInterface != nullptr)
    {
        EColor hittedColor = IBubbleInterface::Execute_GetBubbleColor(OtherActor);
        if (hittedColor == IBubbleInterface::Execute_GetBubbleColor(this))
        {
            IBubbleInterface::Execute_Disable(OtherActor);
        }
        else
        {
            FVector direction = GetActorForwardVector();
            FVector origin;
            FVector box;
            OtherActor->GetActorBounds(true, origin, box);
            direction *= -1; 
            FVector spawnLocation = GetActorLocation() + direction * box.Z;
            spawnLocation.Z = OtherActor->GetActorLocation().Z;

            AGhost* ghost;
            if (EnemySpawner != nullptr)
            {
                ghost = EnemySpawner->SpawnEnemy(spawnLocation, OtherActor->GetActorRotation());
            }
            else
            {
                UWorld* const World = GetWorld();
                ghost = (AGhost*)World->SpawnActor<AGhost>(GhostClass, spawnLocation, OtherActor->GetActorRotation());
            }

            if (ghost != nullptr)
            {
                IBubbleInterface* ghostBubble = Cast<IBubbleInterface>(ghost);
                ensure(ghostBubble);
                IBubbleInterface::Execute_SetBubbleColor(ghost, m_eColor);
                IBubbleInterface::Execute_SetMaterialBubbleColor(ghost);
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Cannot spawn new ghost after collision"))
            }
        }

        IBubbleInterface::Execute_Disable(this);
    }
}

EColor ABubbleProjectile::GetBubbleColor_Implementation() const
{
    return m_eColor;
}

void ABubbleProjectile::SetBubbleColor_Implementation(EColor Color)
{
    m_eColor = Color;
}
