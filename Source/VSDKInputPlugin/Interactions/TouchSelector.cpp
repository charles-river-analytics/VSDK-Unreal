// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#include "TouchSelector.h"

UTouchSelector::UTouchSelector()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTouchSelector::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		GetOwner()->OnActorBeginOverlap.AddDynamic(this, &UTouchSelector::OnOverlapBegin);
		GetOwner()->OnActorEndOverlap.AddDynamic(this, &UTouchSelector::OnOverlapEnd);
	}
}

void UTouchSelector::EndPlay(EEndPlayReason::Type Reason)
{
	Super::EndPlay(Reason);

	if (GetOwner())
	{
		GetOwner()->OnActorBeginOverlap.RemoveDynamic(this, &UTouchSelector::OnOverlapBegin);
		GetOwner()->OnActorEndOverlap.RemoveDynamic(this, &UTouchSelector::OnOverlapEnd);
	}
}

void UTouchSelector::TrySelectAction_Implementation(AActor* ObjectSelecting)
{
	if (InteractableSelect)
	{
		InteractableSelect->Select(ObjectSelecting);
	}
}

void UTouchSelector::TryDeselectAction_Implementation(AActor* ObjectDeselecting)
{
	if (InteractableSelect)
	{
		InteractableSelect->Deselect(ObjectDeselecting);
	}
}

void UTouchSelector::SetSelectable(UInteractableSelect* GivenInteractableSelect)
{
	UE_LOG(LogTemp, Log, TEXT("SetSelectable %s"), *GivenInteractableSelect->GetName());
	InteractableSelect = GivenInteractableSelect;
}

void UTouchSelector::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor)
	{
		Execute_TrySelectAction(this, OtherActor);
	}
}

void UTouchSelector::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{	
	if (OtherActor)
	{
		Execute_TryDeselectAction(this, OtherActor);
	}
}