// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#include "GrabAttachment.h"
#include "InteractableGrab.h"

UGrabAttachment::UGrabAttachment()
{
}

void UGrabAttachment::SetInteractableGrab(UInteractableGrab* GrabType)
{
	InteractableGrab = GrabType;
}

UInteractableGrab * UGrabAttachment::GetInteractableGrab()
{
	return InteractableGrab;
}

void UGrabAttachment::TryGrab(AActor* GrabberActor, AActor* PreviousGrabber)
{
}

void UGrabAttachment::TryUngrab(AActor* UngrabberActor)
{
}
