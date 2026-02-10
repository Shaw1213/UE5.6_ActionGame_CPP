// Fill out your copyright notice in the Description page of Project Settings.


#include "RougePlayerController.h"

#include "RougeInteractionComponent.h"
#include "EnhancedInputComponent.h"

ARougePlayerController::ARougePlayerController()
{
	InteractionComp = CreateDefaultSubobject<URougeInteractionComponent>(TEXT("InteractionComp"));
}

void ARougePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent * EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	
	EnhancedInput->BindAction(Input_Interact, ETriggerEvent :: Triggered, this, &ARougePlayerController::StartInteract);
}

void ARougePlayerController::StartInteract()
{
	InteractionComp-> Interact();
}