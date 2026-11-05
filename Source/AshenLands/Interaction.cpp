// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction.h"

#include "I_Interactable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h" 
#include "TimerManager.h"

// Sets default values for this component's properties
UInteraction::UInteraction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UInteraction::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (Owner && Owner->GetRootComponent())
	{
		// Add interaction radius
		SphereCollider = NewObject<USphereComponent>(Owner, TEXT("SphereCollider"));
		SphereCollider->SetupAttachment(Owner->GetRootComponent());
		SphereCollider->SetSphereRadius(InteractionRadius);
		SphereCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		SphereCollider->SetGenerateOverlapEvents(true);
		SphereCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECR_Overlap);
		SphereCollider->SetHiddenInGame(false); // Visualize sphere
		
		// Define overlap (collision)
		SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &UInteraction::OnInteractOverlap);
		SphereCollider->OnComponentEndOverlap.AddDynamic(this, &UInteraction::OnInteractOverlapEnd);
		SphereCollider->RegisterComponent();
	}
	
}

void UInteraction::OnInteractOverlap(class UPrimitiveComponent* ThisComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner()) return;
	
	if (OtherActor && OtherActor->Implements<UI_Interactable>())
	{
		CurrentInteractable = OtherActor;
		II_Interactable::Execute_OnFocus(CurrentInteractable);
		UKismetSystemLibrary::PrintString(
			this,                                    // World context object
			"Object Found!",                         // Message
			true,                                    // Print to screen?
			true,                                    // Print to console?
			FLinearColor(0.0f, 0.66f, 1.0f, 1.0f),   // Color
			2.0f                                     // Duration
		);
	}
}

void UInteraction::OnInteractOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == CurrentInteractable)
	{
		II_Interactable::Execute_OnUnfocus(CurrentInteractable);
		CurrentInteractable = nullptr;
	}
}

void UInteraction::UpdateInteractable()
{
	if (IsValid(CurrentInteractable))
	{
		II_Interactable::Execute_OnInteract(CurrentInteractable);
	}
}


// Called every frame
void UInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteraction::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (SphereCollider)
	{
		SphereCollider->DestroyComponent();
		SphereCollider = nullptr;
	}
	Super::EndPlay(EndPlayReason);
}

