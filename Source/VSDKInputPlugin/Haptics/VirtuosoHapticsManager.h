// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <VirtuosoInput\Public\VirtuosoHandState.h>
#include "VirtuosoHapticsManager.generated.h"

/*
	The Virtuoso Haptics Manager is used to send Haptic Effects to devices.

	Contributors: Dan Duggan (dduggan@cra.com) Updated: November 2020
*/
UCLASS(Blueprintable)
class VSDKINPUTPLUGIN_API AVirtuosoHapticsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVirtuosoHapticsManager();

protected:
	virtual void BeginPlay() override;

public:	

	/*
		Called to trigger effects. Note that currently a payload only consists of an Unreal
		Engine haptic feedback effect and a hand ID as a location. As support for more
		body coordinate locations are added and additional haptic modalities, this method
		signature will be updated accordingly.
	*/
	virtual void PlayHapticEffect(class UHapticFeedbackEffect_Base* HapticPayload, VirtuosoHandId HapticLocation);

	class APlayerController* PlayerController;

};
