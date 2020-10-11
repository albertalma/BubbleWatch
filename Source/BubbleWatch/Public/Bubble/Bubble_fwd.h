// Copyright Albert Alma Ltd.

#pragma once

#include "Object.h"
#include "CoreMinimal.h"
#include "Bubble_fwd.generated.h"

UENUM(BlueprintType)		
enum class EColor : uint8
{
    BLUE 	    UMETA(DisplayName = "Blue"),
    RED 	    UMETA(DisplayName = "Red"),
    YELLOW	    UMETA(DisplayName = "Yellow"),
    LASTCOLOR   UMETA(DisplayName = "Last")
};