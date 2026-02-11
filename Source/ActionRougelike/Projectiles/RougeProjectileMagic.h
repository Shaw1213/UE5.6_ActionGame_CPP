// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RougeProjectile.h"
#include "RougeProjectileMagic.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
class UAudioComponent;

UCLASS(Abstract)
class ACTIONROUGELIKE_API ARougeProjectileMagic : public ARougeProjectile
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UDamageType> DmgTypeClass = UDamageType::StaticClass();
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Audio")
	TObjectPtr<USoundBase> ExplosionSound;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UNiagaraComponent> LoopedNiagaraComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UAudioComponent> LoopedAudioComponent;
	
	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
public:
	
	virtual void PostInitializeComponents() override;
	
	ARougeProjectileMagic();
};
