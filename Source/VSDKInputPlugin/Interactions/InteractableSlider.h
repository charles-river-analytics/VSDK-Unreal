// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractableComponent.h"
#include "InteractableAxisControl.h"
#include "InteractableSlider.generated.h"

/**
 * Manipulates an Interactable Object by keeping it's positions laterally along the given axes. By default, 
 * if an axis is not specified to slide, then it is locked to the start position.
 *
 * TODO VIRTUOSO-49 Implement 3D editor widget to show limits
 *
 * Written by: Nicolas Herrera (nherrera@cra.com), 2020
 */
UCLASS(ClassGroup = (VSDK), meta = (BlueprintSpawnableComponent))
class VSDKINPUTPLUGIN_API UInteractableSlider : public UInteractableAxisControl
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VSDK | Interactable Slider")
		FVector SlideMinDistances;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VSDK | Interactable Slider")
		FVector SlideMaxDistances;

	/* InteractableAxisControl Override */
	virtual void SetupAxesConstraints() override;

	virtual void SetupStartValues() override;

	virtual void MaintainAxesConstraints() override;

	virtual float Normalize(int axis, float newPosition) override;

	virtual void CheckLimits(int axis, float newPosition) override;

	virtual void SetAxisValue(int axis, int value, bool teleport = false) override;

	virtual float GetAbsoluteFromNormalize(int axis, float normalizedValue) override;

	virtual void MoveOverTime() override;
};
