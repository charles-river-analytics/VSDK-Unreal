// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.h"
#include "InteractableSelect.h"
#include "UseAction.h"
#include "InteractableUse.generated.h"

/*
	Delegate used for Use Events
	First parameter is the UInteractbleUse component sending the event
	Second parameter is the actor "using" the component
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUseSignature, UInteractableUse*, InteractableUseSender, AActor*, UsingActor);

/**
 * UInteractableComponent implementation to enable an object to have a generic
 * 'use' that can be triggered. Implement an a class that inherits the IUse-Action
 * interface in order to enable behavior that can be repeated across interactable objects.
 *
 * TODO Enable the condition (or not) that the object must be grabbed and/or selected
 *
 * Written by: Nicolas Herrera (nherrera@cra.com), Dan Duggan (dduggan@cra.com), 2021
 */
UCLASS( ClassGroup=(VSDK), meta=(BlueprintSpawnableComponent) )
class VSDKINPUTPLUGIN_API UInteractableUse : public UInteractableComponent
{
	GENERATED_BODY()

public:	
	UInteractableUse();

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, Category = "VSDK")
		void Use(AActor* UsingActor);

	UFUNCTION(BlueprintCallable, Category = "VSDK")
		void StopUse(AActor* UnusingActor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VSDK")
		TSubclassOf<UUseAction> UseAction;

	UPROPERTY()
		UUseAction* PrimaryUseAction;

	/* Events */
	UPROPERTY(EditAnywhere, BlueprintAssignable, Category = "VSDK")
		FOnUseSignature OnInteractableUse;

	UPROPERTY(EditAnywhere, BlueprintAssignable, Category = "VSDK")
		FOnUseSignature OnInteractableStopUse;

	/* IInteractableComponent Implementation */
	virtual bool IsActionable_Implementation() override;
};
