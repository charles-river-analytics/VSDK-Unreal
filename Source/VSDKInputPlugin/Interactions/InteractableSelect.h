// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.h"
#include "Selectable.h"
#include "Selector.h"
#include "InteractableSelect.generated.h"
/*
	Delegate used for Select events on Interactable Objects.
	The first param is the Interactable Select Component sending the event
	The second param is the Actor that is selecting the object
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSelectionSignature, UInteractableSelect*, InteractableSelectSource, AActor*, SelectingActor);

/*
 * This InteractableComponent enabled an object to be selected and holds the appropriate
 * data and events to give off when the object is selected.
 *
 * Written by: Nicolas Herrera (nherrera@cra.com), Dan Duggan (dduggan@cra.com), 2021
 */
UCLASS( ClassGroup=(VSDK), meta=(BlueprintSpawnableComponent) )
class VSDKINPUTPLUGIN_API UInteractableSelect : public UInteractableComponent
{
	GENERATED_BODY()

protected:
	/** ActorComponent Override */
	virtual void BeginPlay() override;

public:	
	UInteractableSelect();

	UPROPERTY()
		TMap<AActor*, TScriptInterface<ISelector>> CurrentSelectors;

	UFUNCTION(BlueprintCallable, Category = "VSDK")
		bool IsSelectedByActor(AActor* SelectingActor);

	UFUNCTION(BlueprintCallable, Category = "VSDK")
		void Select(AActor* ObjectSelecting);

	UFUNCTION(BlueprintCallable, Category = "VSDK")
		void Deselect(AActor* ObjectDeselecting);

	/* Events */
	UPROPERTY(EditAnywhere, BlueprintAssignable, Category = "VSDK")
		FOnSelectionSignature OnInteractableSelect;

	UPROPERTY(EditAnywhere, BlueprintAssignable, Category = "VSDK")
		FOnSelectionSignature OnInteractableDeselect;

	/* IInteractableComponent Implementation */	
	virtual bool IsActionable_Implementation() override;
};
