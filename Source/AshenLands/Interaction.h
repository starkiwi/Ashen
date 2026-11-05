// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "TimerManager.h"


#include "Interaction.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ASHENLANDS_API UInteraction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteraction();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction)
	float InteractionRadius = 100.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Interaction)
	USphereComponent* SphereCollider;
	
	UFUNCTION(BlueprintCallable, Category = Interaction)
	void UpdateInteractable();
	
	// To be called when collision starts
	UFUNCTION(BlueprintCallable, Category = Interaction)
	void OnInteractOverlap(class UPrimitiveComponent* ThisComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// To be called when collision ends
	UFUNCTION(BlueprintCallable, Category = Interaction)
	void OnInteractOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	TArray<AActor> NearbyInteractables;
	
	class AActor* CurrentInteractable;
	
	FTimerHandle TimerHandle;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
