// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AshenLandsBaseController.generated.h"

/**
 * 
 */
UCLASS()
class ASHENLANDS_API AAshenLandsBaseController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	class UInputMappingContext* MappingContext;
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	class UEnhancedInputLocalPlayerSubsystem* EnhancedInput;
};
