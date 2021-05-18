// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractableComponent.h"
#include "InteractableAxisControl.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "InteractableRotator.generated.h"


/**
 * Manipulates an Interactable Object by forcing the rotation among the given axes. By default, 
 * if an axis is not specified to rotate, then it is locked to the start rotation.
 *
 * TODO VIRTUOSO-49 Implement 3D editor widget to show limits
 *
 * Written by: Nicolas Herrera (nherrera@cra.com), 2020
 */
UCLASS( ClassGroup=(VSDK), meta=(BlueprintSpawnableComponent) )
class VSDKINPUTPLUGIN_API UInteractableRotator : public UInteractableAxisControl
{
	GENERATED_BODY()

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VSDK | Interactable Rotator")
		FVector MinRotationLimit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VSDK | Interactable Rotator")
		FVector MaxRotationLimit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VSDK | Interactable Rotator")
		FRotator StartingRotation;

	// Property used to calculate rotations
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VSDK | Interactable Rotator")
		FVector PivotLocation;

	// Property used to manually set the pivot location
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VSDK | Interactable Rotator")
		FVector PivotOffset;

	UFUNCTION()
		FVector GetCurrentPivotLocation();

	/* InteractableAxisControl Override */
	virtual void SetupAxesConstraints() override;

	virtual void SetupStartValues() override;

	virtual void MaintainAxesConstraints() override;

	virtual float Normalize(int axis, float value) override;

	virtual void CheckLimits(int axis, float value) override;

	virtual void SetAxisValue(int axis, int value, bool teleport = false) override;

	virtual float GetAbsoluteFromNormalize(int axis, float normalizedValue) override;

	virtual void MoveOverTime() override;

	/** UActorComponent Overrides */
	virtual void BeginPlay() override;
};
