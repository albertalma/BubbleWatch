// Copyright Albert Alma Ltd.

#pragma once

#include "Object.h"
#include "CoreMinimal.h"
#include "Bubble_fwd.h"
#include "BubbleInterface.generated.h"


UINTERFACE()
class BUBBLEWATCH_API UBubbleInterface : public UInterface
{
    GENERATED_UINTERFACE_BODY()
};

class BUBBLEWATCH_API IBubbleInterface
{
    GENERATED_IINTERFACE_BODY()

public:

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    EColor GetBubbleColor() const;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void SetBubbleColor(EColor Color);

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void SetMaterialBubbleColor();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Enable();

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Disable();
};
