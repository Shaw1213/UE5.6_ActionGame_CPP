// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeProjectileTeleport.h"


// Sets default values
ARougeProjectileTeleport::ARougeProjectileTeleport()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARougeProjectileTeleport::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARougeProjectileTeleport::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

