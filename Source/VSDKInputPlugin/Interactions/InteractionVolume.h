// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObject.h"
#include "FilterInteractables.h"
#include "Components/ShapeComponent.h"
#include "Components/SceneComponent.h"
#include "Components/PrimitiveComponent.h"
#include "InteractionVolume.generated.h"

/** Delegate Signatures */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractionVolumeSignature, AActor*, InteractingActor);

/**
 * The Interaction Volume class provides detecting overlap events with our InteractableObject
 * class and controller/hand classes of the user as well as an additional 'use' functionality that
 * allows for further rich and complex interactions. Since this is a scene component, it
 * provides these events and functionality in Blueprint as well. Extending the Interaction Volume
 * can allows for things such as detecting additional events such as what button was pressed on
 * the controller or what events an interactable object gives off when within the volume. In order
 * to generate overlap events, a BoxCollision is generated when this class is added. Use the Details
 * pane to change the shape to what suits your need.
 *
 * Written by: Nicolas Herrera (nherrera@cra.com), 2020
 */
UCLASS(Blueprintable)
class VSDKINPUTPLUGIN_API UInteractionVolume : public USceneComponent
{
	GENERATED_BODY()

public:
	UInteractionVolume();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VSDK | Interaction Volumes")
		UFilterInteractables* FilterForInteractableObjects;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VSDK | Interaction Volumes")
		UShapeComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VSDK | Interaction Volumes")
		TSet<AActor*> IntersectingActors;

	UFUNCTION(BlueprintCallable, Category = "VSDK | Interaction Volumes")
		virtual void UseVolume(AActor* UsingActor);

	UFUNCTION(BlueprintCallable, Category = "VSDK | Interaction Volumes")
		virtual void FinishUseVolume(AActor* UsingActor);

	UFUNCTION(BlueprintCallable, Category = "VSDK | Interaction Volumes")
		virtual void StopUseVolume(AActor* UsingActor);

	/** Events */
	UPROPERTY(BlueprintAssignable, Category = "VSDK | Interaction Volumes")
		FInteractionVolumeSignature OnObjectEnter;

	UPROPERTY(BlueprintAssignable, Category = "VSDK | Interaction Volumes")
		FInteractionVolumeSignature OnObjectExit;

	UPROPERTY(BlueprintAssignable, Category = "VSDK | Interaction Volumes")
		FInteractionVolumeSignature OnUseStarted;

	UPROPERTY(BlueprintAssignable, Category = "VSDK | Interaction Volumes")
		FInteractionVolumeSignature OnUseFinished;

	UPROPERTY(BlueprintAssignable, Category = "VSDK | Interaction Volumes")
		FInteractionVolumeSignature OnUseStopped;

	/** Overlap Methods */
	UFUNCTION()
		virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	/** Utility Methods */
	UFUNCTION(BlueprintCallable, Category = "VSDK | Interaction Volumes")
		bool IsInteractableObject(AActor* Other);

	UFUNCTION(BlueprintCallable, Category = "VSDK | Interaction Volumes")
		bool IsHand(AActor* Other);

	/** UActorComponent Overrides */
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void OnComponentCreated() override;
};
