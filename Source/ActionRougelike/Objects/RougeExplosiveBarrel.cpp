// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeExplosiveBarrel.h"


// Sets default values
ARougeExplosiveBarrel::ARougeExplosiveBarrel()
{

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARougeExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ARougeExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

