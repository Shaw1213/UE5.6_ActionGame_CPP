// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeItemChest.h"

#include "DataWrappers/ChaosVDParticleDataWrapper.h"


// Sets default values
ARougeItemChest::ARougeItemChest()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	BaseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComp"));
	RootComponent = BaseMeshComponent;
	BaseMeshComponent->SetCollisionProfileName("Interaction");
	
	LidMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMeshComp"));
	LidMeshComponent->SetupAttachment(BaseMeshComponent);
}

void ARougeItemChest::Interact()
{
	//play open animation
	SetActorTickEnabled(true);
}

void ARougeItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CurrentLidPitch = FMath::FInterpConstantTo(CurrentLidPitch, TargetLidPitch, DeltaTime, OpenLidSpeed);
	
	LidMeshComponent->SetRelativeRotation(FRotator(CurrentLidPitch, 0.0f, 0.0f));
	
	if (FMath::IsNearlyEqual(CurrentLidPitch, TargetLidPitch))
	{
		//Animation is done, stop ticking
		SetActorTickEnabled(false);
		
		ChestAnimationComplete();
	}
}

