// Copyright 2020 Charles River Analytics, Inc. All Rights Reserved.

#include "InteractableComponent.h"

UInteractableComponent::UInteractableComponent()
{
	bIsComponentActive = false;

	InteractableObject = Cast<AInteractableObject>(GetOwner());
}

void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();
}

FName UInteractableComponent::GetComponentName()
{
	return ComponentName;
}

// Default interactable component is not actionable
bool UInteractableComponent::IsActionable_Implementation()
{
	return false;
}