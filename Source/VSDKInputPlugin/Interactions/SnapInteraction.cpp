// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.


#include "SnapInteraction.h"
#include "InteractableObject.h"
#include "InteractableComponent.h"
#include "InteractableSelect.h"
#include "InteractableGrab.h"
#include "Components/BoxComponent.h"

USnapInteraction::USnapInteraction()
{
	// no op
}

void USnapInteraction::TrySnapActor(AActor* Other)
{
	if (Other && Other->IsA(AInteractableObject::StaticClass()))
	{
		AInteractableObject* Interactable = Cast<AInteractableObject>(Other);
		if (Interactable)
		{
			UInteractableComponent* InteractableComp = Interactable->GetInteractableComponent(FName("Grab"));
			if (InteractableComp)
			{
				UInteractableGrab* GrabComp = Cast<UInteractableGrab>(InteractableComp);
				if (GrabComp)
				{
					GrabComp->ForceUngrab();
					FTransform NewActorTrans;
					NewActorTrans.SetLocation(GetComponentTransform().GetLocation() + SnapLocation);
					NewActorTrans.SetScale3D(Other->GetTransform().GetScale3D());
					NewActorTrans.SetRotation(SnapOrientation.Quaternion() * GetComponentTransform().GetRotation());
					Other->SetActorTransform(NewActorTrans);
					OnSnap(Other);
				}
			}
			
		}
	}
}

void USnapInteraction::OnSnap_Implementation(AActor* Other)
{
	// no op
}

