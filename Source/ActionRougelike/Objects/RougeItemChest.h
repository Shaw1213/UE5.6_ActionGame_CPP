// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/RougeInteractionInterface.h"
#include "GameFramework/Actor.h"
#include "RougeItemChest.generated.h"

UCLASS()
class ACTIONROUGELIKE_API ARougeItemChest : public AActor, public IRougeInteractionInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BaseMeshComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> LidMeshComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	float CurrentLidPitch = 0.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	float TargetLidPitch = 120.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	float OpenLidSpeed = 50.0f;
	
	UFUNCTION(BLueprintImplementableEvent)
	void ChestAnimationComplete();

public:
	
	virtual void Interact_Implementation() override;
	
	virtual void Tick(float DeltaTime) override;
	
	ARougeItemChest();
};
