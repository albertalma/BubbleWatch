// Copyright Albert Alma Ltd.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Containers/Queue.h"
#include "Bubble/Bubble.h"
#include "BubblePool.generated.h"

UCLASS()
class BUBBLEWATCH_API UBubblePool : public UObject
{
	GENERATED_BODY()

public:

    UBubblePool();

    virtual void InitialisePool(UWorld* const World, TSubclassOf<class UObject> BubbleClass, int MaxElementsFVector, FVector Location, FRotator Rotation);

    virtual IBubble* GetBubble();

    virtual void AddBubble(UObject* Bubble);

protected:

    int GetNextIndex();

protected:

    UPROPERTY()
    TArray<TScriptInterface<IBubble>> m_aBubblePool;

    UPROPERTY()
    int m_iIndex;
};
