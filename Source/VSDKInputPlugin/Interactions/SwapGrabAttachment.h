// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GrabAttachment.h"
#include "SwapGrabAttachment.generated.h"

/**
 * GrabAttachment for a secondary grabs that will switch the interactable object 
 * from the first grabber to the second grabber.
 * 
 * Written by: Nicolas Herrera (nherrera@cra.com), 2020
 */
UCLASS()
class VSDKINPUTPLUGIN_API USwapGrabAttachment : public UGrabAttachment
{
	GENERATED_BODY()
	
public:
	/* UGrabAttachment Override */
	virtual void TryGrab(AActor* GrabberActor, AActor* PreviousGrabber) override;

	virtual void TryUngrab(AActor* UngrabberActor) override;
};
