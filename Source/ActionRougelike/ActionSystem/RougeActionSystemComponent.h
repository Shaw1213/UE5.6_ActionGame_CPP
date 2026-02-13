// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RougeActionSystemComponent.generated.h"


USTRUCT(BlueprintType)
struct FRougeAttributeSet
{
	GENERATED_BODY()
	
	FRougeAttributeSet()
		:Health(100.0f) {}
	
	UPROPERTY(BlueprintReadOnly)
	float Health;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ACTIONROUGELIKE_API URougeActionSystemComponent : public UActorComponent
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(BlueprintReadOnly, Category="Attributes")
	FRougeAttributeSet Attributes;

public:
	void ApplyHealthChange(float InValueChange);
	
	URougeActionSystemComponent();
};
