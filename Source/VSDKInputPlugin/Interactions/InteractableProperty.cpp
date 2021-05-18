// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#include "InteractableProperty.h"

UInteractableProperty::UInteractableProperty()
{
}

void UInteractableProperty::BeginPlay_Implementation()
{
	// Not the BeginPlay from UActorComponent, but from UInteractalbeProperty 
	// Use for setup in base classes
}

void UInteractableProperty::SetInteractableOwner(AInteractableObject * InteractOwner)
{
	InteractableOwner = InteractOwner;
}

AInteractableObject * UInteractableProperty::GetInteractableOwner()
{
	return InteractableOwner;
}
