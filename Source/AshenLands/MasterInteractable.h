// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "I_Interactable.h"

#include "MasterInteractable.generated.h"

UCLASS()
class ASHENLANDS_API AMasterInteractable : public AActor, public II_Interactable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called when interacted with
	virtual void OnInteract_Implementation() override;
	
	virtual void OnFocus_Implementation() override;
	
	virtual void OnUnfocus_Implementation() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
