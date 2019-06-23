// Copyright Albert Alma Ltd.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUBBLEWATCH_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

    FORCEINLINE float GetCurrentHealth() { return m_fHealth;  }
    FORCEINLINE float GetMaxHealth() { return m_fMaxHealth; }

    float DecreaseHealth(float DecreaseValue);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

    UPROPERTY()
    float m_fHealth;

    UPROPERTY(EditAnyWhere, Category = "Health")
    float m_fMaxHealth = 100.0f;
};
