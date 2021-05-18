// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#include "DirectionGrabAttachment.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "InteractableGrab.h"

UDirectionGrabAttachment::UDirectionGrabAttachment()
{
}

void UDirectionGrabAttachment::TryGrab(AActor* GrabberActor, AActor* PreviousGrabber)
{
	bReadyToTick = true;
	FirstGrabber = PreviousGrabber;
	SecondGrabber = GrabberActor;

	InitialGrabOffset = InteractableOwner->GetActorLocation() - FirstGrabber->GetActorLocation();
}

void UDirectionGrabAttachment::TryUngrab(AActor* UngrabberActor)
{
	// Gracefully switch to being grabbed by the secobdary grabber actor if the primary grabber is released
	if (UngrabberActor == FirstGrabber)
	{
		// Since the SecondGrabber is already grabbing via this secondary grab, stop grabbing via this method and redo the grab
		InteractableGrab->Ungrab(SecondGrabber);
		InteractableGrab->Grab(SecondGrabber);
	}

	bReadyToTick = false;
	FirstGrabber = nullptr;
	SecondGrabber = nullptr;
}

void UDirectionGrabAttachment::Tick(float DeltaTime)
{
	if (FirstGrabber && SecondGrabber)
	{
		DrawDebugLine(GetWorld(), FirstGrabber->GetActorLocation(), SecondGrabber->GetActorLocation(), FColor::Blue, false, -1.0f, 0, .25f);
		DrawDebugLine(GetWorld(), FirstGrabber->GetActorLocation(), InteractableOwner->GetActorLocation(), FColor::Red, false, -1.0f, 0, .25f);

		FVector directionBetweenGrabbers = SecondGrabber->GetActorLocation() - FirstGrabber->GetActorLocation();

		FRotator targetRotation = UKismetMathLibrary::MakeRotFromX(directionBetweenGrabbers);
		
		InteractableOwner->SetActorRotation(targetRotation);

		FVector newLocation = FirstGrabber->GetActorLocation() + targetRotation.RotateVector(InitialGrabOffset);
		InteractableOwner->SetActorLocation(newLocation);
	}
}

bool UDirectionGrabAttachment::IsTickable() const
{
	return bReadyToTick;
}

TStatId UDirectionGrabAttachment::GetStatId() const
{
	return UObject::GetStatID();
}