// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeProjectileTeleport.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"


ARougeProjectileTeleport::ARougeProjectileTeleport()
{
	LoopedNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LoopedNiagaraComp"));
	LoopedNiagaraComponent->SetupAttachment(SphereComponent);
}

void ARougeProjectileTeleport::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComponent->OnComponentHit.AddDynamic(this, &ARougeProjectileTeleport::OnActorHit);
}

void ARougeProjectileTeleport::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(
		TeleportTimerHandle,
		this,
		&ARougeProjectileTeleport::TeleportInstigator,
		TeleportDelay,
		false
	);
}

void ARougeProjectileTeleport::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (bTeleportTriggered || OtherActor == GetInstigator())
	{
		return;
	}

	ProjectileMovementComponent->StopMovementImmediately();
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	GetWorldTimerManager().ClearTimer(TeleportTimerHandle);

	GetWorldTimerManager().SetTimer(
		TeleportTimerHandle,
		this,
		&ARougeProjectileTeleport::TeleportInstigator,
		TeleportDelay,
		false
	);
}

void ARougeProjectileTeleport::TeleportInstigator()
{
	if (bTeleportTriggered)
	{
		return;
	}

	bTeleportTriggered = true;

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, TeleportEffect, GetActorLocation());

	GetWorldTimerManager().SetTimer(
		TeleportTimerHandle,
		this,
		&ARougeProjectileTeleport::Teleport,
		TeleportDelay,
		false
	);
}

void ARougeProjectileTeleport::Teleport()
{
	APawn* InstigatorPawn = GetInstigator();
	if (InstigatorPawn)
	{
		InstigatorPawn->TeleportTo(GetActorLocation(), InstigatorPawn->GetActorRotation(), false, true);
	}

	Destroy();
	
}

