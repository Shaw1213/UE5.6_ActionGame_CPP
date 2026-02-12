// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RougeProjectile.h"
#include "RougeProjectileBlackhole.generated.h"

class URadialForceComponent;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class ACTIONROUGELIKE_API ARougeProjectileBlackhole : public ARougeProjectile
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<UNiagaraSystem> BlackHoleEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<UNiagaraComponent> LoopedBlackHoleEffect;
	
	UPROPERTY(EditDefaultsOnly, Category="Gravity")
	TObjectPtr<URadialForceComponent> RadialForceComp;
	
	
	float BlackHoleLifespan = 5.0f;
	
	UPROPERTY(EditDefaultsOnly, Category="Gravity")
	float RadioForceRadius = 500.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Gravity")
	float GravityStrength = -1000000.f ; //negative value to pull objects towards the center of the black hole
	
	FTimerHandle BlackHoleTimerHandle;
	
	void SelfDestroy();


public:
	ARougeProjectileBlackhole();

	virtual void PostInitializeComponents() override;
	
	virtual void Tick(float DeltaTime) override;

};
