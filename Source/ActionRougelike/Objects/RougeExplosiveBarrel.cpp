// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeExplosiveBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ARougeExplosiveBarrel::ARougeExplosiveBarrel()
{

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	RootComponent = StaticMeshComp;
	
	//Audio
	BurningAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("BurningAudioComp"));
	BurningAudioComponent->SetupAttachment(RootComponent);
	BurningAudioComponent->bAutoActivate = false;
	
	ExplodeAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ExplodeAudioComp"));
	ExplodeAudioComponent->SetupAttachment(RootComponent);
	ExplodeAudioComponent->bAutoActivate = false;
	
	//Effect 
	LoopedBurningEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("BurningEffect"));
	LoopedBurningEffect->SetupAttachment(RootComponent);
	LoopedBurningEffect->bAutoActivate = false;
	ExplosionEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ExplosionEffect"));

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


void ARougeExplosiveBarrel::Explode()
{
	//spawn explosion effect
	if (ExplosionEffect)
	{
		UNiagaraFunctionLibrary :: SpawnSystemAtLocation(
			this,
			ExplosionEffect->GetAsset(),
			GetActorLocation(),
			GetActorRotation()
			);
	}
	
	//play explosion sound
	if (ExplodeAudioComponent)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			ExplodeAudioComponent->Sound,
			GetActorLocation(),
			GetActorRotation()
			);
	}
	
	//TODO : Apply radial damage
	
	
	Destroy();
	
}

void ARougeExplosiveBarrel::StartBurning()
{
	if (BurningAudioComponent && LoopedBurningEffect)
	{
		BurningAudioComponent->Play();
		LoopedBurningEffect->Activate();
	}
	
	GetWorldTimerManager().SetTimer(
		ExplosionTimerHandle,
		this,
		&ARougeExplosiveBarrel::Explode,
		BurningTicks,
		false
		);
	
}

float ARougeExplosiveBarrel::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
                                        class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (!bHasStartedBurning)
	{
		bHasStartedBurning = true;
		StartBurning();
	}

	return ActualDamage;
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

