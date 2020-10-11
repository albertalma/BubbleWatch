// Copyright Albert Alma Ltd.

#include "EnemySpawner.h"
#include "Ghost/Ghost.h"
#include "Pool/GhostPool.h"
#include "Kismet/GameplayStatics.h"

AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
    m_iIndex = 0;
    m_fTimer = m_fSpawnRateSeconds;
    m_iTotalEnemiesNumber = 0;
    m_iEnemiesNumberCounter = 0;
    m_pGhostPool = NewObject<UGhostPool>();
    m_pGhostPool->InitialisePool(GetWorld(), GhostClass, m_iInitialEnemiesNumber, GetActorLocation(), GetActorRotation());
}

void AEnemySpawner::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

    if (m_iIndex >= m_iInitialEnemiesNumber)
    {
        SetActorTickEnabled(false);
    }
    else if (m_fTimer >= m_fSpawnRateSeconds)
    {
        SpawnEnemy(GetActorLocation(), GetActorRotation());
        ++m_iIndex;
        m_fTimer = 0;
    }
    else
    {
        m_fTimer += DeltaSeconds;
    }


}

AGhost* AEnemySpawner::SpawnEnemy(FVector Location, FRotator Rotation)
{
    AGhost* ghost;
    if (m_pGhostPool->GetAvailableBubbles() > 0)
    {
        ghost = (AGhost*) m_pGhostPool->PopBubble();
        ghost->SetActorLocation(Location);
        ghost->SetActorRotation(Rotation);
    }
    else
    {
       ghost = GetWorld()->SpawnActor<AGhost>(GhostClass, Location, Rotation);
    }
    if (ghost != nullptr)
    {
        ghost->SetSpawner(this);
        IBubbleInterface::Execute_Enable(ghost);
        ++m_iTotalEnemiesNumber;
    }
    return ghost;
}

void AEnemySpawner::AddEnemy(AGhost* Ghost)
{
    m_pGhostPool->AddBubble(Ghost);
    ++m_iEnemiesNumberCounter;
    if (m_iEnemiesNumberCounter == m_iTotalEnemiesNumber)
    {
        UWorld* TheWorld = GetWorld();
        UGameplayStatics::OpenLevel(GetWorld(), "WinMenu");
    }
}



