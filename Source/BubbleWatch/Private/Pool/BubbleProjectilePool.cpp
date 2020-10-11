// Copyright Albert Alma Ltd.

#include "BubbleProjectilePool.h"
#include "Bubble_fwd.h"

EColor UBubbleProjectilePool::GetCurrentBubbleColor() const
{
    UObject* bubbleObject = m_aBubblePool[m_iIndex].GetObject();
    IBubbleInterface* bubbleInterface = Cast<IBubbleInterface>(bubbleObject);
    if (ensure(bubbleInterface))
    {
        return IBubbleInterface::Execute_GetBubbleColor(bubbleObject);
    }
    return EColor::LASTCOLOR;
}

EColor UBubbleProjectilePool::GetNextBubbleColor() const
{
    int index = GetNextIndex();
    UObject* bubbleObject = m_aBubblePool[index].GetObject();
    IBubbleInterface* bubbleInterface = Cast<IBubbleInterface>(bubbleObject);
    if (ensure(bubbleInterface))
    {
        return IBubbleInterface::Execute_GetBubbleColor(bubbleObject);
    }
    return EColor::LASTCOLOR;
}