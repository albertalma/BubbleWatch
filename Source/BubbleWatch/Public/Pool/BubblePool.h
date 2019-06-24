// Copyright Albert Alma Ltd.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Containers/Queue.h"
#include "Bubble/BubbleProjectile.h"
#include "BubblePool.generated.h"

UCLASS()
class BUBBLEWATCH_API UBubblePool : public UObject
{
	GENERATED_BODY()

public:

    UBubblePool();

    void InitialisePool(UWorld* const World, TSubclassOf<class ABubbleProjectile> BubbleClass, int MaxElementsFVector, FVector Location, FRotator Rotation);

    ABubbleProjectile* GetBubble();

    EColor GetCurrentBubbleColor();

    EColor GetNextBubbleColor();

private:

    int GetNextIndex();

private:

    UPROPERTY()
    TArray<ABubbleProjectile*> m_aBubblePool;

    UPROPERTY()
    int m_iIndex;
};
