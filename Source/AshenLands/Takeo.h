// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"

// Camera
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Input
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Controller.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "TimerManager.h"

// Interaction
#include "Interaction.h"

// Attacking
#include "I_Attacker.h"

#include "Takeo.generated.h"

/**
 * 
 */
UCLASS()
class ASHENLANDS_API ATakeo : public APaperZDCharacter, public II_Attacker
{
	GENERATED_BODY()
	
public:
	ATakeo();
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	
public:
	
	// ------------------ Camera -----------------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* SideCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* SpringArm;
	
	
	
	// -------------------  Input  --------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputAction* AttackAction;
	
protected:
	// Sets up controller and actions
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	FVector2D MoveActionValue;

	// Handles input for move
	void MoveInput(const FInputActionValue& InValue);
	
	// Handles input for attack (animation handled in blueprint)
	void AttackInput(const FInputActionValue& InValue);
	
	
	
	// ------------------------- Attack -----------------------------
public:
	bool IsAttacking = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	FVector AttackOffset = FVector(50.f, 50.f, 0.f);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float AttackRadius = 50.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float AttackCooldown = 1.0f;
	
protected:
	virtual void OnPrimaryAttack_Implementation() override;
	
	FVector FindAttackOffset();
	
	FTimerHandle TimerHandle;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	APlayerController* PlayerController;
	
	void AttackReset();
};

