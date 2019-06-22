// Copyright Albert Alma Ltd.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Bubble.h"
#include "Ghost.generated.h"

/**
 * 
 */
UCLASS()
class BUBBLEWATCH_API AGhost : public ACharacter, public IBubble
{
	GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    EColor GetBubbleColor();
    virtual EColor GetBubbleColor_Implementation() override;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetBubbleColor(EColor Color);
    virtual void SetBubbleColor_Implementation(EColor Color) override;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Disable();
    virtual void Disable_Implementation() override;

private:

    UPROPERTY(EditAnyWhere, Category = "Settings")
    EColor m_eColor;
	
};
