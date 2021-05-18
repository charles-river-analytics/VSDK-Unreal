// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "Selectable.h"
#include "InteractableSelect.h"
#include "TouchSelector.generated.h"

/*
 * Basic implementation of an ISelectable for selecting an AInteractableObject via collisions. 
 *
 * Written by: Nicolas Herrera (nherrera@cra.com), 2020
 */
UCLASS( ClassGroup=(VSDK), meta=(BlueprintSpawnableComponent) )
class VSDKINPUTPLUGIN_API UTouchSelector : public UActorComponent, public ISelectable
{
	GENERATED_BODY()

public:	
	UTouchSelector();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(EEndPlayReason::Type Reason) override;

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UInteractableSelect* InteractableSelect;

	/* ISelectable implementation */
	UFUNCTION()
		virtual void TrySelectAction_Implementation(AActor* ObjectSelecting) override;

	UFUNCTION()
		virtual void TryDeselectAction_Implementation(AActor* ObjectDeselecting) override;

	UFUNCTION()
		virtual void SetSelectable(UInteractableSelect* GivenInteractableSelect) override;

	/* Physics events to detect overlap */
	UFUNCTION()
		void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
		void OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);
};
