// Copyright Albert Alma Ltd.

#pragma once

#include "CoreMinimal.h"
#include "BubbleInterface.h"
#include "BubblePool.generated.h"

UCLASS()
class BUBBLEWATCH_API UBubblePool : public UObject
{
	GENERATED_BODY()

public:

    UBubblePool();

    virtual void InitialisePool(UWorld* const World, TSubclassOf<class UObject> BubbleClass, int MaxElementsFVector, FVector Location, FRotator Rotation);

    /* Get current bubble and increase index */
    virtual IBubbleInterface* PopBubble();

    virtual void AddBubble(IBubbleInterface* Bubble);

protected:

    int GetNextIndex() const;

protected:

    UPROPERTY()
    TArray<TScriptInterface<IBubbleInterface>> m_aBubblePool;

    UPROPERTY()
    int m_iIndex;
};
