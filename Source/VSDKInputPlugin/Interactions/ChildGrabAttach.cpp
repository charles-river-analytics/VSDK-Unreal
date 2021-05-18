// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#include "ChildGrabAttach.h"

UChildGrabAttach::UChildGrabAttach()
{
}

void UChildGrabAttach::TryGrab(AActor* GrabberActor, AActor* PreviousGrabber)
{
	OriginalParent = InteractableOwner;

	if (GrabberActor)
	{
		if (PhysicsComponent)
		{
			PhysicsComponent->SetSimulatePhysics(false);
		}

		FAttachmentTransformRules TransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false);

		InteractableOwner->AttachToComponent(GrabberActor->GetRootComponent(), TransformRules);

		// Move the object to the offset if given
		if (GrabComponent)
		{
			InteractableOwner->SetActorLocation(InteractableOwner->GetActorLocation() + GrabComponent->GetGrabOffset(GrabberActor));
		}
	}
}

void UChildGrabAttach::TryUngrab(AActor* UngrabberActor)
{
	if (PhysicsComponent)
	{
		PhysicsComponent->SetSimulatePhysics(bSimulatingPhysics);
	}

	if (OriginalParent && InteractableOwner != OriginalParent)
	{
		FAttachmentTransformRules TransformRules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false);

		InteractableOwner->AttachToActor(OriginalParent, TransformRules);
	}
	else
	{
		// Detach from all everything, making it exist back at the root of the world
		FDetachmentTransformRules DetachmentRules(EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, EDetachmentRule::KeepWorld, false);
		
		InteractableOwner->DetachFromActor(DetachmentRules);
	}
}

void UChildGrabAttach::BeginPlay_Implementation()
{
	if (InteractableOwner != nullptr)
	{
		PhysicsComponent = Cast<UPrimitiveComponent>(InteractableOwner->GetComponentByClass(UPrimitiveComponent::StaticClass()));

		if (PhysicsComponent != nullptr)
		{
			bSimulatingPhysics = PhysicsComponent->BodyInstance.bSimulatePhysics;
		}

		GrabComponent = Cast<UInteractableGrab>(InteractableOwner->GetComponentByClass(UInteractableGrab::StaticClass()));
	}
}