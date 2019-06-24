// Copyright Albert Alma Ltd.

#include "BubblePool.h"
#include "Bubble/BubbleProjectile.h"
#include "GameFramework/Actor.h"
#include "Containers/Array.h"

UBubblePool::UBubblePool()
{
}

void UBubblePool::InitialisePool(UWorld* const World, TSubclassOf<class ABubbleProjectile> BubbleClass, int MaxElements, FVector Location, FRotator Rotation)
{
    m_iIndex = 0;
    for (int i = 0; i < MaxElements; ++i)
    {
        ABubbleProjectile* bubble = (ABubbleProjectile*)World->SpawnActor<ABubbleProjectile>(BubbleClass, Location, Rotation);
        ensure(bubble);
        bubble->Disable();
        m_aBubblePool.Add(bubble);
    }
}

ABubbleProjectile* UBubblePool::GetBubble()
{
    ABubbleProjectile* bubble = m_aBubblePool[m_iIndex];
    m_iIndex = GetNextIndex();
    return bubble;
}

EColor UBubblePool::GetCurrentBubbleColor()
{
    ABubbleProjectile* bubble = m_aBubblePool[m_iIndex];
    return bubble->GetBubbleColor();
}

EColor UBubblePool::GetNextBubbleColor()
{
    int index = GetNextIndex();
    ABubbleProjectile* bubble = m_aBubblePool[index];
    return bubble->GetBubbleColor();
}

int UBubblePool::GetNextIndex()
{
    return (m_iIndex >= m_aBubblePool.Num() - 1) ? 0 : m_iIndex + 1;
}