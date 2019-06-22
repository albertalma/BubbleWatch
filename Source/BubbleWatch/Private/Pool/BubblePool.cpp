// Copyright Albert Alma Ltd.

#include "BubblePool.h"
#include "Bubble/BubbleProjectile.h"
#include "GameFramework/Actor.h"
#include "Containers/Array.h"

UBubblePool::UBubblePool()
{
}

void UBubblePool::InitialisePool(UWorld* const World, TSubclassOf<class ABubbleProjectile> BubbleClass, int MaxElements)
{
    m_iIndex = 0;
    for (int i = 0; i < MaxElements; ++i)
    {
        ABubbleProjectile* bubble = World->SpawnActor<ABubbleProjectile>(BubbleClass, FVector(), FRotator());
        ensure(bubble);
        bubble->Disable();
        m_aBubblePool.Add(bubble);
    }
}

ABubbleProjectile* UBubblePool::GetBubble()
{
    ABubbleProjectile* bubble = m_aBubblePool[m_iIndex];
    m_iIndex = (m_iIndex >= m_aBubblePool.Num()-1) ? 0 : m_iIndex + 1;
    return bubble;
}

EColor UBubblePool::GetCurrentBubbleColor()
{
    return m_aBubblePool[m_iIndex]->GetBubbleColor();
}

EColor UBubblePool::GetNextBubbleColor()
{
    //TODO move this into a function
    int index = (m_iIndex >= m_aBubblePool.Num() - 1) ? 0 : m_iIndex + 1;
    return  m_aBubblePool[m_iIndex]->GetBubbleColor();
}