// Fill out your copyright notice in the Description page of Project Settings.


#include "RougeInteractionComponent.h"

#include "RougeGameTypes.h"
#include "Core/RougeInteractionInterface.h"
#include "Engine/OverlapResult.h"


// Sets default values for this component's properties
URougeInteractionComponent::URougeInteractionComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

}

void URougeInteractionComponent::Interact()
 {
	IRougeInteractionInterface* InteractionInterface = Cast<IRougeInteractionInterface>(SelectedActor);
	if (InteractionInterface)
	{
		InteractionInterface->Interact();
	}
 }

void URougeInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	APlayerController* PC = CastChecked<APlayerController>(GetOwner());
	
	FVector Center = PC->GetPawn()->GetActorLocation();
	
	
	ECollisionChannel CollisionChannel = COLLISION_INTERACTION;
	
	FCollisionShape Shape;
	Shape.SetSphere(InteractionRadius);
	
	TArray<FOverlapResult> Overlaps;
	
	GetWorld()->OverlapMultiByChannel(Overlaps, Center, FQuat::Identity, CollisionChannel, Shape);
	
	AActor* BestActor = nullptr;
	float HighestDot = -1.0;
	
	for (FOverlapResult& Overlap : Overlaps)
	{	
		FVector OverlapLocation = Overlap.GetActor()->GetActorLocation();
		
		FVector OverlapDirection = (OverlapLocation-Center).GetSafeNormal();
		
		float DotResult = FVector::DotProduct(OverlapDirection,PC->GetControlRotation().Vector());
		if (DotResult > HighestDot)
		{
			BestActor = Overlap.GetActor();
			HighestDot = DotResult;
		}
		
		//Debug Draw
		DrawDebugBox(GetWorld(),OverlapLocation, FVector(50.f), FColor::Red);
        FString DebugString = FString::Printf(TEXT("Dot: %f"), DotResult);
        DrawDebugString(GetWorld(),OverlapLocation, DebugString, nullptr, FColor::White, 0.0f, true);
	}
	
	SelectedActor = BestActor;
	
	if (BestActor)
	{
		DrawDebugBox(GetWorld(),BestActor->GetActorLocation(), FVector(60.f), FColor::Green);
	}
	
	DrawDebugSphere(GetWorld(), Center, InteractionRadius, 32, FColor::White);
}

