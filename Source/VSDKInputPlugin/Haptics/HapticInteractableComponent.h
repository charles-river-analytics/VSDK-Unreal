// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <VirtuosoInput\Public\VirtuosoHandState.h>
#include "HapticInteractableComponent.generated.h"

/*
	The Haptic Interactable Component is designed to be attached to interactable objects and
	provide haptic outputs for common actions. For now, the haptic outputs must be wired
	manually in Blueprint, but in future iterations they will loop in automatically.

	Contributors: Dan Duggan (dduggan@cra.com) Updated: November 2020
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VSDKINPUTPLUGIN_API UHapticInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHapticInteractableComponent();

	UPROPERTY(EditAnywhere)
		class UHapticFeedbackEffect_Base* SelectEffect;

	UPROPERTY(EditAnywhere)
		class UHapticFeedbackEffect_Base* DeselectEffect;

	UPROPERTY(EditAnywhere)
		class UHapticFeedbackEffect_Base* GrabEffect;

	UPROPERTY(EditAnywhere)
		class UHapticFeedbackEffect_Base* UngrabEffect;

	UPROPERTY(EditAnywhere)
		class UHapticFeedbackEffect_Base* UseEffect;

	UFUNCTION(BlueprintCallable)
		virtual void PlaySelectEffect();

	UFUNCTION(BlueprintCallable)
		virtual void PlayDeselectEffect();

	UFUNCTION(BlueprintCallable)
		virtual void PlayGrabEffect();

	UFUNCTION(BlueprintCallable)
		virtual void PlayUngrabEffect();

	UFUNCTION(BlueprintCallable)
		virtual void PlayUseEffect();

	UFUNCTION(BlueprintCallable)
		void SetSelectingHand(VirtuosoHandId Selector);


protected:
	virtual void BeginPlay() override;

	// Searches the current world for a haptics manager
	virtual void FindHapticsManager();

	class AVirtuosoHapticsManager* HapticsManager;

	VirtuosoHandId CurrentSelectingHand;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
