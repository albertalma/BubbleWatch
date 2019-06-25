// Copyright Albert Alma Ltd.

#pragma once

#include "CoreMinimal.h"
#include "Pool/BubblePool.h"
#include "BubbleProjectilePool.generated.h"

/**
 * 
 */
UCLASS()
class BUBBLEWATCH_API UBubbleProjectilePool : public UBubblePool
{
	GENERATED_BODY()

public:

    EColor GetCurrentBubbleColor();

    EColor GetNextBubbleColor();

};
