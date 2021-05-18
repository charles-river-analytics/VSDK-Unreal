// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InteractableObject.h"
#include "InteractableProperty.generated.h"

/**
 * The subset of UObjects for managing common components for InteractableObjects that are
 * not ActorComponents.
 *
 * Written by: Nicolas Herrera (nherrera@cra.com), 2020
 */
UCLASS()
class VSDKINPUTPLUGIN_API UInteractableProperty : public UObject
{
	GENERATED_BODY()

public:
	UInteractableProperty();

	UPROPERTY()
		AInteractableObject* InteractableOwner;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = VSDK)
		void BeginPlay();
	virtual void BeginPlay_Implementation();

	UFUNCTION(BlueprintCallable, Category = VSDK)
		void SetInteractableOwner(AInteractableObject* InteractOwner);

	UFUNCTION(BlueprintCallable, Category=VSDK)
		AInteractableObject* GetInteractableOwner();
};
