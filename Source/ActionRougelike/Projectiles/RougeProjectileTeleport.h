// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RougeProjectile.h"
#include "GameFramework/Actor.h"
#include "RougeProjectileTeleport.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class ACTIONROUGELIKE_API ARougeProjectileTeleport : public ARougeProjectile
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<UNiagaraComponent> LoopedNiagaraComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<UNiagaraSystem> TeleportEffect;
	
	FTimerHandle TeleportTimerHandle;
	
	float TeleportDelay = 0.2f;

	bool bTeleportTriggered = false;
	
	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	void TeleportInstigator();
	
	void Teleport();
	

public:
	ARougeProjectileTeleport();
	
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
};
