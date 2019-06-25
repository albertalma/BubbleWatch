// Copyright Albert Alma Ltd.

#include "BubbleProjectilePool.h"

EColor UBubbleProjectilePool::GetCurrentBubbleColor()
{
    UObject* bubbleObject = m_aBubblePool[m_iIndex].GetObject();
    IBubble* bubbleInterface = Cast<IBubble>(bubbleObject);
    if (ensure(bubbleInterface))
    {
        return bubbleInterface->Execute_GetBubbleColor(bubbleObject);
    }
    return EColor::LASTCOLOR;
}

EColor UBubbleProjectilePool::GetNextBubbleColor()
{
    int index = GetNextIndex();
    UObject* bubbleObject = m_aBubblePool[index].GetObject();
    IBubble* bubbleInterface = Cast<IBubble>(bubbleObject);
    if (ensure(bubbleInterface))
    {
        return bubbleInterface->Execute_GetBubbleColor(bubbleObject);
    }
    return EColor::LASTCOLOR;
}