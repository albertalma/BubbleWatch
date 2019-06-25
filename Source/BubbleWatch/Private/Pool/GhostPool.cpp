// Copyright Albert Alma Ltd.


#include "GhostPool.h"

IBubble* UGhostPool::GetBubble()
{
    IBubble* bubble = Cast<IBubble>(m_aBubblePool.Pop(true).GetObject());
    return bubble;
}