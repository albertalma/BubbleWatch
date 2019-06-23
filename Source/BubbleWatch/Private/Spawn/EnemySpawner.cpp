// Copyright Albert Alma Ltd.

#include "EnemySpawner.h"
#include "Ghost/Ghost.h"

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
    for (int i = 0; i < m_iEnemiesNumber; ++i)
    {
        AGhost* ghost = (AGhost*) GetWorld()->SpawnActor<AGhost>(GhostClass, GetActorLocation(), GetActorRotation());
        ensure(ghost);
        ghost->Disable();
        m_aEnemiesPool.Add(ghost);
    }
}

// Called every frame
void AEnemySpawner::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
    if (m_fTimer >= m_fSpawnRateSeconds && m_iIndex < m_iEnemiesNumber)
    {
        AGhost* ghost = m_aEnemiesPool[m_iIndex];
        ghost->Enable();
        ++m_iIndex;
        m_fTimer = 0;
    }
    else
    {
        m_fTimer += DeltaSeconds;
    }
}

