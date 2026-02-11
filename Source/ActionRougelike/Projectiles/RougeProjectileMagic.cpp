// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeProjectileMagic.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

ARougeProjectileMagic::ARougeProjectileMagic()
{
	
	LoopedNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LoopedNiagaraComp"));
	LoopedNiagaraComponent->SetupAttachment(SphereComponent);
	
	LoopedAudioComponent  = CreateDefaultSubobject<UAudioComponent>(TEXT("LoopedSoundComp"));
	LoopedAudioComponent->SetupAttachment(SphereComponent);
	
}

// Called when the game starts or when spawned
void ARougeProjectileMagic::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SphereComponent->OnComponentHit.AddDynamic(this, &ARougeProjectileMagic::OnActorHit );
	
	SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);// Ignore the actor that spawned this projectile
}

// Called when projectile hits something
void ARougeProjectileMagic::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FVector HitDirection = GetActorRotation().Vector();
	
	UGameplayStatics::ApplyPointDamage(OtherActor, 10.f, HitDirection , Hit, GetInstigatorController(), this,DmgTypeClass);
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect,GetActorLocation());
	
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation(), FRotator::ZeroRotator);
	
	Destroy();
}


