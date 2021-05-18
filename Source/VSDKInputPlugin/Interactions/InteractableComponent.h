// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableObject.h"
#include "InteractableComponent.generated.h"

/**
 * The base UActorComponent for enabling behaviors on interactable objects. By inheriting
 * this class and attaching to an AInteractableObject, it will be exposed to the interactable
 * object and be easily triggered from the interactable object class.
 *
 * Written by: Nicolas Herrera (nherrera@cra.com), 2020
 */
UCLASS(Blueprintable, ClassGroup = (VSDK), meta = (BlueprintSpawnableComponent))
class VSDKINPUTPLUGIN_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	class AInteractableObject* InteractableObject;

	FName ComponentName;

public:
	UInteractableComponent();

	// Return true if the componet has been started but has not been stopped
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bIsComponentActive;

	// Returns the name of the interactable component
	UFUNCTION(BlueprintCallable)
		FName GetComponentName();

	// Return true if the StartComponent can be called
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		bool IsActionable();
	virtual bool IsActionable_Implementation();
};
