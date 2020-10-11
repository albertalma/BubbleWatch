// Copyright Albert Alma Ltd.


#include "GhostPool.h"
#include "BubbleInterface.h"

IBubbleInterface* UGhostPool::PopBubble()
{
    IBubbleInterface* bubble = Cast<IBubbleInterface>(m_aBubblePool.Pop(true).GetObject());
    return bubble;
}