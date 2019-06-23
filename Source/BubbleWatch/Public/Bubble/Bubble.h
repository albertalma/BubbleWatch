// Copyright Albert Alma Ltd.

#pragma once

#include "Object.h"
#include "CoreMinimal.h"
#include "Bubble.generated.h"

UENUM(BlueprintType)		
enum class EColor : uint8
{
    BLUE 	    UMETA(DisplayName = "Blue"),
    RED 	    UMETA(DisplayName = "Red"),
    YELLOW	    UMETA(DisplayName = "Yellow"),
    LASTCOLOR   UMETA(DisplayName = "Last")
};

UINTERFACE()
class BUBBLEWATCH_API UBubble : public UInterface
{
    GENERATED_UINTERFACE_BODY()
};

class BUBBLEWATCH_API IBubble
{
    GENERATED_IINTERFACE_BODY()

public:

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    EColor GetBubbleColor();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetBubbleColor(EColor Color);

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void SetMaterialBubbleColor();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Enable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Disable();
};
