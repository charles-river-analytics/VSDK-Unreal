// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Selectable.generated.h"

/**
 * Interface for selecting an AInteractableObject. Implement the two functions, ExecuteSelect and
 * ExecuteDeselct, for selecting/deselecting the object.
 *
 * This class does not need to be modified.
 *
 * Written by: Nicolas Herrera (nherrera@cra.com), 2020
 */
UINTERFACE()
class USelectable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for selecting an AInteractableObject. Implement the two functions, ExecuteSelect and
 * ExecuteDeselct, for selecting/deselecting the object.
 *
 * Written by: Nicolas Herrera (nherrera@cra.com), 2020
 */
class VSDKINPUTPLUGIN_API ISelectable
{
	GENERATED_BODY()

public:
	UFUNCTION()
		virtual void SetSelectable(UInteractableSelect* GivenInteractableSelect);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void TrySelectAction(AActor* ObjectSelecting);
	virtual void TrySelectAction_Implementation(AActor* ObjectSelecting);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void TryDeselectAction(AActor* ObjectDeselecting);
	virtual void TryDeselectAction_Implementation(AActor* ObjectDeselecting);
};