// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "I_Attacker.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UI_Attacker : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ASHENLANDS_API II_Attacker
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Attack)
	void OnPrimaryAttack();
	
};
