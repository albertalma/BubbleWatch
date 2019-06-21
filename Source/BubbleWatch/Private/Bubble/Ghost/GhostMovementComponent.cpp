// Copyright Albert Alma Ltd.


#include "GhostMovementComponent.h"

void UGhostMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
    AActor* owner = GetOwner();
    if (owner != nullptr)
    {
        FVector currentLocation = owner->GetActorLocation();
        owner->SetActorLocation(currentLocation + MoveVelocity);
    }
}