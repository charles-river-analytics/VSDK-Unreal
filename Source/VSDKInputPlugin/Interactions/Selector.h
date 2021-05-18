// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableObject.h"
#include "Selector.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USelector : public UInterface
{
	GENERATED_BODY()
};

/**
 * Allows the implementing class to receive notification from the Interactable Object when
 * it is selected/deselected.
 *
 * Written by: Nicolas Herrera (nherrera@cra.com), 2020
 */
class VSDKINPUTPLUGIN_API ISelector
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION()
		virtual void OnInteractableBeginSelect(AInteractableObject* SelectedObject) = 0;

	UFUNCTION()
		virtual void OnInteractableEndSelect(AInteractableObject* DeselectedObject) = 0;
};
