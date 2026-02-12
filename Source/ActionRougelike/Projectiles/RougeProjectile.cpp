// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"



ARougeProjectile::ARougeProjectile()
{
	
	//Collision component and set sphere
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	RootComponent = SphereComponent;
	SphereComponent->SetSphereRadius(16.0f);
	SphereComponent->SetCollisionProfileName("Projectile");
	
	//Movement and collision components
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	ProjectileMovementComponent->InitialSpeed = 1000.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;

}

void ARougeProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComponent->IgnoreActorWhenMoving(GetInstigator(), true);
}


