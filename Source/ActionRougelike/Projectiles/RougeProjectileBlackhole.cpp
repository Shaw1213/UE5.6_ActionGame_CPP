// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeProjectileBlackhole.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

ARougeProjectileBlackhole::ARougeProjectileBlackhole()
{
	LoopedNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LoopedNiagaraComp"));
	LoopedNiagaraComponent->SetupAttachment(SphereComponent);
}

