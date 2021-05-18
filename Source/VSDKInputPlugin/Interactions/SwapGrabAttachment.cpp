// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#include "SwapGrabAttachment.h"
#include "InteractableGrab.h"

void USwapGrabAttachment::TryGrab(AActor* GrabberActor, AActor* PreviousGrabber)
{
	// Force the object to be let go by the current grabber
	InteractableGrab->UngrabMain(PreviousGrabber);

	// Now grab by the current grabber
	InteractableGrab->Grab(GrabberActor);
}

void USwapGrabAttachment::TryUngrab(AActor* UngrabberActor)
{
	// Not needed as the swap is a one-time event that happens during the initial grab attempt
}