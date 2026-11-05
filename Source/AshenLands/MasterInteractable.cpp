// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterInteractable.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AMasterInteractable::AMasterInteractable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMasterInteractable::BeginPlay()
{
	Super::BeginPlay();
}

void AMasterInteractable::OnInteract_Implementation()
{
	this->Destroy();
}

void AMasterInteractable::OnFocus_Implementation()
{
	UStaticMeshComponent* Mesh = FindComponentByClass<UStaticMeshComponent>();
	Mesh->SetRenderCustomDepth(true);
	Mesh->SetCustomDepthStencilValue(2);
	UKismetSystemLibrary::PrintString(
		this,				// World context object
		"Object Selected",	// Message
		true,				// Print to screen?
		true,				// Print to console?
		FLinearColor(0.0f, 0.66f, 1.0f, 1.0f), // Color
		2.0f				// Duration
	);
}

void AMasterInteractable::OnUnfocus_Implementation()
{
	UStaticMeshComponent* Mesh = FindComponentByClass<UStaticMeshComponent>();
	Mesh->SetCustomDepthStencilValue(0);
	Mesh->SetRenderCustomDepth(false);
}

// Called every frame
void AMasterInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
