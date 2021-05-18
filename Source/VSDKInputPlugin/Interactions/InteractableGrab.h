// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "InteractableComponent.h"
#include "GrabAttachment.h"
#include "InteractableGrab.generated.h"

/* 
* Delegate used for broadcasting Grab Events (OnGrab, OnUnGrab, etc.). 
* First param is the UInteractableGrab being grabbed/ungrabbed 
* Second param is the Actor that is grabbing
*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGrabSignature, UInteractableGrab*, InteractableGrabSource, AActor*, GrabbingActor);

// Forward declarations
class UGrabAttachment;

/*
 * UInteractableComponent implementation that allows an object to be grabbed. The
 * grabbing behavior requires the user to implement or use a class that implements the
 * GrabAttachment script in order to grab/ungrab an object in different ways.
 *
 * Written by: Nicolas Herrera (nherrera@cra.com), Dan Duggan (dduggan@cra.com), 2021
 */
UCLASS( ClassGroup=(VSDK), meta=(BlueprintSpawnableComponent) )
class VSDKINPUTPLUGIN_API UInteractableGrab : public UInteractableComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:	
	UInteractableGrab();

	UFUNCTION(BlueprintCallable, Category = "VSDK")
		void Grab(AActor* GrabberActor);

	UFUNCTION(BlueprintCallable, Category = "VSDK")
		void Ungrab(AActor* GrabberActor);

	UFUNCTION(BlueprintCallable, Category = "VSDK")
		void UngrabMain(AActor* GrabberActor);

	UFUNCTION(BlueprintCallable, Category = "VSDK")
		int GetGrabCount();

	UFUNCTION(BlueprintCallable, Category = "VSDK")
		void ForceUngrab();

	UFUNCTION(BlueprintCallable, Category = "VSDK")
		FVector GetGrabOffset(AActor* GrabberActor);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VSDK")
		TArray<AActor*> GrabberActorArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VSDK")
		TSubclassOf<UGrabAttachment> GrabAttach;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VSDK")
		bool bPrecisionGrab;

	UPROPERTY()
		UGrabAttachment* PrimaryGrabAttachment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VSDK")
		TSubclassOf<UGrabAttachment> MultiGrabAttachment;

	UPROPERTY()
		UGrabAttachment* SecondaryGrabAttachment;

	/* Events */
	UPROPERTY(EditAnywhere, BlueprintAssignable, Category = "VSDK")
		FOnGrabSignature OnInteractableGrab;

	UPROPERTY(EditAnywhere, BlueprintAssignable, Category = "VSDK")
		FOnGrabSignature OnInteractableUngrab;

	/*IInteractableComponent Implementation*/
	virtual bool IsActionable_Implementation() override;
};
