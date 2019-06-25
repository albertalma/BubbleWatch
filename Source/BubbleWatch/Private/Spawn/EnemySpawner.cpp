// Copyright Albert Alma Ltd.

#include "EnemySpawner.h"
#include "Ghost/Ghost.h"
#include "Pool/GhostPool.h"
#include "Kismet/GameplayStatics.h"

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
    m_iTotalEnemiesNumber = m_iInitialEnemiesNumber;
    m_iEnemiesNumberCounter = 0;
    m_pGhostPool = NewObject<UGhostPool>();
    m_pGhostPool->InitialisePool(GetWorld(), GhostClass, m_iInitialEnemiesNumber, GetActorLocation(), GetActorRotation());
}

// Called every frame
void AEnemySpawner::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

    if (m_fTimer >= m_fSpawnRateSeconds)
    {
        SpawnEnemy(GetActorLocation(), GetActorRotation());
        ++m_iIndex;
        m_fTimer = 0;
    }
    else
    {
        m_fTimer += DeltaSeconds;
    }

    if (m_iIndex > m_iInitialEnemiesNumber)
    {
        SetActorTickEnabled(false);
    }
}

AGhost* AEnemySpawner::SpawnEnemy(FVector Location, FRotator Rotation)
{
    AGhost* ghost;
    if (m_pGhostPool->GetAvailableBubbles() > 0)
    {
        ghost = (AGhost*) m_pGhostPool->GetBubble();
        ghost->SetActorLocation(Location);
        ghost->SetActorRotation(Rotation);
    }
    else
    {
       ghost = GetWorld()->SpawnActor<AGhost>(GhostClass, Location, Rotation);
       if (ghost != nullptr)
       {
           ++m_iTotalEnemiesNumber;
       }
    }
    if (ghost != nullptr)
    {
        ghost->SetSpawner(this);
        ghost->Enable();
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



