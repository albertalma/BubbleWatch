// Copyright Albert Alma Ltd.


#include "Ghost.h"
#include "GameFramework/CharacterMovementComponent.h"

EColor AGhost::GetBubbleColor_Implementation()
{
    return m_eColor;
}

void AGhost::Enable_Implementation()
{
    //TODO Enable and disable AIController changing something in the blackboard probably
    int n = FMath::RandRange(0, static_cast<int>(EColor::LASTCOLOR) - 1);
    if (ensure(this->GetClass()->ImplementsInterface(UBubble::StaticClass())))
    {
        IBubble::Execute_SetBubbleColor(this, static_cast<EColor>(n));
        IBubble::Execute_SetMaterialBubbleColor(this);
    }
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
}

void AGhost::SetBubbleColor_Implementation(EColor Color)
{
    m_eColor = Color;
}
