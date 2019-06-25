// Copyright Albert Alma Ltd.

#include "BubblePool.h"
#include "Bubble/BubbleProjectile.h"
#include "GameFramework/Actor.h"
#include "Containers/Array.h"

UBubblePool::UBubblePool()
{
}

void UBubblePool::InitialisePool(UWorld* const World, TSubclassOf<class UObject> BubbleClass, int MaxElements, FVector Location, FRotator Rotation)
{
    m_iIndex = 0;
    for (int i = 0; i < MaxElements; ++i)
    {
        UObject* spawnedBubble = World->SpawnActor<UObject>(BubbleClass, Location, Rotation);
        if (ensure(spawnedBubble->GetClass()->ImplementsInterface(UBubble::StaticClass())))
        {
            TScriptInterface<IBubble> bubbleInterface;
            bubbleInterface.SetInterface(Cast <IBubble>(spawnedBubble));
            bubbleInterface.SetObject(spawnedBubble);
            bubbleInterface->Execute_Disable(spawnedBubble);
            m_aBubblePool.Add(bubbleInterface);
        }
    }
}

IBubble* UBubblePool::GetBubble()
{
    IBubble* bubble = Cast<IBubble>(m_aBubblePool[m_iIndex].GetObject());
    m_iIndex = GetNextIndex();
    return bubble;
}

int UBubblePool::GetNextIndex()
{
    return (m_iIndex >= m_aBubblePool.Num() - 1) ? 0 : m_iIndex + 1;
}

void UBubblePool::AddBubble(UObject* bubble)
{
    if (ensure(bubble->GetClass()->ImplementsInterface(UBubble::StaticClass())))
    {
        TScriptInterface<IBubble> bubbleInterface;
        bubbleInterface.SetInterface(Cast <IBubble>(bubble));
        bubbleInterface.SetObject(bubble);
        m_aBubblePool.Add(bubbleInterface);
    }
}