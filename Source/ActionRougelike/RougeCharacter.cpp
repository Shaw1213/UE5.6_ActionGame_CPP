// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeCharacter.h"

#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

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
	
}

// Called when the game starts or when spawned
void ARougeCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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

// Called every frame
void ARougeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARougeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Binding Input Actions
	UEnhancedInputComponent * EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	EnhancedInput->BindAction(Input_Move, ETriggerEvent :: Triggered, this, &ARougeCharacter::Move );
	
	EnhancedInput->BindAction(Input_Look, ETriggerEvent :: Triggered, this, &ARougeCharacter::Look );

}

