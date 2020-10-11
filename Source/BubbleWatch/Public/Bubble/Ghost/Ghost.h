// Copyright Albert Alma Ltd.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BubbleInterface.h"
#include "Ghost.generated.h"

class AEnemySpawner;

UCLASS()
class BUBBLEWATCH_API AGhost : public ACharacter, public IBubbleInterface
{
	GENERATED_BODY()

public:

    virtual EColor GetBubbleColor_Implementation() const override;

    virtual void SetBubbleColor_Implementation(EColor Color) override;

    virtual void Enable_Implementation() override;

    virtual void Disable_Implementation() override;

    FORCEINLINE void SetSpawner(AEnemySpawner* Spawner) { m_pSpawner = Spawner; }

private:

    UPROPERTY(EditAnyWhere, Category = "Settings")
    EColor m_eColor;
	
    UPROPERTY()
    AEnemySpawner* m_pSpawner;
};
