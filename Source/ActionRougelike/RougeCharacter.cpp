// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeCharacter.h"

#include "Projectiles/RougeProjectileMagic.h"
#include "EnhancedInputComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARougeCharacter::ARougeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Setting up SpringArm and Camera Components
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	MuzzleSocketName = "Muzzle_01";
}

// Called when the game starts or when spawned
void ARougeCharacter::BeginPlay()
{
	JumpMaxCount = JumpMaxCountNum; // Allow double jump
	Super::BeginPlay();
}

// Called to bind functionality to input
void ARougeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Binding Input Actions
	UEnhancedInputComponent * EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInput->BindAction(Input_Move, ETriggerEvent :: Triggered, this, &ARougeCharacter::Move );
	
	EnhancedInput->BindAction(Input_Look, ETriggerEvent :: Triggered, this, &ARougeCharacter::Look );
	
	EnhancedInput->BindAction(Input_Jump, ETriggerEvent :: Triggered, this, &ARougeCharacter::Jump );
	
	EnhancedInput->BindAction(Input_Jump,ETriggerEvent :: Completed, this, &ACharacter::StopJumping );
	
	EnhancedInput->BindAction(Input_PrimaryAttack, ETriggerEvent :: Triggered, this, &ARougeCharacter::PrimaryAttack );

}

void ARougeCharacter::Move(const FInputActionValue& InValue)
{
	FVector2d InputValue = InValue.Get<FVector2d>();
	
	//FVector MoveDirection = FVector(InputValue.X , InputValue.Y, 0.f);
	
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.f;
	
	// Forward Movement
	AddMovementInput(ControlRot.Vector(), InputValue.X);
	
	// Sideway Movement
	FVector RightDirection = ControlRot.RotateVector(FVector::RightVector);
	AddMovementInput(RightDirection, InputValue.Y);
}

void ARougeCharacter::Look(const FInputActionInstance& InValue)
{
	FVector2d InputValue = InValue.GetValue().Get<FVector2d>();
	
	AddControllerPitchInput(InputValue.Y);
	AddControllerYawInput(InputValue.X);
}

void ARougeCharacter::PrimaryAttack()
{
	
	PlayAnimMontage(AttackMontage);
	
	FTimerHandle AttackTimerHandle;
	
	const float AttackDelayTime = 0.2f;
	
	UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect, GetMesh(), MuzzleSocketName,
		FVector::ZeroVector ,FRotator::ZeroRotator,EAttachLocation::Type::SnapToTarget, true);
	
	UGameplayStatics::PlaySound2D(this, CastingSound);
	
	GetWorldTimerManager().SetTimer(AttackTimerHandle,this, &ARougeCharacter::AttackTimerElapsed,AttackDelayTime);
	
}

void ARougeCharacter::AttackTimerElapsed()
{
	FVector SpawnLocation = GetMesh()->GetSocketLocation(MuzzleSocketName);;
 	FRotator SpawnRotation = GetControlRotation();
 	FActorSpawnParameters SpawnParams;
 	SpawnParams.Instigator = this;
 	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; // Ensures the projectile spawns even if there's a collision
 
 	AActor* NewProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
	
	MoveIgnoreActorAdd(NewProjectile);
}

void ARougeCharacter::Jump()
{
	//First Jump
	if (JumpCurrentCount == 0 && CanJump())
	{
		Super::Jump();
	}
	
	//Second Jump - redirecting 
	if (JumpCurrentCount == 1 && JumpCurrentCount < JumpMaxCount)
	{
		UCharacterMovementComponent * MovementComp = GetCharacterMovement();
		
		//Get last input direction 
		FVector LastInput = MovementComp->GetLastInputVector();
		
		//Calculate new velocity
		// Apply redirect
		FVector NewVelocity;
		NewVelocity.X = LastInput.X * AirRedirectionStrength;
		NewVelocity.Y = LastInput.Y * AirRedirectionStrength;
		NewVelocity.Z = DoubleJumpForce;
        
		MovementComp->Velocity = NewVelocity;
        
		bPressedJump = true;
		JumpCurrentCount++;
	}
}

// Called every frame
void ARougeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



