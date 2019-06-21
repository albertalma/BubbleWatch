// Copyright Albert Alma Ltd.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "GhostMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class BUBBLEWATCH_API UGhostMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
    
    /** path following: request new velocity */
    virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	
};
