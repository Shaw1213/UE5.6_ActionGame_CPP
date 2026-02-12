// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeProjectileBlackhole.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Engine/OverlapResult.h"


ARougeProjectileBlackhole::ARougeProjectileBlackhole()
{
	PrimaryActorTick.bCanEverTick = true;

	LoopedBlackHoleEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LoopedBlackHoleEffect"));
	LoopedBlackHoleEffect->SetupAttachment(RootComponent);
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComp->SetupAttachment(RootComponent);
	RadialForceComp->Radius = RadioForceRadius;
	RadialForceComp->ForceStrength = GravityStrength;
	RadialForceComp->Falloff = RIF_Linear;
	RadialForceComp->bAutoActivate = true;
	RadialForceComp->bIgnoreOwningActor = true;
	RadialForceComp->RemoveObjectTypeToAffect (UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn)); //ignore pawns, only affect physics objects
}

void ARougeProjectileBlackhole::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, BlackHoleEffect, GetActorLocation());

	GetWorldTimerManager().SetTimer(
		BlackHoleTimerHandle,
		this,
		&ARougeProjectileBlackhole::SelfDestroy,
		BlackHoleLifespan,//5 seconds
		false
		);
	
}

void ARougeProjectileBlackhole::SelfDestroy()
{
	Destroy();
}

void ARougeProjectileBlackhole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<FOverlapResult> Overlaps;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(GetInstigator());

	bool bHasOverlaps = GetWorld()->OverlapMultiByObjectType(
		Overlaps,
		GetActorLocation(),
		FQuat::Identity,
		FCollisionObjectQueryParams::AllDynamicObjects,
		FCollisionShape::MakeSphere(SphereComponent->GetScaledSphereRadius()),
		QueryParams
	);

	if (bHasOverlaps)
	{
		for (const FOverlapResult& Overlap : Overlaps)
		{
			UPrimitiveComponent* OverlapComp = Overlap.GetComponent();
			if (OverlapComp && OverlapComp->IsSimulatingPhysics())
			{
				Overlap.GetActor()->Destroy();
			}
		}
	}

	DrawDebugSphere(GetWorld(), GetActorLocation(), RadioForceRadius, 32, FColor::White);
}