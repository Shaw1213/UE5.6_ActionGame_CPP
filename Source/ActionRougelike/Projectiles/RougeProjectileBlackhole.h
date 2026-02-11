// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RougeProjectile.h"
#include "GameFramework/Actor.h"
#include "RougeProjectileBlackhole.generated.h"

class UNiagaraComponent;

UCLASS()
class ACTIONROUGELIKE_API ARougeProjectileBlackhole : public ARougeProjectile
{
	GENERATED_BODY()
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UNiagaraComponent> LoopedNiagaraComponent;

public:
	ARougeProjectileBlackhole();
};
