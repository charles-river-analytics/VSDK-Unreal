// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#include "InteractableUse.h"

UInteractableUse::UInteractableUse()
{
	PrimaryComponentTick.bCanEverTick = true;

	ComponentName = FName("Use");
}

void UInteractableUse::BeginPlay()
{
	Super::BeginPlay();

	if (UseAction)
	{
		PrimaryUseAction = NewObject<UUseAction>(this, UseAction);
		PrimaryUseAction->SetInteractableOwner(Cast<AInteractableObject>(GetOwner()));
		PrimaryUseAction->SetInteractableUse(this);
		PrimaryUseAction->BeginPlay();
	}
}

bool UInteractableUse::IsActionable_Implementation()
{
	return !bIsComponentActive;
}

void UInteractableUse::Use(AActor* UsingActor)
{
	if (IsActionable())
	{
		if (PrimaryUseAction)
		{
			PrimaryUseAction->TryUse(UsingActor);

			bIsComponentActive = true;

			OnInteractableUse.Broadcast(this, UsingActor);
		}
	}
}

void UInteractableUse::StopUse(AActor* UnusingActor)
{
	if (bIsComponentActive)
	{
		if (PrimaryUseAction)
		{
			PrimaryUseAction->TryUnuse(UnusingActor);

			bIsComponentActive = false;

			OnInteractableStopUse.Broadcast(this, UnusingActor);
		}	
	}
}