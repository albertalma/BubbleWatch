// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "CoreMinimal.h"
#include "Bubble.generated.h"

UENUM(BlueprintType)		
enum class EColor : uint8
{
    BLUE 	UMETA(DisplayName = "Blue"),
    RED 	UMETA(DisplayName = "Red"),
    YELLOW	UMETA(DisplayName = "Yellow")
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

};
