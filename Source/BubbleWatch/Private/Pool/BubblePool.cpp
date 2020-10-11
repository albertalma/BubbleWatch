// Copyright Albert Alma Ltd.

#include "BubblePool.h"
#include "Bubble/BubbleProjectile.h"
#include "GameFramework/Actor.h"
#include "Containers/Array.h"
#include "BubbleInterface.h"

UBubblePool::UBubblePool()
{
}

void UBubblePool::InitialisePool(UWorld* const World, TSubclassOf<class UObject> BubbleClass, int MaxElements, FVector Location, FRotator Rotation)
{
    m_iIndex = 0;
    for (int i = 0; i < MaxElements; ++i)
    {
        if (IBubbleInterface* spawnedBubble = World->SpawnActor<IBubbleInterface>(BubbleClass, Location, Rotation))
        {
            IBubbleInterface::Execute_Disable(spawnedBubble->_getUObject());
            m_aBubblePool.Add(spawnedBubble->_getUObject());
        }
    }
}

IBubbleInterface* UBubblePool::PopBubble()
{
    IBubbleInterface* bubble = Cast<IBubbleInterface>(m_aBubblePool[m_iIndex].GetObject());
    m_iIndex = GetNextIndex();
    return bubble;
}

int UBubblePool::GetNextIndex() const
{
    return (m_iIndex >= m_aBubblePool.Num() - 1) ? 0 : m_iIndex + 1;
}

void UBubblePool::AddBubble(IBubbleInterface* bubble)
{
    /*TScriptInterface<IBubbleInterface> bubbleInterface;
    bubbleInterface.SetInterface(Cast <IBubbleInterface>(bubble));
    bubbleInterface.SetObject(bubble);*/
    m_aBubblePool.Add(bubble->_getUObject());
}