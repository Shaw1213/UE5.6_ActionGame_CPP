// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RougeExplosiveBarrel.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class ACTIONROUGELIKE_API ARougeExplosiveBarrel : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARougeExplosiveBarrel();

protected:

	UPROPERTY(EditDefaultsOnly, Category="StaticMesh")
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;
	
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UNiagaraComponent> ExplosionEffect;
	
	UPROPERTY(EditDefaultsOnly, Category="Effects")
	TObjectPtr<UNiagaraComponent> LoopedBurningEffect;
	
	UPROPERTY(EditDefaultsOnly, Category="Audio")
	TObjectPtr<UAudioComponent> BurningAudioComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Audio")
	TObjectPtr<UAudioComponent> ExplodeAudioComponent;
	
	FTimerHandle ExplosionTimerHandle;
	
	void Explode();
	
	void StartBurning();
	
	UPROPERTY(EditDefaultsOnly, Category="BurningTime")
	float BurningTicks = 3.0f;
	
	bool bHasStartedBurning = false;

	//Taking dmg
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;
	
	//play 

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
