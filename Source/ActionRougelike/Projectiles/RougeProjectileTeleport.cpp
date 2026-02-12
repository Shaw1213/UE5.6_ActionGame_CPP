// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeProjectileTeleport.h"
#include "Components/SphereComponent.h"
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
}

