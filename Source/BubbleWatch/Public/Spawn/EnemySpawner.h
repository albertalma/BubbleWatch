// Copyright Albert Alma Ltd.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class AGhost;

UCLASS()
class BUBBLEWATCH_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

private:

    UPROPERTY(EditAnyWhere, Category = "Spawn Settings")
    int m_iEnemiesNumber;

    UPROPERTY(EditAnyWhere, Category = "Spawn Settings")
    float m_fSpawnRateSeconds;

    //TODO Revise Categories
    UPROPERTY(EditAnyWhere, Category = "Spawn Settings")
    TSubclassOf<class AGhost> GhostClass;

    UPROPERTY()
    TArray<AGhost*> m_aEnemiesPool;

    UPROPERTY()
    int m_iIndex;

    UPROPERTY()
    float m_fTimer;
};
