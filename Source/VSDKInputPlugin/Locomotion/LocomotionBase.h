// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LocomotionBase.generated.h"

/**
 * The base class that will define locomotion.
 * Inherit from this for different implementations
 * 
 * Written by: Arthur Wollocko (awollocko@cra.com), 2020
 */
UCLASS()
class VSDKINPUTPLUGIN_API ALocomotionBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALocomotionBase();

	// Keeps a reference to the player controller for input binding. 
	class APlayerController* PlayerController;

protected:
	
public:	
	virtual void BeginPlay() override;

	virtual void DoLocomotion();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VSDK | Locomotion")
		bool bLocomotionEnabled;

	UFUNCTION(BlueprintCallable)
		virtual void EnableLocomotion();

	UFUNCTION(BlueprintCallable)
		virtual void DisableLocomotion();

};
