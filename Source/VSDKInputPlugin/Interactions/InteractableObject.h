// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrabHandle.h"
#include "InteractableObject.generated.h"

/*
 * The base actor for any object that should be interacted with by the user. This class
 * acts as a point for all the interactable components. Additionally, end developers
 * should try and reference this class for actions and not reference the components directly.
 *
 * Written by: Nicolas Herrera (nherrera@cra.com), 2020
 * Edited by: Arthur Wollocko (awollocko@cra.com), 2020
 */
UCLASS(Blueprintable, ClassGroup = (VSDK))
class VSDKINPUTPLUGIN_API AInteractableObject : public AActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TMap<FName, class UInteractableComponent*> AvailableInteractableComponents;

public:	
	AInteractableObject();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* InteractableMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UGrabHandle* GrabHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VSDK")
		class UInteractableSelect* DefaultSelectComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VSDK")
		class UInteractableGrab* DefaultGrabComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VSDK")
		class UInteractableUse* DefaultUseComponent;

	UFUNCTION(BlueprintCallable)
		UInteractableComponent* GetInteractableComponent(FName componentName);

	UFUNCTION(BlueprintCallable)
		FTransform GetGrabTransform();
};
