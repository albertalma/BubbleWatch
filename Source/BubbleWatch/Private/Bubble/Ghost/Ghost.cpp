// Copyright Albert Alma Ltd.


#include "Ghost.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemySpawner.h"
#include "Bubble_fwd.h"

EColor AGhost::GetBubbleColor_Implementation() const
{
    return m_eColor;
}

void AGhost::Enable_Implementation()
{
    int n = FMath::RandRange(0, static_cast<int>(EColor::LASTCOLOR) - 1);
    IBubbleInterface::Execute_SetBubbleColor(this, static_cast<EColor>(n));
    IBubbleInterface::Execute_SetMaterialBubbleColor(this);
    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
    SetActorHiddenInGame(false);
    SetActorEnableCollision(true);
    SetActorTickEnabled(true);
}

void AGhost::Disable_Implementation()
{
    GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
    SetActorTickEnabled(false);
    if (m_pSpawner != nullptr)
    {
        m_pSpawner->AddEnemy(this);
    }
}

void AGhost::SetBubbleColor_Implementation(EColor Color)
{
    m_eColor = Color;
}
