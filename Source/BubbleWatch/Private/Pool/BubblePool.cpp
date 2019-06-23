// Copyright Albert Alma Ltd.

#include "BubblePool.h"
#include "Bubble/BubbleProjectile.h"
#include "GameFramework/Actor.h"
#include "Containers/Array.h"

#include "EngineGlobals.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"

UBubblePool::UBubblePool()
{
}

void UBubblePool::InitialisePool(UWorld* const World, TSubclassOf<class ABubbleProjectile> BubbleClass, int MaxElements)
{
    m_iIndex = 0;
    for (int i = 0; i < MaxElements; ++i)
    {
        ABubbleProjectile* bubble = (ABubbleProjectile*)World->SpawnActor<ABubbleProjectile>(BubbleClass, FVector(), FRotator());
        ensure(bubble);
        bubble->Disable();
        m_aBubblePool.Add(bubble);
    }
}

ABubbleProjectile* UBubblePool::GetBubble()
{
    ABubbleProjectile* bubble = m_aBubblePool[m_iIndex];
    m_iIndex = (m_iIndex >= m_aBubblePool.Num()-1) ? 0 : m_iIndex + 1;
    GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Red, FString::Printf(TEXT("Current Color: %i"), static_cast<int>(GetCurrentBubbleColor())));
    GEngine->AddOnScreenDebugMessage(2, 60.f, FColor::Red, FString::Printf(TEXT("Next Color: %i"), static_cast<int>(GetNextBubbleColor())));
    return bubble;
}

EColor UBubblePool::GetCurrentBubbleColor()
{
    ABubbleProjectile* bubble = m_aBubblePool[m_iIndex];
    return bubble->GetBubbleColor();
}

EColor UBubblePool::GetNextBubbleColor()
{
    //TODO move this into a function
    int index = (m_iIndex >= m_aBubblePool.Num() - 1) ? 0 : m_iIndex + 1;
    ABubbleProjectile* bubble = m_aBubblePool[index];
    return bubble->GetBubbleColor();
}