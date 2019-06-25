// Copyright Albert Alma Ltd.

#include "EnemySpawner.h"
#include "Ghost/Ghost.h"
#include "Pool/GhostPool.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
    //TODO Maybe a generic pool??
	Super::BeginPlay();
    m_iIndex = 0;
    m_fTimer = m_fSpawnRateSeconds;

    m_pGhostPool = NewObject<UGhostPool>();
    m_pGhostPool->InitialisePool(GetWorld(), GhostClass, m_iEnemiesNumber, GetActorLocation(), GetActorRotation());
}

// Called every frame
void AEnemySpawner::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
    if (m_fTimer >= m_fSpawnRateSeconds && m_iIndex < m_iEnemiesNumber)
    {
        AGhost* ghost = (AGhost*) m_pGhostPool->GetBubble();
        ghost->SetActorLocation(GetActorLocation());
        ghost->SetActorRotation(GetActorRotation());
        ghost->Enable();
        ++m_iIndex;
        m_fTimer = 0;
    }
    else
    {
        m_fTimer += DeltaSeconds;
    }
}

