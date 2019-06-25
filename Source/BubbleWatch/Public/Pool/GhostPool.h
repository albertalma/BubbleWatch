// Copyright Albert Alma Ltd.

#pragma once

#include "CoreMinimal.h"
#include "Pool/BubblePool.h"
#include "GhostPool.generated.h"

/**
 * 
 */
UCLASS()
class BUBBLEWATCH_API UGhostPool : public UBubblePool
{
	GENERATED_BODY()
public:

    virtual IBubble* GetBubble() override;

};
