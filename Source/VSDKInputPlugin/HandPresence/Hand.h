// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interactions/InteractableGrab.h"
#include "../Interactions/InteractableUse.h"
#include "../Interactions/Selector.h"
#include "../Character/VSDKCharacter.h"
#include <MotionControllerComponent.h>
#include "Hand.generated.h"

/*
	This delegate is used when the Hand Component interacts with objects.
	The first param is the Hand Component sending the event
	The second param is the other object, which will never be null
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHandAction, AHand*, HandSender, AInteractableObject*, OtherObject);

/**
 * Responsible for a single HAND, encapsulating both motion controllers and hand tracking.
 * Spawned as an actor, at runtime by the Character
 *
 * Written by: Arthur Wollocko (awollocko@cra.com), Dan Duggan (dduggan@cra.com), 2021
 */
UCLASS()
class VSDKINPUTPLUGIN_API AHand : public AActor, public ISelector
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHand();

	/** Setup Components on hands */
	UPROPERTY(EditAnywhere)
		class UVirtuosoMotionController* MotionController; 

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* HandMesh;

	UPROPERTY(VisibleAnywhere)
		AVSDKCharacter* ControllingCharacter;

	/** Interaction functionality - Provide components for different interactions */
	//UPROPERTY(EditAnywhere)
		//UGrabber* VGrabber;

	// Note: This only allows the hand to have one interactable object be selected
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		AInteractableObject* CurrentSelectedObject;

	UPROPERTY()
		UInteractableGrab* CurrentSelectedInteractableGrab;

	UPROPERTY()
		UInteractableUse* CurrentSelectedInteractableUse;

	/** ENUM for Which hand this object represents */
	UPROPERTY(VisibleAnywhere)
		EControllerHand Hand;

protected:

public:	

	/** Configure the hand setup -- Bind to VSDK character */
	void SetHand(EControllerHand HandToSet);
	FORCEINLINE void SetVSDKCharacter(class AVSDKCharacter* Character) { ControllingCharacter = Character; };

	/** Interaction Functions -- likely delegate to interaction components (TODO: T3) */
	void Grab();
	void DropCurrent();
	void Use();
	void StopUse();

	/* Events */

	// Event called when an object is successfully grabbed
	UPROPERTY(EditAnywhere, BlueprintAssignable, Category = "VSDK")
		FOnHandAction OnHandGrab;

	// Event called when an object is successfully un-grabbed
	UPROPERTY(EditAnywhere, BlueprintAssignable, Category = "VSDK")
		FOnHandAction OnHandUnGrab;

	// Event called when an object is successfully used
	UPROPERTY(EditAnywhere, BlueprintAssignable, Category = "VSDK")
		FOnHandAction OnHandUse;

	// Event called when an object is no longer being used
	UPROPERTY(EditAnywhere, BlueprintAssignable, Category = "VSDK")
		FOnHandAction OnHandStopUse;

	// Event called when an object is successfully selected
	UPROPERTY(EditAnywhere, BlueprintAssignable, Category = "VSDK")
		FOnHandAction OnHandSelect;

	// Event called when an object is successfully deselected
	UPROPERTY(EditAnywhere, BlueprintAssignable, Category = "VSDK")
		FOnHandAction OnHandDeselect;

	/** ISelector Implementation */
	void OnInteractableBeginSelect(AInteractableObject* SelectedObject) override;

	void OnInteractableEndSelect(AInteractableObject* DeselectedObject) override;
};
