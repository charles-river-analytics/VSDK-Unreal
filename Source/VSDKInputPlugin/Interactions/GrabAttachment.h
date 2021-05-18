// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InteractableProperty.h"
#include "GrabAttachment.generated.h"

// Forward declarations
class UInteractableGrab;

/**
 * The base class to implement different grabbing behaviors. Implement the TryGrab function to set up the
 * grabbing object and TryUngrab to release the object.
 *
 * This class does not need to be modified.
 *
 * Written by: Nicolas Herrera (nherrera@cra.com), 2020
 */
UCLASS(BlueprintType, Blueprintable)
class VSDKINPUTPLUGIN_API UGrabAttachment : public UInteractableProperty
{
	GENERATED_BODY()
	
public:
	UGrabAttachment();

	// Generalize as InteractableComponent in InteractableProperty?
	UPROPERTY()
		UInteractableGrab* InteractableGrab;

	UFUNCTION(BlueprintCallable, Category = VSDK)
		void SetInteractableGrab(UInteractableGrab* GrabType);

	UFUNCTION(BlueprintCallable, Category = VSDK)
		UInteractableGrab* GetInteractableGrab();

	UFUNCTION(BlueprintCallable, Category = VSDK)
		virtual void TryGrab(AActor* GrabberActor, AActor* PreviousGrabber);

	UFUNCTION(BlueprintCallable, Category = VSDK)
		virtual void TryUngrab(AActor* UngrabberActor);
};
