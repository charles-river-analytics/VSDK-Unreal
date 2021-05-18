// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LocomotionBase.h"
#include "../Pointers/PointerBase.h"
#include "LocomotionTeleportation.generated.h"

/**
 * Teleportation implementation of LocomotionBase
 * Will bind to the input (via its parent) - and then draw the typical "VR Spline" coming off a controller.
 *
 * Written by: Arthur Wollocko (awollocko@cra.com), 2020
 */
UCLASS()
class VSDKINPUTPLUGIN_API ALocomotionTeleportation : public ALocomotionBase
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ALocomotionTeleportation();

	/** Teleport Functionality */
	UPROPERTY(EditAnywhere)
		class USceneComponent* DestinationMarker;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* DestinationMarkerMesh;


	/** The pointer representation for the teleportation */
	UPROPERTY()
		APointerBase* pointer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VSDK | Teleportation")
		TSubclassOf<APointerBase> pointerBp;

	void UpdateDestinationMarker();

	UFUNCTION(BlueprintCallable)
		void DoLocomotion() override;
	UFUNCTION()
		void TeleportToDestinationEnd();


	/** Teleport Fade */

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VSDK | Teleportation")
		float TeleportFadeTime;				//  The amount of time the teleport fade should last for (total, both fade in + fade out)
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VSDK | Teleportation")
		FLinearColor TeleportFadeColor;		//  The color at which to fade to/from


	/** Adjustments for Destination Rotation -- [-1,1] value typically from a thumbstick */
	void DestinationRotationAdjustment(float amountFromThumbstickAxis);


	/** Enabling and disabling locomotion override to hide/show the teleport path and marker */
	void EnableLocomotion() override;
	void DisableLocomotion() override;


protected:
	UPROPERTY()
		USceneComponent* LocomotionRoot;
	/** Adjustments for rotation around the YAW due to thumbstick press */
	class AHand* ControllingActor;
	/** The current amount the thumbstick is adjusting the rotation by. This will be used to rotate the indicator around the YAW */
	float CurrentRotationAdjustment = 0.0;

	/** Allows the check to ensure the controlling actor is set before acting on it */
	UFUNCTION()
		void SetControllingActor();

public:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
};
