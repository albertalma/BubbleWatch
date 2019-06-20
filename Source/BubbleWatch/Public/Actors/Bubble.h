// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bubble.generated.h"

UENUM(BlueprintType)		
enum class EColor : uint8
{
    BLUE 	UMETA(DisplayName = "Blue"),
    RED 	UMETA(DisplayName = "Red"),
    YELLOW	UMETA(DisplayName = "Yellow")
};

UCLASS()
class BUBBLEWATCH_API ABubble : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABubble();

    FORCEINLINE EColor GetBubbleColor() { return m_eColor; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

    UPROPERTY(EditAnyWhere, Category = Projectile)
    EColor m_eColor;
};
