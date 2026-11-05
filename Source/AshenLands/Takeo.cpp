// Fill out your copyright notice in the Description page of Project Settings.
#include "Takeo.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interaction.h"
#include "KismetTraceUtils.h"


ATakeo::ATakeo()
{
	// ---------------------CAMERA------------------------
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->SocketOffset = FVector(0.0f, 0.0f, 70.0f);
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	SideCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("SideCamera"));
	SideCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	SideCamera->bUsePawnControlRotation = false;
	SideCamera->bAutoActivate = true;
}

// --------------------- INPUT --------------------------------
void ATakeo::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATakeo::MoveInput);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ATakeo::AttackInput);
	}
}

void ATakeo::MoveInput(const FInputActionValue& InValue)
{
	MoveActionValue = InValue.Get<FVector2D>();
	// x movement
	this->AddMovementInput(FVector(1, 0, 0), MoveActionValue.X);
	// y movement
	this->AddMovementInput(FVector(0, -1, 0), MoveActionValue.Y);
}

void ATakeo::AttackInput(const FInputActionValue& InValue)
{
	if (!IsAttacking)
	{
		//stop movement 
		IsAttacking = true;
		GetCharacterMovement()->MovementMode = MOVE_None;

		//set cooldown timer
		GetWorldTimerManager().SetTimer(
			TimerHandle,
			this,
			&ATakeo::AttackReset,
			AttackCooldown,
			false
		);
	}
}

// -------------------- ATTACK -------------------------------
void ATakeo::OnPrimaryAttack_Implementation()
{
	UKismetSystemLibrary::PrintString(
		this, // World context object
		"ATTACK", // Message
		true, // Print to screen?
		true, // Print to console?
		FLinearColor(0.0f, 0.66f, 1.0f, 1.0f), // Color
		1.0f // Duration
	);
	
	
	TArray<FHitResult> OutResults;
	FCollisionQueryParams Params(SCENE_QUERY_STAT(TakeoPrimaryAttack), false, this);
	
	FCollisionShape MySphere = FCollisionShape::MakeSphere(AttackRadius);
	const bool bHit = GetWorld()->SweepMultiByChannel(
		OutResults, 
		GetActorLocation(), 
		FindAttackOffset(), 
		FQuat::Identity, 
		ECC_GameTraceChannel2, 
		MySphere,
		Params);
	
	DrawDebugSphereTraceMulti(
		GetWorld(),
		GetActorLocation(),
		FindAttackOffset(),
		AttackRadius,
		EDrawDebugTrace::ForDuration,
		bHit,
		OutResults,
		FColor(255, 0, 0),
		FColor(255, 0, 0),
		1.0f
		);
	
	// for (const FHitResult& Hit : OutResults)
	// {
	// 	AActor* HitActor = Hit.GetActor();
	// 	if (!IsValid(HitActor)) continue; // this guard is the one that matters
 //
	// 	// Apply damage, etc.
	
}

FVector ATakeo::FindAttackOffset()
{
	FVector OffsetCalc = FVector((MoveActionValue.X * AttackOffset.X), (MoveActionValue.Y * AttackOffset.Y), 0);
	return GetActorLocation() + OffsetCalc;
}

void ATakeo::AttackReset()
{
	IsAttacking = false;
	GetCharacterMovement()->MovementMode = MOVE_Walking;
}

void ATakeo::BeginPlay()
{
	Super::BeginPlay();

	if (!PlayerController)
	{
		PlayerController = Cast<APlayerController>(GetController());
	}
}

void ATakeo::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
