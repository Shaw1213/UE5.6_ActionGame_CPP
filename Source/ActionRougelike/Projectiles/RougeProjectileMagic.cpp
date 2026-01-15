// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeProjectileMagic.h"
#include "RougeProjectileMagic.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ARougeProjectileMagic::ARougeProjectileMagic()
{
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	RootComponent = SphereComponent;
	SphereComponent->SetSphereRadius(16.0f);
	SphereComponent->SetCollisionProfileName("Projectile");
	
	LoopedNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LoopedNiagaraComp"));
	LoopedNiagaraComponent->SetupAttachment(SphereComponent);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	ProjectileMovementComponent->InitialSpeed = 200.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;

}

// Called when the game starts or when spawned
void ARougeProjectileMagic::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	SphereComponent->OnComponentHit.AddDynamic(this, &ARougeProjectileMagic::OnActorHit );
}

// Called when projectile hits something
void ARougeProjectileMagic::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// @todo: Create a dmg type for magic projectile
	TSubclassOf<UDamageType> DmgTypeClass = UDamageType::StaticClass();
	UGameplayStatics::ApplyDamage(OtherActor, 10.f, GetInstigatorController(), this,DmgTypeClass);
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect,GetActorLocation());
	
	Destroy();
}


