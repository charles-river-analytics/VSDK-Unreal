// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#include "InteractableGrab.h"
#include "UObject/UObjectBaseUtility.h"

UInteractableGrab::UInteractableGrab()
{
	PrimaryComponentTick.bCanEverTick = true;

	ComponentName = FName("Grab");
}

void UInteractableGrab::BeginPlay()
{
	Super::BeginPlay();

	if (GrabAttach)
	{
		PrimaryGrabAttachment = NewObject<UGrabAttachment>(this, GrabAttach);
		PrimaryGrabAttachment->SetInteractableOwner(Cast<AInteractableObject>(GetOwner()));
		PrimaryGrabAttachment->SetInteractableGrab(this);
		PrimaryGrabAttachment->BeginPlay();
	}

	if (MultiGrabAttachment)
	{
		SecondaryGrabAttachment = NewObject<UGrabAttachment>(this, MultiGrabAttachment);
		SecondaryGrabAttachment->SetInteractableOwner(Cast<AInteractableObject>(GetOwner()));
		SecondaryGrabAttachment->SetInteractableGrab(this);
		SecondaryGrabAttachment->BeginPlay();
	}
}

bool UInteractableGrab::IsActionable_Implementation()
{
	return !bIsComponentActive;
}

int UInteractableGrab::GetGrabCount()
{
	return GrabberActorArray.Num();
}

void UInteractableGrab::Grab(AActor* GrabberActor)
{
	if (GrabberActor)
	{
		GrabberActorArray.Add(GrabberActor);

		if (GetGrabCount() == 1)
		{
			if (PrimaryGrabAttachment)
			{
				PrimaryGrabAttachment->TryGrab(GrabberActor, nullptr);
			}
		}
		else
		{
			// TODO For now, handle only having a single multigrab attachment
			if (SecondaryGrabAttachment)
			{
				SecondaryGrabAttachment->TryGrab(GrabberActor, GrabberActorArray[0]);
			}
		}

		bIsComponentActive = true;

		OnInteractableGrab.Broadcast(this, GrabberActor);
	}
}

void UInteractableGrab::Ungrab(AActor* GrabberActor)
{
	if (GrabberActorArray.Contains(GrabberActor))
	{
		GrabberActorArray.Remove(GrabberActor);

		OnInteractableUngrab.Broadcast(this, GrabberActor);

		if (GetGrabCount() == 0)
		{
			if (PrimaryGrabAttachment)
			{
				PrimaryGrabAttachment->TryUngrab(GrabberActor);
			}

			bIsComponentActive = false;
		}
		else
		{
			if (SecondaryGrabAttachment != nullptr)
			{
				SecondaryGrabAttachment->TryUngrab(GrabberActor);
			}
		}
	}
}

void UInteractableGrab::UngrabMain(AActor* GrabberActor)
{
	if (GrabberActorArray.Contains(GrabberActor))
	{
		GrabberActorArray.Remove(GrabberActor);

		OnInteractableUngrab.Broadcast(this, GrabberActor);

		if (PrimaryGrabAttachment)
		{
			PrimaryGrabAttachment->TryUngrab(GrabberActor);

			if (GetGrabCount() == 0)
			{
				bIsComponentActive = false;
			}
		}
	}
}

void UInteractableGrab::ForceUngrab()
{
	// Duplicate the array so items aren't removed while iterating
	TArray<AActor*> GrabberActorArrayDuplicate;
	for (int32 index = 0; index < GrabberActorArray.Num(); index++)
	{
		GrabberActorArrayDuplicate.Add(GrabberActorArray[index]);
	}

	// Remove each item from the array
	for (int32 index = 0; index < GrabberActorArrayDuplicate.Num(); index++)
	{
		Ungrab(GrabberActorArrayDuplicate[index]);
	}
}

FVector UInteractableGrab::GetGrabOffset(AActor* GrabberActor)
{
	if (bPrecisionGrab)
	{
		return FVector::ZeroVector;
	}

	// Note: We may want to set up a similiar 'grab holder area' on a controller/hand and not use the location of the actor
	return GrabberActor->GetActorLocation() - InteractableObject->GetGrabTransform().GetLocation();
}